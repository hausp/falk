

#ifndef SYNTAX_TREE_HPP
#define SYNTAX_TREE_HPP

#include <memory>

class SyntaxTree {
 public:
 	class Node;
 	enum class Type { OPERAND, OPERATOR };

 	void emplace(const std::string&, unsigned, Type);

 private:
 	std::unique_ptr<Node> root;
};

class SyntaxTree::Node {
 public:
 	Node(const std::string&, unsigned, Type);
 private:
 	std::string content;
 	unsigned priority;
 	Type type;
 	std::unique_ptr<Node> left;
 	std::unique_ptr<Node> right;
};

#endif /* SYNTAX_TREE_HPP */
