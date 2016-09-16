
template<typename... Nodes>
polska::NodePtr polska::Node::create(Operator op, Nodes... children) {
    constexpr size_t num = sizeof...(children);
    auto node = std::make_unique<Node>(num);
    node->type = Type::OPERATOR;
    node->content = static_cast<char>(op);
    set_children(node, 0, children...);
    return node;
}

template<typename...>
void polska::Node::set_children(NodePtr, size_t) {}

template<typename... Nodes>
void polska::Node::set_children(NodePtr node, size_t c, NodePtr first, Nodes... children) {
    node->children[c].reset(first);
    set_children(node, c+1, children...);
}
