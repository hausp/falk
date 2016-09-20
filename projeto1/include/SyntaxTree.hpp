

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
        ASSIGN = '=',
        DECLARE = 'v'
    }

    struct Node;
    struct DeclNode;
    struct InitNode;

    using NodePtr = std::unique_ptr<Node>;
    using InNodePtr = std::unique_ptr<InitNode>;

    struct Node {
        enum class Type { OPERAND, OPERATOR };
        Node(size_t);
        std::string content;
        Type type;
        std::vector<NodePtr> children;

        static NodePtr create() {}
        static NodePtr create(Operator);

        template<typename, typename... Nodes>
        static NodePtr create(const std::string&, Nodes&&...);

        static NodePtr create(const std::string&, const std::string&);

        template<typename... Nodes>
        static NodePtr create(Operator, Nodes&&...);

        template<typename... Nodes>
        void set_children(NodePtr);
        
        template<typename... Nodes>
        void set_children(NodePtr, NodePtr, Nodes&&...);

        
        virtual operator std::string() const;
    };

    struct DeclNode : public Node {
        operator std::string() const override;
    };
    
    struct InitNode : public Node {
        operator std::string() const override;
    };
}

#include "SyntaxTree.ipp"

#endif /* POLSKA_NODE_HPP */
