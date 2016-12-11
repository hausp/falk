
template<typename A>
ast::lvalue<A>::lvalue():
  object{new ast::empty_node<A>{}} { }

template<typename A>
template<typename T>
ast::lvalue<A>::lvalue(const T& data):
  object{new ast::model<A, T>{data}} { }

template<typename A>
bool ast::lvalue<A>::empty() const {
    return object->empty();
}

template<typename A>
template<typename T>
void ast::lvalue<A>::op_assign(rvalue<A>& rhs, const T& op) {
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
void ast::lvalue<A>::set_index(node_ptr row, node_ptr column) {
    object->add_subnode(std::move(row));
    object->add_subnode(std::move(column));
}

template<typename A>
ast::lvalue<A>& ast::lvalue<A>::operator+=(rvalue<A>& rhs) {
    op_assign(rhs, falk::op::callback<falk::op::assignment,
                                      falk::op::assignment::ADD, 2>());
    return *this;
}

template<typename A>
ast::lvalue<A>& ast::lvalue<A>::operator-=(rvalue<A>& rhs) {
    op_assign(rhs, falk::op::callback<falk::op::assignment,
                                      falk::op::assignment::SUB, 2>());
    return *this;
}

template<typename A>
ast::lvalue<A>& ast::lvalue<A>::operator*=(rvalue<A>& rhs) {
    op_assign(rhs, falk::op::callback<falk::op::assignment,
                                      falk::op::assignment::MULT, 2>());
    return *this;
}

template<typename A>
ast::lvalue<A>& ast::lvalue<A>::operator/=(rvalue<A>& rhs) {
    op_assign(rhs, falk::op::callback<falk::op::assignment,
                                      falk::op::assignment::DIV, 2>());
    return *this;
}

template<typename A>
ast::lvalue<A>& ast::lvalue<A>::operator%=(rvalue<A>& rhs) {
    op_assign(rhs, falk::op::callback<falk::op::assignment,
                                      falk::op::assignment::MOD, 2>());
    return *this;
}

template<typename A>
ast::lvalue<A>& ast::lvalue<A>::operator&=(rvalue<A>& rhs) {
    op_assign(rhs, falk::op::callback<falk::op::assignment,
                                      falk::op::assignment::AND, 2>());
    return *this;
}

template<typename A>
ast::lvalue<A>& ast::lvalue<A>::operator|=(rvalue<A>& rhs) {
    op_assign(rhs, falk::op::callback<falk::op::assignment,
                                      falk::op::assignment::OR, 2>());
    return *this;
}

template<typename A>
ast::lvalue<A>& ast::lvalue<A>::pow(rvalue<A>& rhs) {
    op_assign(rhs, falk::op::callback<falk::op::assignment,
                                      falk::op::assignment::POW, 2>());
    return *this;
}

template<typename A>
ast::lvalue<A>& ast::lvalue<A>::operator=(rvalue<A>& rhs) {
    op_assign(rhs, falk::op::callback<falk::op::assignment,
                                      falk::op::assignment::DIRECT, 2>());
    return *this;
}

template<typename A>
ast::lvalue<A>::operator rvalue<A>() {
    auto v = rvalue<A>(falk::valueof());
    v.object->add_subnode(std::move(object));
    return v;
}

template<typename A>
typename ast::lvalue<A>::node_ptr ast::lvalue<A>::extract() {
    return object;
}
