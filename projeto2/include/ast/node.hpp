
#ifndef FALK_AST_NODE_HPP
#define FALK_AST_NODE_HPP

#include <memory>
#include <type_traits>
#include "aut/value_holder.hpp"

namespace ast {
    // Magic taken from here:
    // http://stackoverflow.com/questions/1005476/how-to-detect-whether-there-is-a-specific-member-variable-in-class
    template<typename T, bool = std::is_fundamental<T>::value>
    struct has_arity;

    template<typename T>
    struct has_arity<T, true> {
        static constexpr auto value = false;
    };

    template<typename T>
    struct has_arity<T, false> {
        struct Fallback { int arity; };
        struct Derived : T, Fallback { };

        template<typename C, C> struct ChT;

        template<typename C>
        static constexpr void f(ChT<int Fallback::*, &C::arity>*) { }
        
        template<typename C>
        static constexpr int f(...) { return 0; }

        static constexpr auto value =
            !std::is_void<decltype(f<Derived>(0))>();
    }; 


    // This class defines an interface to construct the hole abstract syntax
    // tree. There are 4 methods provided:
    // visit(Analyser&) - pass all information about the node to the
    // analyser.
    // add_subnode(std::shared_ptr<node<Analyser>>) - allows the adition of
    // a subnode.
    // empty() - used to detect empty nodes, usually skipped in semantic
    // analysis.
    // size() - returns the number of subnodes.
    template<typename Analyser>
    class node {
     public:
        virtual void visit(Analyser&) = 0;
        virtual void add_subnode(std::shared_ptr<node<Analyser>>) = 0;
        virtual bool empty() { return false; }
        virtual size_t size() const = 0;
    };

    // This class allows to create a node holding any kind of value.
    // That way, is possible to retrieve pure values previously stored
    // in syntax analysis. The visit() method will pass the pure value
    // to analyser along with it's children, if any.
    // The deduction of how many children a node can have is done through
    // a method called arity(). If a value has this method,
    // it can have children. If arity() returns a positive value, it's children
    // will be holded in an array, otherwise, a list.
    template<typename Analyser, typename T, bool = has_arity<T>::value>
    class model;

    // This specialization captures values without children.
    template<typename Analyser, typename T>
    class model<Analyser, T, false> : public node<Analyser> {
        using node_ptr = std::shared_ptr<node<Analyser>>;
     public:
        model(const T& d) : data{d} { }
        void visit(Analyser& analyser) override {
            analyser.analyse(data);
        }
        void add_subnode(node_ptr node) override { }
        size_t size() const override { return 0; }
     private:
        T data;
    };

    // This specialization captures values with children.
    template<typename Analyser, typename T>
    class model<Analyser, T, true> : public node<Analyser> {
        using node_ptr = std::shared_ptr<node<Analyser>>;
        using holder = aut::value_holder<node_ptr, T::arity()>;
     public:
        model(const T& d) : data{d} { }
        void visit(Analyser& analyser) override {
            analyser.analyse(data, subnodes.container);
        }
        void add_subnode(node_ptr node) override {
            subnodes.add(std::move(node));
        }

        size_t size() const override { return subnodes.container.size(); }
     private:
        T data;
        holder subnodes;
    };

    // An empty node. All methods are empty, does nothing. No exceptions,
    // no errors. The empty() method returns true.
    template<typename Analyser>
    class empty_node : public node<Analyser> {
     public:
        void visit(Analyser&) override { };
        void add_subnode(std::shared_ptr<node<Analyser>>) override { };
        bool empty() override { return true; }
        size_t size() const override { return 0; }
    };
}

#endif /* FALK_AST_NODE_HPP */
