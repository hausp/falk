#include <iostream>

template<typename A>
sma::list<A>& sma::list<A>::operator+=(node_ptr node) {
    object->add_subnode(node);
    return *this;
}
