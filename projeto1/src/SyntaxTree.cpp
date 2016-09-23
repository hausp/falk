
#include "SyntaxTree.hpp"
#include "SymbolMap.hpp"

stx::Node::Node(std::unique_ptr<Traversal> traversal)
 : traversal(std::move(traversal)) { }

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

std::string stx::InOrderTraversal::operator()(const stx::Node& root) const {
    std::string out;
    auto left = root.left_child();
    auto right = root.right_child();
    if (left) {
        out += operator()(*left);
    }
    out += root;
    if (right) {
        out += operator()(*right);
    }
    return out;
}

std::string stx::PreOrderTraversal::operator()(const stx::Node& root) const {
    std::string out = root;
    for (auto& child : root) {
        out += operator()(*child);
    }
    return out;
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
