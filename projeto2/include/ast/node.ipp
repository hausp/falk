
template<typename Analyser>
falk::ast::node<Analyser>::~node() { }

template<typename Analyser>
falk::ast::tnode<Analyser>::tnode(typename Analyser::Type type):
 type{type} { }

template<typename Analyser>
falk::ast::tnode<Analyser>::~tnode() { }

template<typename Analyser>
void falk::ast::lnode<Analyser>::traverse(Analyser& analyser) {
    analyser.analyse(*this);
}

template<typename Analyser>
void falk::ast::lnode<Analyser>::insert(node_ptr<Analyser> node) {
    nodes.insert(std::move(node));
}

template<typename Analyser>
falk::ast::tlnode<Analyser>::tlnode(typename Analyser::Type type):
 tnode<Analyser>{type} { }

template<typename Analyser>
void falk::ast::tlnode<Analyser>::traverse(Analyser& analyser) {
    analyser.analyse(*this);
}

template<typename Analyser>
void falk::ast::tlnode<Analyser>::insert(node_ptr<Analyser> node) {
    nodes.insert(std::move(node));
}

template<size_t Size, typename Analyser>
template<typename... Args,
typename falk::ast::dnode<Size, Analyser>::template enable<Args...>>
falk::ast::dnode<Size, Analyser>::dnode(Args... args):
 nodes{std::move(args)...} { }

template<size_t Size, typename Analyser>
void falk::ast::dnode<Size, Analyser>::traverse(Analyser& analyser) {
    analyser.analyse(*this);
}

template<size_t Size, typename Analyser>
void falk::ast::dnode<Size, Analyser>::insert(node_ptr<Analyser> node) {
    if (size < nodes.size()) {
        nodes[size] = std::move(node);
        ++size;
    }
}

template<size_t Size, typename Analyser>
template<typename... Args,
typename falk::ast::tdnode<Size, Analyser>::template enable<Args...>>
falk::ast::tdnode<Size, Analyser>::tdnode(typename Analyser::Type type,
    Args... args): tnode<Analyser>{type}, nodes{std::move(args)...} { }

template<size_t Size, typename Analyser>
void falk::ast::tdnode<Size, Analyser>::traverse(Analyser& analyser) {
    analyser.analyse(*this);
}

template<size_t Size, typename Analyser>
void falk::ast::tdnode<Size, Analyser>::insert(node_ptr<Analyser> node) {
    if (size < nodes.size()) {
        nodes[size] = std::move(node);
        ++size;
    }
}

