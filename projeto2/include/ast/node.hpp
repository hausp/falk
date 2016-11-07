
#ifndef FALK_AST_NODE_HPP
#define FALK_AST_NODE_HPP

#include <array>
#include <list>
#include <memory>

namespace falk {
    namespace ast {
        template<typename Analyser>
        class node {
         public:
            virtual ~node();
            virtual void traverse(Analyser&) = 0;
        };

        template<typename Analyser>
        class tnode {
            friend Analyser;
         public:
            tnode(typename Analyser::Type);
            virtual ~tnode();
            virtual void traverse(Analyser&) = 0;
         private:
            typename Analyser::Type type;
        };

        template<typename Analyser>
        using node_ptr = std::unique_ptr<node<Analyser>>;

        template<typename Analyser>
        using tnode_ptr = std::unique_ptr<tnode<Analyser>>;

        template<typename Analyser>
        class lnode : public node<Analyser> {
            friend Analyser;
         public:
            virtual void traverse(Analyser&);
            virtual void insert(node_ptr<Analyser>);
         private:
            std::list<node_ptr<Analyser>> nodes;
        };

        template<typename Analyser>
        class tlnode : public tnode<Analyser> {
            friend Analyser;
         public:
            tlnode(typename Analyser::Type);
            virtual void traverse(Analyser&);
            virtual void insert(node_ptr<Analyser>);
         private:
            std::list<tnode_ptr<Analyser>> nodes;
        };

        template<size_t Size, typename Analyser>
        class dnode : public node<Analyser> {
            friend Analyser;
            template<typename... Args>
            using enable = std::enable_if_t<sizeof...(Args) == Size, int>;
         public:
            template<typename... Args, enable<Args...> = 0>
            dnode(Args...);
            virtual void traverse(Analyser&);
            virtual void insert(node_ptr<Analyser>);
         private:
            std::array<tnode_ptr<Analyser>, Size> nodes;
            size_t size = 0;
        };

        template<size_t Size, typename Analyser>
        class tdnode : public tnode<Analyser> {
            friend Analyser;
            template<typename... Args>
            using enable = std::enable_if_t<sizeof...(Args) == Size, int>;
         public:
            template<typename... Args, enable<Args...> = 0>
            tdnode(typename Analyser::Type, Args...);
            virtual void traverse(Analyser&);
            virtual void insert(node_ptr<Analyser>);
         private:
            std::array<tnode_ptr<Analyser>, Size> nodes;
            size_t size = 0;
        };
    }
}

#include "node.ipp"

#endif /* FALK_AST_NODE_HPP */
