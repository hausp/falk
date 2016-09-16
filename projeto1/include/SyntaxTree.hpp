

#ifndef POLSKA_NODE_HPP
#define POLSKA_NODE_HPP

#include <memory>
#include <ostream>
#include <string>
#include <vector>

namespace polska {
    enum class Operator : char {
        PLUS = '+',
        MINUS = '-',
        TIMES = '*',
        DIVIDE = '/',
        PAR = '(',
        ASSIGN = '='
    }

    struct Node;
    using NodePtr = std::unique_ptr<Node>;

    struct Node {
        enum class Type { OPERAND, OPERATOR };
        Node(size_t);
        std::string content;
        Type type;
        std::vector<NodePtr> children;

        static NodePtr create(Operator);

        template<typename... Nodes>
        static NodePtr create(Operator, Nodes...);

        template<typename... Nodes>
        void set_children(NodePtr, size_t);

        template<typename... Nodes>
        void set_children(NodePtr, size_t, NodePtr, Nodes...);
    };

    inline std::ostream& operator<<(std::ostream& stream, const Node& root) {
        stream << root.content;
        for (auto& child : root.children) {
            stream << child;
        }
        return stream;
    }
}

#include "SyntaxTree.ipp"

#endif /* POLSKA_NODE_HPP */
