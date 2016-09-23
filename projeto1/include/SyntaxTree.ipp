// namespace {
//     template<typename... Nodes>
//     void aux(stx::DeclNode& node, stx::InNodePtr first, Nodes&&... nodes) {
//         node.children.push_back(stx::NodePtr(first.release()));
//         aux(node, std::forward<Nodes>(nodes)...);
//     }
// }

#include "macros.hpp"

template<typename T>
stx::Node* stx::Node::make_literal(const T& value) {
    auto node = new Node();
    node->content = utils::to_string(value);
    return node;
}

template<typename... Nodes>
stx::Node* stx::Node::make_operator(Operator op, Nodes&&... child_list) {
    auto node = new Node(PRE_ORDER);
    node->content = static_cast<char>(op);
    node->set_children(std::forward<Nodes>(child_list)...);
    return node;
}

template<typename... Nodes>
stx::Node* stx::Node::make_assignment(Nodes&&... child_list) {
    try {
        return make_operator(Operator::ASSIGN, std::forward<Nodes>(child_list)...);
    } catch (utils::error&) {
        return new Node();
    }
}

template<typename...>
void stx::Node::set_children() {}

template<typename... Nodes>
void stx::Node::set_children(NodePtr first, Nodes&&... child_list) {
    if (!first) {
        throw utils::error();
    }
    children.emplace_back(first.release());
    set_children(std::forward<Nodes>(child_list)...);
}

inline void stx::Node::set_content(const std::string& value) {
    content = value;
}

inline stx::Node::operator std::string() const {
    return traversal(*this, content + " ");
}

inline std::ostream& operator<<(std::ostream& stream, const stx::Node& root) {
    return stream << static_cast<std::string>(root);
}

// inline stx::DeclNode::operator std::string() const {
//     std::string out(content);
//     out += " var: ";
//     size_t i = 0;
//     for (auto& child : children) {
//         if (i > 0) {
//             out += ", ";
//         }
//         out += *child;
//         ++i;
//     }
//     return out;
// }

// inline stx::InitNode::operator std::string() const {
//     std::string out(*children.front());
//     out += " " + content + " ";
//     out += **std::next(children.begin());
//     return out;
// }

