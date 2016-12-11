
template<typename A>
ast::declaration<A>::declaration():
  object{new empty} { }

template<typename A>
template<typename T>
ast::declaration<A>::declaration(const T& data, node_ptr value):
  object{new ast::model<A, T>{data}} {
    object->add_subnode(value);
}

template<typename A>
typename ast::declaration<A>::node_ptr ast::declaration<A>::extract() {
    return object;
}