

#ifndef POLSKA_NODE_HPP
#define POLSKA_NODE_HPP

#include <list>
#include <memory>
#include <ostream>
#include <string>
#include "utils.hpp"

namespace stx {
    enum class Operator : char {
        PLUS = '+',
        MINUS = '-',
        TIMES = '*',
        DIVIDE = '/',
        PAR = '(',
        ASSIGN = '=',
        DECLARE = 'v'
    };

    class Node;

    using NodePtr = std::unique_ptr<Node>;
    using Children = std::list<NodePtr>;
    using Traversal = std::function<std::string(const Node&, const std::string&)>;


    class Node {
     public:
        static const Traversal IN_ORDER;
        static const Traversal PRE_ORDER;
        // struct Mask;
        Node(const Traversal& = IN_ORDER);

        // Mask left_children() const;
        // Mask right_children() const;

        const Node* left_child() const;
        const Node* right_child() const;

        Children::iterator begin() { return children.begin(); }
        Children::const_iterator begin() const { return children.cbegin(); }
        Children::iterator end() { return children.end(); }
        Children::const_iterator end() const { return children.cend(); }

        void set_content(const std::string&);

        template<typename... Nodes>
        void set_children();
        
        template<typename... Nodes>
        void set_children(NodePtr, Nodes&&...);

        template<typename... Nodes>
        static Node* make_operator(Operator, Nodes&&...);

        template<typename... Nodes>
        static Node* make_assignment(Nodes&&...);

        template<typename T>
        static Node* make_literal(const T&);

        operator std::string() const;

     private:
        std::string content;
        Children children;
        Traversal traversal;
        // std::list<NodePtr>::const_iterator middle;
        // short middle_counter = 0;
    };

    // struct Node::Mask {
    //     std::list<NodePtr>::const_iterator begin;
    //     std::list<NodePtr>::const_iterator end;

    //     // std::list<NodePtr>::const_iterator begin() const { return first; }
    //     // std::list<NodePtr>::const_iterator end() const { return limit; }
    // };

    // struct DeclNode : public Node {
    //     operator std::string() const override;
    // };
    
    // struct InitNode : public Node {
    //     operator std::string() const override;
    // };
}

#include "SyntaxTree.ipp"

#endif /* POLSKA_NODE_HPP */
