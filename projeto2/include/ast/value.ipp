
namespace ast {
    template<typename A>
    value<A>::value():
      object{new ast::empty_node<A>{}} { }

    template<typename A>
    value<A>::value(node_ptr node):
      object{std::move(node)} { }

    template<typename A>
    template<typename T>
    value<A>::value(const T& data):
      object{new ast::model<A, T>{data}} { }

    template<typename A>
    bool value<A>::empty() const {
        return object->empty();
    }

    template<typename A>
    value<A>::operator node_ptr() {
        return object;
    }

    template<typename A>
    template<typename T>
    void value<A>::op_assign(value<A>& rhs, const T& op) {
        if (rhs.object->empty()) {
            object = std::move(rhs.object);
        } else if (!object->empty()) {
            auto n = std::make_shared<ast::model<A, T>>(op);
            n->add_subnode(std::move(object));
            n->add_subnode(std::move(rhs.object));
            object = n;
        } else {
            rhs.object.reset(new ast::empty_node<A>);
        }
    }

    template<typename A>
    template<typename T>
    value<A> value<A>::op(value<A>& rhs, const T& op) {
        if (rhs.object->empty()) {
            object.reset(new ast::empty_node<A>);
            auto v = value<A>{};
            v.object.reset(new ast::empty_node<A>);
            return v;
        }
        
        if(object->empty()) {
            rhs.object.reset(new ast::empty_node<A>);
            auto v = value<A>{};
            v.object.reset(new ast::empty_node<A>);
            return v;
        }
        
        auto v = value<A>{op};
        v.object->add_subnode(std::move(object));
        v.object->add_subnode(std::move(rhs.object));
        return v;
    }

    template<typename A>
    template<typename T>
    value<A> value<A>::op(const T& op) {
        if(object->empty()) {
            object.reset(new ast::empty_node<A>);
            auto v = value<A>{};
            v.object.reset(new ast::empty_node<A>);
            return v;
        }

        auto v = value<A>{op};
        v.object->add_subnode(std::move(object));
        return v;
    }

    template<typename A>
    void value<A>::traverse(A& analyser) {
        object->traverse(analyser);
    }

    template<typename A>
    value<A>& value<A>::operator+=(value<A>& rhs) {
        op_assign(
            rhs,
            falk::op::callback<falk::op::assignment,
                               falk::op::assignment::ADD, 2>()
        );
        return *this;
    }

    template<typename A>
    value<A>& value<A>::operator-=(value<A>& rhs) {
        op_assign(
            rhs,
            falk::op::callback<falk::op::assignment,
                               falk::op::assignment::SUB, 2>()
        );
        return *this;
    }

    template<typename A>
    value<A>& value<A>::operator*=(value<A>& rhs) {
        op_assign(
            rhs,
            falk::op::callback<falk::op::assignment,
                               falk::op::assignment::MULT, 2>()
        );
        return *this;
    }

    template<typename A>
    value<A>& value<A>::operator/=(value<A>& rhs) {
        op_assign(
            rhs,
            falk::op::callback<falk::op::assignment,
                               falk::op::assignment::DIV, 2>()
        );
        return *this;
    }

    template<typename A>
    value<A>& value<A>::operator%=(value<A>& rhs) {
        op_assign(
            rhs,
            falk::op::callback<falk::op::assignment,
                               falk::op::assignment::MOD, 2>()
        );
        return *this;
    }

    template<typename A>
    value<A>& value<A>::operator&=(value<A>& rhs) {
        op_assign(
            rhs,
            falk::op::callback<falk::op::assignment,
                               falk::op::assignment::AND, 2>()
        );
        return *this;
    }

    template<typename A>
    value<A>& value<A>::operator|=(value<A>& rhs) {
        op_assign(
            rhs,
            falk::op::callback<falk::op::assignment,
                               falk::op::assignment::OR, 2>()
        );
        return *this;
    }

    template<typename A>
    value<A> value<A>::operator!() {
        return op(
            falk::op::callback<falk::op::assignment,
                               falk::op::assignment::OR, 2>()
        );
    }

    template<typename A>
    value<A>& value<A>::pow(value<A>& rhs) {
        op_assign(
            rhs,
            falk::op::callback<falk::op::assignment,
                               falk::op::assignment::POW, 2>()
        );
        return *this;
    }

    template<typename A>
    value<A> value<A>::pow(value<A>& lhs, value<A>& rhs) {
        return lhs.op(
            rhs,
            falk::op::callback<falk::op::arithmetic,
                               falk::op::arithmetic::POW, 2>()
        );
    }

    template<typename A>
    value<A> operator+(value<A>& lhs, value<A>& rhs) {
        return lhs.op(
            rhs,
            falk::op::callback<falk::op::arithmetic,
                               falk::op::arithmetic::ADD, 2>()
        );
    }

    template<typename A>
    value<A> operator-(value<A>& lhs, value<A>& rhs) {
        return lhs.op(
            rhs,
            falk::op::callback<falk::op::arithmetic,
                               falk::op::arithmetic::SUB, 2>()
        );
    }

    template<typename A>
    value<A> operator-(value<A>& rhs) {
        return rhs.op(
            falk::op::callback<falk::op::arithmetic,
                               falk::op::arithmetic::SUB, 1>()
        );
    }

    template<typename A>
    value<A> operator*(value<A>& lhs, value<A>& rhs) {
        return lhs.op(
            rhs,
            falk::op::callback<falk::op::arithmetic,
                               falk::op::arithmetic::MULT, 2>()
        );
    }

    template<typename A>
    value<A> operator/(value<A>& lhs, value<A>& rhs) {
        return lhs.op(
            rhs,
            falk::op::callback<falk::op::arithmetic,
                               falk::op::arithmetic::DIV, 2>()
        );
    }

    template<typename A>
    value<A> operator%(value<A>& lhs, value<A>& rhs) {
        return lhs.op(
            rhs,
            falk::op::callback<falk::op::arithmetic,
                               falk::op::arithmetic::MOD, 2>()
        );
    }

    template<typename A>
    value<A> operator<(value<A>& lhs, value<A>& rhs) {
        return lhs.op(
            rhs,
            falk::op::callback<falk::op::comparison,
                               falk::op::comparison::LT, 2>()
        );
    }

    template<typename A>
    value<A> operator>(value<A>& lhs, value<A>& rhs) {
        return lhs.op(
            rhs,
            falk::op::callback<falk::op::comparison,
                               falk::op::comparison::GT, 2>()
        );
    }

    template<typename A>
    value<A> operator<=(value<A>& lhs, value<A>& rhs) {
        return lhs.op(
            rhs,
            falk::op::callback<falk::op::comparison,
                               falk::op::comparison::LE, 2>()
        );
    }

    template<typename A>
    value<A> operator>=(value<A>& lhs, value<A>& rhs) {
        return lhs.op(
            rhs,
            falk::op::callback<falk::op::comparison,
                               falk::op::comparison::GE, 2>()
        );
    }

    template<typename A>
    value<A> operator==(value<A>& lhs, value<A>& rhs) {
        return lhs.op(
            rhs,
            falk::op::callback<falk::op::comparison,
                               falk::op::comparison::EQ, 2>()
        );
    }

    template<typename A>
    value<A> operator!=(value<A>& lhs, value<A>& rhs) {
        return lhs.op(
            rhs,
            falk::op::callback<falk::op::comparison,
                               falk::op::comparison::NE, 2>()
        );
    }

    template<typename A>
    value<A> operator&&(value<A>& lhs, value<A>& rhs) {
        return lhs.op(
            rhs,
            falk::op::callback<falk::op::logic,
                               falk::op::logic::AND, 2>()
        );
    }

    template<typename A>
    value<A> operator||(value<A>& lhs, value<A>& rhs) {
        return lhs.op(
            rhs,
            falk::op::callback<falk::op::logic,
                               falk::op::logic::OR, 2>()
        );
    }    
}
