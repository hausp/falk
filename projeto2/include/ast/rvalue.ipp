
namespace ast {
    template<typename A>
    rvalue<A>::rvalue():
      object{new ast::empty_node<A>{}} { }

    template<typename A>
    rvalue<A>::rvalue(node_ptr node):
      object{std::move(node)} { }

    template<typename A>
    template<typename T>
    rvalue<A>::rvalue(const T& data):
      object{new ast::model<A, T>{data}} { }

    template<typename A>
    template<typename T>
    rvalue<A>::rvalue(const T& data, node_ptr node):
      object{new ast::model<A, T>{data}} {
        object->add_subnode(std::move(node));
    }

    template<typename A>
    bool rvalue<A>::empty() const {
        return object->empty();
    }

    template<typename A>
    rvalue<A>::operator node_ptr() {
        return object;
    }

    template<typename A>
    template<typename T>
    rvalue<A> rvalue<A>::op(rvalue<A>& rhs, const T& op) {
        if (rhs.object->empty()) {
            object.reset(new ast::empty_node<A>);
            auto v = rvalue<A>{};
            v.object.reset(new ast::empty_node<A>);
            return v;
        }
        
        if(object->empty()) {
            rhs.object.reset(new ast::empty_node<A>);
            auto v = rvalue<A>{};
            v.object.reset(new ast::empty_node<A>);
            return v;
        }
        
        auto v = rvalue<A>{op};
        v.object->add_subnode(std::move(object));
        v.object->add_subnode(std::move(rhs.object));
        return v;
    }

    template<typename A>
    template<typename T>
    rvalue<A> rvalue<A>::op(const T& op) {
        if(object->empty()) {
            object.reset(new ast::empty_node<A>);
            auto v = rvalue<A>{};
            v.object.reset(new ast::empty_node<A>);
            return v;
        }

        auto v = rvalue<A>{op};
        v.object->add_subnode(std::move(object));
        return v;
    }

    template<typename A>
    void rvalue<A>::visit(A& analyser) {
        object->visit(analyser);
    }

    template<typename A>
    rvalue<A> rvalue<A>::pow(rvalue<A>& lhs, rvalue<A>& rhs) {
        return lhs.op(rhs, falk::op::callback<falk::op::arithmetic,
                                              falk::op::arithmetic::POW, 2>());
    }

    template<typename A>
    rvalue<A> operator+(rvalue<A>& lhs, rvalue<A>& rhs) {
        return lhs.op(rhs, falk::op::callback<falk::op::arithmetic,
                                              falk::op::arithmetic::ADD, 2>());
    }

    template<typename A>
    rvalue<A> operator-(rvalue<A>& lhs, rvalue<A>& rhs) {
        return lhs.op(rhs, falk::op::callback<falk::op::arithmetic,
                                              falk::op::arithmetic::SUB, 2>());
    }

    template<typename A>
    rvalue<A> operator-(rvalue<A>& rhs) {
        return rhs.op(falk::op::callback<falk::op::arithmetic,
                                         falk::op::arithmetic::SUB, 1>());
    }

    template<typename A>
    rvalue<A> operator*(rvalue<A>& lhs, rvalue<A>& rhs) {
        return lhs.op(rhs, falk::op::callback<falk::op::arithmetic,
                                              falk::op::arithmetic::MULT, 2>());
    }

    template<typename A>
    rvalue<A> operator/(rvalue<A>& lhs, rvalue<A>& rhs) {
        return lhs.op(rhs, falk::op::callback<falk::op::arithmetic,
                                              falk::op::arithmetic::DIV, 2>());
    }

    template<typename A>
    rvalue<A> operator%(rvalue<A>& lhs, rvalue<A>& rhs) {
        return lhs.op(rhs, falk::op::callback<falk::op::arithmetic,
                                              falk::op::arithmetic::MOD, 2>());
    }

    template<typename A>
    rvalue<A> operator<(rvalue<A>& lhs, rvalue<A>& rhs) {
        return lhs.op(rhs, falk::op::callback<falk::op::comparison,
                                              falk::op::comparison::LT, 2>());
    }

    template<typename A>
    rvalue<A> operator>(rvalue<A>& lhs, rvalue<A>& rhs) {
        return lhs.op(rhs, falk::op::callback<falk::op::comparison,
                                              falk::op::comparison::GT, 2>());
    }

    template<typename A>
    rvalue<A> operator<=(rvalue<A>& lhs, rvalue<A>& rhs) {
        return lhs.op(rhs, falk::op::callback<falk::op::comparison,
                                              falk::op::comparison::LE, 2>());
    }

    template<typename A>
    rvalue<A> operator>=(rvalue<A>& lhs, rvalue<A>& rhs) {
        return lhs.op(rhs, falk::op::callback<falk::op::comparison,
                                              falk::op::comparison::GE, 2>());
    }

    template<typename A>
    rvalue<A> operator==(rvalue<A>& lhs, rvalue<A>& rhs) {
        return lhs.op(rhs, falk::op::callback<falk::op::comparison,
                                              falk::op::comparison::EQ, 2>());
    }

    template<typename A>
    rvalue<A> operator!=(rvalue<A>& lhs, rvalue<A>& rhs) {
        return lhs.op(rhs, falk::op::callback<falk::op::comparison,
                                              falk::op::comparison::NE, 2>());
    }

    template<typename A>
    rvalue<A> operator&&(rvalue<A>& lhs, rvalue<A>& rhs) {
        return lhs.op(rhs, falk::op::callback<falk::op::logic,
                                              falk::op::logic::AND, 2>());
    }

    template<typename A>
    rvalue<A> operator||(rvalue<A>& lhs, rvalue<A>& rhs) {
        return lhs.op(rhs, falk::op::callback<falk::op::logic,
                                              falk::op::logic::OR, 2>());
    }

    template<typename A>
    rvalue<A> operator!(rvalue<A>& rhs) {
        return rhs.op(rhs, falk::op::callback<falk::op::logic,
                                              falk::op::logic::NOT, 1>());
    }
}

template<typename A>
typename ast::rvalue<A>::node_ptr ast::rvalue<A>::extract() {
    return object;
}
