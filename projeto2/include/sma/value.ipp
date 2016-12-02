
namespace sma {
    template<typename A, typename O>
    value<A,O>::value():
      object{new ast::empty_node<A>{}} { }

    template<typename A, typename O>
    value<A,O>::value(node_ptr node):
      object{std::move(node)} { }

    template<typename A, typename O>
    template<typename T>
    value<A,O>::value(const T& data):
      object{new ast::model<A, T>{data}} { }

    template<typename A, typename O>
    bool value<A,O>::empty() const {
        return object->empty();
    }

    template<typename A, typename O>
    value<A,O>::operator node_ptr() {
        return object;
    }

    template<typename A, typename O>
    template<typename T>
    void value<A,O>::op_assign(val& rhs, const T& op) {
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

    template<typename A, typename O>
    template<typename T>
    value<A,O> value<A,O>::op(value<A,O>& rhs, const T& op) {
        if (rhs.object->empty()) {
            object.reset(new ast::empty_node<A>);
            auto v = value<A,O>{};
            v.object.reset(new ast::empty_node<A>);
            return v;
        }
        
        if(object->empty()) {
            rhs.object.reset(new ast::empty_node<A>);
            auto v = value<A,O>{};
            v.object.reset(new ast::empty_node<A>);
            return v;
        }
        
        auto v = value<A,O>{op};
        v.object->add_subnode(std::move(object));
        v.object->add_subnode(std::move(rhs.object));
        return v;
    }

    template<typename A, typename O>
    template<typename T>
    value<A,O> value<A,O>::op(const T& op) {
        if(object->empty()) {
            object.reset(new ast::empty_node<A>);
            auto v = value<A,O>{};
            v.object.reset(new ast::empty_node<A>);
            return v;
        }

        auto v = value<A,O>{op};
        v.object->add_subnode(std::move(object));
        return v;
    }

    template<typename A, typename O>
    void value<A,O>::traverse(A& analyser) {
        object->traverse(analyser);
    }

    template<typename A, typename O>
    value<A,O>& value<A,O>::operator+=(value<A,O>& rhs) {
        op_assign(
            rhs,
            typename O::template
            callback<typename O::arithmetic, O::arithmetic::ADD, 2, true>()
        );
        return *this;
    }

    template<typename A, typename O>
    value<A,O>& value<A,O>::operator-=(value<A,O>& rhs) {
        op_assign(
            rhs,
            typename O::template
            callback<typename O::arithmetic, O::arithmetic::SUB, 2, true>()
        );
        return *this;
    }

    template<typename A, typename O>
    value<A,O>& value<A,O>::operator*=(value<A,O>& rhs) {
        op_assign(
            rhs,
            typename O::template
            callback<typename O::arithmetic, O::arithmetic::MULT, 2, true>()
        );
        return *this;
    }

    template<typename A, typename O>
    value<A,O>& value<A,O>::operator/=(value<A,O>& rhs) {
        op_assign(
            rhs,
            typename O::template
            callback<typename O::arithmetic, O::arithmetic::DIV, 2, true>()
        );
        return *this;
    }

    template<typename A, typename O>
    value<A,O>& value<A,O>::operator%=(value<A,O>& rhs) {
        op_assign(
            rhs,
            typename O::template
            callback<typename O::arithmetic, O::arithmetic::MOD, 2, true>()
        );
        return *this;
    }

    template<typename A, typename O>
    value<A,O>& value<A,O>::operator&=(value<A,O>& rhs) {
        op_assign(
            rhs,
            typename O::template
            callback<typename O::logic, O::logic::AND, 2, true>()
        );
        return *this;
    }

    template<typename A, typename O>
    value<A,O>& value<A,O>::operator|=(value<A,O>& rhs) {
        op_assign(
            rhs,
            typename O::template
            callback<typename O::logic, O::logic::OR, 2, true>()
        );
        return *this;
    }

    template<typename A, typename O>
    value<A,O> value<A,O>::operator!() {
        return op(
            typename O::template
            callback<typename O::logic, O::logic::OR, 2, true>()
        );
    }

    template<typename A, typename O>
    value<A,O>& value<A,O>::pow(value<A,O>& rhs) {
        op_assign(
            rhs,
            typename O::template
            callback<typename O::arithmetic, O::arithmetic::POW, 2, true>()
        );
        return *this;
    }

    template<typename A, typename O>
    value<A,O> value<A,O>::pow(value<A,O>& lhs, value<A,O>& rhs) {
        return lhs.op(
            rhs,
            typename O::template
            callback<typename O::arithmetic, O::arithmetic::POW, 2>()
        );
    }

    template<typename A, typename O>
    value<A,O> operator+(value<A,O>& lhs, value<A,O>& rhs) {
        return lhs.op(
            rhs,
            typename O::template
            callback<typename O::arithmetic, O::arithmetic::ADD, 2>()
        );
    }

    template<typename A, typename O>
    value<A,O> operator-(value<A,O>& lhs, value<A,O>& rhs) {
        return lhs.op(
            rhs, typename O::template
            callback<typename O::arithmetic, O::arithmetic::SUB, 2>()
        );
    }

    template<typename A, typename O>
    value<A,O> operator-(value<A,O>& rhs) {
        return rhs.op(
            typename O::template
            callback<typename O::arithmetic, O::arithmetic::SUB, 1>()
        );
    }

    template<typename A, typename O>
    value<A,O> operator*(value<A,O>& lhs, value<A,O>& rhs) {
        return lhs.op(
            rhs,
            typename O::template
            callback<typename O::arithmetic, O::arithmetic::MULT, 2>()
        );
    }

    template<typename A, typename O>
    value<A,O> operator/(value<A,O>& lhs, value<A,O>& rhs) {
        return lhs.op(
            rhs,
            typename O::template
            callback<typename O::arithmetic, O::arithmetic::DIV, 2>()
        );
    }

    template<typename A, typename O>
    value<A,O> operator%(value<A,O>& lhs, value<A,O>& rhs) {
        return lhs.op(
            rhs,
            typename O::template
            callback<typename O::arithmetic, O::arithmetic::MOD, 2>()
        );
    }

    template<typename A, typename O>
    value<A,O> operator<(value<A,O>& lhs, value<A,O>& rhs) {
        return lhs.op(
            rhs,
            typename O::template
            callback<typename O::comparison, O::comparison::LT, 2>()
        );
    }

    template<typename A, typename O>
    value<A,O> operator>(value<A,O>& lhs, value<A,O>& rhs) {
        return lhs.op(
            rhs,
            typename O::template
            callback<typename O::comparison, O::comparison::GT, 2>()
        );
    }

    template<typename A, typename O>
    value<A,O> operator<=(value<A,O>& lhs, value<A,O>& rhs) {
        return lhs.op(
            rhs,
            typename O::template
            callback<typename O::comparison, O::comparison::LE, 2>()
        );
    }

    template<typename A, typename O>
    value<A,O> operator>=(value<A,O>& lhs, value<A,O>& rhs) {
        return lhs.op(
            rhs,
            typename O::template
            callback<typename O::comparison, O::comparison::GE, 2>()
        );
    }

    template<typename A, typename O>
    value<A,O> operator==(value<A,O>& lhs, value<A,O>& rhs) {
        return lhs.op(
            rhs,
            typename O::template
            callback<typename O::comparison, O::comparison::EQ, 2>()
        );
    }

    template<typename A, typename O>
    value<A,O> operator!=(value<A,O>& lhs, value<A,O>& rhs) {
        return lhs.op(
            rhs,
            typename O::template
            callback<typename O::comparison, O::comparison::NE, 2>()
        );
    }

    template<typename A, typename O>
    value<A,O> operator&&(value<A,O>& lhs, value<A,O>& rhs) {
        return lhs.op(
            rhs,
            typename O::template
            callback<typename O::logic, O::logic::NE, 2>()
        );
    }

    template<typename A, typename O>
    value<A,O> operator||(value<A,O>& lhs, value<A,O>& rhs) {
        return lhs.op(
            rhs,
            typename O::template
            callback<typename O::logic, O::logic::NE, 2>()
        );
    }    
}
