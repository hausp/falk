

#ifndef POLSKA_NODE_HPP
#define POLSKA_NODE_HPP

#include <list>
#include <memory>
#include <ostream>
#include <string>
#include "utils.hpp"

class symbol_map;

namespace polska {
    enum class Operator : char {
        PLUS = '+',
        MINUS = '-',
        TIMES = '*',
        DIVIDE = '/',
        PAR = '(',
        ASSIGN = '=',
        DECLARE = 'v'
    };

    struct Node;
    struct DeclNode;
    struct InitNode;

    using NodePtr = std::unique_ptr<Node>;
    using DeclNodePtr = std::unique_ptr<DeclNode>;
    using InNodePtr = std::unique_ptr<InitNode>;

    struct Node {
        enum class Type { OPERAND, OPERATOR };
        std::string content;
        Type type;
        std::list<NodePtr> children;

        template<typename T>
        static NodePtr create_literal(const T&);

        template<typename... Nodes>
        static NodePtr create_operator(Operator, Nodes&&...);

        template<typename... Nodes>
        void set_children();
        
        template<typename... Nodes>
        void set_children(NodePtr&, Nodes&&...);

        static DeclNodePtr declaration(::Type, const std::string&, NodePtr&, symbol_map&);

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
