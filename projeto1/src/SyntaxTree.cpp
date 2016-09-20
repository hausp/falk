

#include "SyntaxTree.hpp"

polska::Node::Node(size_t children) : children(children) {}

polska::NodePtr polska::Node::create(const std::string& value) {
    auto node = std::make_unique<Node>(0);
    node->type = Type::OPERAND;
    node->content = value;
    return node;
}

NodePtr polska::Node::create(const std::string& var, const std::string& value) {
	auto node = std::unique_ptr<Node>(new InitNode(2));
	node->content = static_cast<char>(polska::Operator::ASSIGN);
	node->children[0].reset(create(var));
	node->children[1].reset(create(value));
	return node;
}
