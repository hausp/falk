
template<typename A>
ast::list<A>::list():
  object{new ast::empty_node<A>{}} { }

template<typename A>
template<typename T>
ast::list<A>::list(const T& data):
  object{new ast::model<A, T>{data}} { }


template<typename A>
ast::list<A>& ast::list<A>::operator+=(node_ptr node) {
    object->add_subnode(node);
    return *this;
}

template<typename A>
ast::list<A>::operator node_ptr() {
    return object;
}

template<typename A>
typename ast::list<A>::node_ptr ast::list<A>::extract() {
    return object;
}
