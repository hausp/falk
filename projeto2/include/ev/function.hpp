
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
            using node = ast::node<evaluator>;
            using node_ptr = std::shared_ptr<node>;
         public:
            function(parameters params, node_ptr node):
              _code{std::move(node)}, _params{std::move(params)}, fail{false} { }

            function(bool flag = false): fail{flag} { }

            bool error() const { return fail; }

            const parameters& params() const { return _params; }
            parameters& params() { return _params; }

            node_ptr& code() { return _code; }
         private:
            node_ptr _code;
            parameters _params;
            bool fail;
        };
    }
}

#endif /* FALK_EV_FUNCTION_HPP */
