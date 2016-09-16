

#include "SyntaxTree.hpp"

polska::Node::Node(size_t children) : children(children) {}

polska::NodePtr polska::Node::create(const std::string& value) {
    auto node = std::make_unique<Node>(0);
    node->type = Type::OPERAND;
    node->content = value;
    return node;
}
