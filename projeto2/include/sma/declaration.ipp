
template<typename A>
sma::declaration<A>::declaration():
  object{new empty} { }

template<typename A>
template<typename T>
sma::declaration<A>::declaration(const T& data, node_ptr value):
  object{new ast::model<A, T>{data}} {
    object->add_subnode(value);
}

template<typename A>
typename sma::declaration<A>::node_ptr sma::declaration<A>::extract() {
    return object;
}