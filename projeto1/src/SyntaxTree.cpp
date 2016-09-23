
#include "SyntaxTree.hpp"
#include "SymbolMap.hpp"

const stx::Traversal stx::Node::IN_ORDER = [](const stx::Node& root, const std::string& value) {
    auto left = root.left_child();
    auto right = root.right_child();
    std::string out;
    if (left) {
        out = static_cast<std::string>(*left);
    }
    out += value;
    if (right) {
        out += static_cast<std::string>(*right);
    }
    return out;
};

const stx::Traversal stx::Node::PRE_ORDER = [](const stx::Node& root, const std::string& value) {
    std::string out = value;
    for (auto& child : root) {
        out += static_cast<std::string>(*child);
    }
    return out;
};

stx::Node::Node(const Traversal& traversal)
 : traversal(traversal) { }

const stx::Node* stx::Node::left_child() const {
    if (children.size() > 0) {
        return children.front().get();
    }
    return nullptr;
}

const stx::Node* stx::Node::right_child() const {
    if (children.size() > 1) {
        return children.back().get();
    }
    return nullptr;
}

// stx::DeclNodePtr stx::Node::declaration(::Type type, const std::string& var_name,
//                                              stx::NodePtr& literal, symbol_map& symbols) {
//     if (!symbols.declare(var_name, type)) {
//         utils::error<Error::MULTIPLE_DEFINITION>();
//     }
//     auto node = std::make_unique<DeclNode>();
//     node->content = utils::to_string(type);
//     auto var_node = stx::Node::create_literal(var_name);
//     if (literal) {
//         auto child = stx::Node::create_operator(stx::Operator::ASSIGN, var_node, literal);
//         node->children.emplace_back(child.release());
//     } else {
//         node->children.emplace_back(var_node.release());
//     }
//     return node;
// }
