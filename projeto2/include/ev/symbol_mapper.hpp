
#ifndef FALK_EV_SYMBOL_MAPPER_HPP
#define FALK_EV_SYMBOL_MAPPER_HPP

#include <stack>
#include <unordered_map>

#include "base/types.hpp"
#include "function.hpp"
#include "variable.hpp"

namespace falk {
    namespace ev {
        class symbol_mapper {
            struct scope {
                std::unordered_map<std::string, variable> variables;
                std::unordered_map<std::string, function> functions;
            };
         public:
            symbol_mapper();

            void open_scope();
            void close_scope();

            void declare_function(const std::string&, function);
            void declare_variable(const std::string&, variable);

            function& retrieve_function(const std::string&);
            variable& retrieve_variable(const std::string&);

            bool is_declared(const std::string&) const;
            symbol::type typeof(const std::string&) const;
         private:
            std::stack<scope> scopes;
            std::unordered_map<std::string, symbol::type> symbol_table;
        };

        inline function& symbol_mapper::retrieve_function(const std::string& id) {
            if (symbol_table.count(id)) {
                if (symbol_table.at(id) == symbol::type::FUNCTION) {
                    return scopes.top().functions.at(id);
                } else {
                    // TODO: error
                    // return what?
                }
            } else {
                // TODO: error
                // return what?
            }
        }

        inline variable& symbol_mapper::retrieve_variable(const std::string& id) {
            if (symbol_table.count(id)) {
                if (symbol_table.at(id) == symbol::type::VARIABLE) {
                    return scopes.top().variables.at(id);
                } else {
                    // TODO: error
                    // return what?
                }
            } else {
                // TODO: error
                // return what?
            }
        }

        inline void symbol_mapper::open_scope() {
            scopes.emplace();
        }

        inline void symbol_mapper::close_scope() {
            scopes.pop();
        }

        inline bool symbol_mapper::is_declared(const std::string& id) const {
            return symbol_table.count(id);
        }

        inline symbol::type symbol_mapper::typeof(const std::string& id) const {
            return symbol_table.at(id);
        }
    }
}

#endif /* FALK_EV_SYMBOL_MAPPER_HPP */
