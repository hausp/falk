

#include "SyntaxTree.hpp"


void SyntaxTree::emplace(const std::string& content, unsigned p, Type type) {
	if (!root) {
		root.reset(new Node(content, p, type));
	}
}

SyntaxTree::Node::Node(const std::string& content, unsigned p, Type type)
 : content(content), priority(p), type(type) {

}