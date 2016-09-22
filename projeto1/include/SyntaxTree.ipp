namespace {
    template<typename... Nodes>
    void aux(polska::DeclNode& node, polska::InNodePtr first, Nodes&&... nodes) {
        node.children.push_back(polska::NodePtr(first.release()));
        aux(node, std::forward<Nodes>(nodes)...);
    }
}

template<typename T>
polska::NodePtr polska::Node::create_literal(const T& value) {
    auto node = std::make_unique<Node>();
    node->type = Type::OPERAND;
    node->content = utils::to_string(value);
    return node;
}

template<typename... Nodes>
polska::NodePtr polska::Node::create_operator(Operator op, Nodes&&... child_list) {
    auto node = std::make_unique<Node>();
    node->type = Type::OPERATOR;
    node->content = static_cast<char>(op);
    node->set_children(std::forward<Nodes>(child_list)...);
    return node;
}

template<typename...>
void polska::Node::set_children() {}

template<typename... Nodes>
void polska::Node::set_children(NodePtr& first, Nodes&&... child_list) {
    children.emplace_back(first.release());
    set_children(std::forward<Nodes>(child_list)...);
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
    std::string out(*children.front());
    out += " " + content + " ";
    out += **std::next(children.begin());
    return out;
}

inline std::ostream& operator<<(std::ostream& stream, const polska::Node& root) {
    return stream << std::string(root);
}
