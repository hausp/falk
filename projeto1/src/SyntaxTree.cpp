
#include "SyntaxTree.hpp"
#include "symbol_map.hpp"

// polska::NodePtr polska::Node::create(const std::string& value) {
//     auto node = std::make_unique<Node>(0);
//     node->type = Type::OPERAND;
//     node->content = value;
//     return node;
// }

// polska::NodePtr polska::Node::create(const std::string& var, const std::string& value) {
// 	auto node = std::unique_ptr<Node>(new InitNode(2));
// 	node->content = static_cast<char>(polska::Operator::ASSIGN);
// 	node->children[0].reset(create(var).release());
// 	node->children[1].reset(create(value).release());
// 	return node;
// }

polska::DeclNodePtr polska::Node::declaration(::Type type, const std::string& var_name,
                                             polska::NodePtr literal, symbol_map& symbols) {
    if (!symbols.declare(var_name, type)) {
        utils::error<Error::MULTIPLE_DEFINITION>();
    }
    auto node = std::make_unique<DeclNode>();
    node->content = utils::to_string(type);
    auto var_node = polska::Node::create_literal(var_name);
    if (literal) {
        auto child = polska::Node::create_operator(polska::Operator::ASSIGN, var_node, literal);
        node->children.emplace_back(child.release());
    } else {
        node->children.emplace_back(var_node.release());
    }
    return node;
}
