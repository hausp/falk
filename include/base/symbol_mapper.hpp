
#ifndef FALK_EV_SYMBOL_MAPPER_HPP
#define FALK_EV_SYMBOL_MAPPER_HPP

#include <stack>
#include <unordered_map>

#include "errors.hpp"
#include "types.hpp"
#include "types/function.hpp"
#include "types/variable.hpp"

namespace {
    struct scope {
        std::unordered_map<std::string, falk::variable> variables;
        std::unordered_map<std::string, falk::function> functions;
        std::unordered_map<std::string, falk::symbol::type> symbol_table;
    };
}

namespace falk {
    class symbol_mapper {
     public:
        symbol_mapper();

        void open_scope();
        void close_scope();

        void declare_function(const std::string&, function);
        void declare_variable(const std::string&, variable);

        void undefine_function(const std::string&);

        function& retrieve_function(const std::string&);
        variable& retrieve_variable(const std::string&);

        bool is_declared(const std::string&) const;
        scope& scope_of(const std::string& id);
        symbol::type type_of(const std::string&) const;

        void update_result(variable);
     private:
        std::list<scope> scopes;
    };
}

#endif /* FALK_EV_SYMBOL_MAPPER_HPP */
