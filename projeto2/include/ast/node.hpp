
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

        static constexpr auto value = !std::is_void<decltype(f<Derived>(0))>();
    }; 

    template<typename Analyser>
    class node {
     public:
        virtual void traverse(Analyser&) = 0;
        virtual void add_subnode(std::shared_ptr<node<Analyser>>) = 0;
        virtual bool empty() { return false; }
    };

    template<typename Analyser, typename T, bool = has_arity<T>::value>
    class model;

    template<typename Analyser, typename T>
    class model<Analyser, T, false> : public node<Analyser> {
     public:
        model(const T& d) : data{d} { }
        void traverse(Analyser& analyser) override {
            analyser.analyse(data);
        }
        void add_subnode(std::shared_ptr<node<Analyser>>) override { }
     private:
        T data;
    };

    template<typename Analyser, typename T>
    class model<Analyser, T, true> : public node<Analyser> {
        using node_ptr = std::shared_ptr<node<Analyser>>;
        using holder = aut::value_holder<node_ptr, T::arity()>;
     public:
        model(const T& d) : data{d} { }
        void traverse(Analyser& analyser) override {
            analyser.analyse(data, operands.container);
        }
        void add_subnode(std::shared_ptr<node<Analyser>> node) override {
            operands.add(std::move(node));
        }
     private:
        T data;
        holder operands;
    };

    template<typename Analyser>
    class empty_node : public node<Analyser> {
     public:
        void traverse(Analyser&) override { };
        void add_subnode(std::shared_ptr<node<Analyser>>) override { };
        bool empty() override { return true; }
    };
}

#endif /* FALK_AST_NODE_HPP */
