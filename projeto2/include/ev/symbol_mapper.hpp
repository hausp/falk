
#ifndef FALK_EV_SYMBOL_MAPPER_HPP
#define FALK_EV_SYMBOL_MAPPER_HPP

#include <stack>
#include <unordered_map>

#include "base/errors.hpp"
#include "base/types.hpp"
#include "function.hpp"
#include "variable.hpp"

namespace falk {
    namespace ev {
        class symbol_mapper {
            struct scope {
                std::unordered_map<std::string, variable> variables;
                std::unordered_map<std::string, function> functions;
                std::unordered_map<std::string, symbol::type> symbol_table;
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
            scope& scope_of(const std::string& id);
            symbol::type type_of(const std::string&) const;
         private:
            std::list<scope> scopes;
        };
    }
}

#endif /* FALK_EV_SYMBOL_MAPPER_HPP */
