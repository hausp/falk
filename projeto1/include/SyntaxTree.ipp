namespace {
    template<typename... Nodes>
    void aux(DeclNode& node, InNodePtr first, Nodes&&... nodes) {
        node.children.push_back(first.release());
        aux(node, std::forward<Nodes>(nodes)...);
    }
}

template<typename... Nodes>
polska::NodePtr polska::Node::create(Operator op, Nodes&&... children) {
    constexpr static auto num = sizeof...(children);
    auto node = std::make_unique<Node>(num);
    node->type = Type::OPERATOR;
    node->content = static_cast<char>(op);
    set_children(*node, std::forward<Nodes>(children)...);
    return node;
}

template<typename NodeType, typename... Nodes>
static NodePtr polska::Node::create(const std::string& type, Nodes&&... children) {
    constexpr static auto num = sizeof...(children);
    auto result = std::make_unique<NodeType>(num);
    result->content = type;
    aux(*result, std::forward<Nodes>(children)...);
    return result;
}

template<typename...>
void polska::Node::set_children(Node&, size_t) {}

template<typename... Nodes>
void polska::Node::set_children(Node& node, size_t c, NodePtr first, Nodes&&... children) {
    node.children[c].reset(first);
    set_children(node, c+1, children...);
}

inline polska::Node::operator std::string() const {
    std::string out(content);
    for (auto& child : children) {
        out += *child;
    }
    return out;
}

inline polska::DeclNode::operator std::string() const {
    std::string out(content);
    out += " var: ";
    size_t i = 0;
    for (auto& child : children) {
        if (i > 0) {
            out += ", ";
        }
        out += *child;
        ++i;
    }
    return out;
}

inline polska::InitNode::operator std::string() const {
    std::string out(*children[0]);
    out += " " + content + " ";
    out += *children[1];
    return out;
}

inline std::ostream& operator<<(std::ostream& stream, const Node& root) {
    return stream << std::string(root);
}
