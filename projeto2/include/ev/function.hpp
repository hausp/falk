
#ifndef FALK_EV_FUNCTION_HPP
#define FALK_EV_FUNCTION_HPP

#include <vector>
#include "ast/list.hpp"
#include "base/actions.hpp"
// #include "evaluator.hpp"

namespace falk {
    namespace ev {
        class evaluator;
        // some black magic to create callable user-defined functions
        class function {
         public:
            function(parameters params, ast::list<evaluator> node):
              _code{std::move(node)}, _params{std::move(params)}, fail{false} { }

            function(bool flag = false): fail{flag} { }

            // void add_param(falk::parameter p) { _params.push_back(p); }

            bool error() const { return fail; }

            const parameters& params() const { return _params; }
            parameters& params() { return _params; }

            ast::list<evaluator>& code() { return _code; }
         private:
            ast::list<evaluator> _code;
            parameters _params;
            bool fail;
        };
    }
}

#endif /* FALK_EV_FUNCTION_HPP */
