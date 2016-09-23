

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

    struct Traversal {
        virtual std::string operator()(const Node&) const = 0;
    };

    struct InOrderTraversal : public Traversal {
        std::string operator()(const Node&) const override;
    };

    struct PreOrderTraversal : public Traversal {
        std::string operator()(const Node&) const override;
    };

    using NodePtr = std::unique_ptr<Node>;
    using Children = std::list<NodePtr>;
    using TraversalPtr = std::unique_ptr<Traversal>;

    class Node {
     public:
        // struct Mask;
        Node(std::unique_ptr<Traversal> = std::make_unique<InOrderTraversal>());

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

        template<typename T>
        static Node* make_literal(const T&);

        std::string traverse() const;
        operator std::string() const;

     private:
        std::string content;
        Children children;
        TraversalPtr traversal;
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
