
#ifndef FALK_ACTIONS_HPP
#define FALK_ACTIONS_HPP

#include "types.hpp"
#include "ast/rvalue.hpp"

namespace falk {
    namespace ev {
        class evaluator;
    }
    
    struct block {
        static constexpr int arity() { return -1; }
    };

    struct conditional {
        static constexpr size_t arity() { return 3; }
    };

    template<symbol::type Type>
    struct declare {
        static constexpr size_t arity() { return 1; }
        
        std::string id;
        bool deduce_type;
        structural::type s_type;
        fundamental::type f_type;
    };

    struct loop {
        static constexpr size_t arity() { return 2; }
    };

    struct ret {
        ast::rvalue<ev::evaluator> value;
    };

    struct valueof {
        static constexpr size_t arity() { return 1; }
    };

    struct var_id {
        static constexpr size_t arity() { return 2; }

        std::string id;
        std::pair<int64_t, int64_t> index = {-1, -1};
    };

    struct create_structure {
        static constexpr int arity() { return -1; }
    };

    struct parameter {
        var_id vid;
        structural::type s_type;
    };

    using parameters = std::vector<falk::parameter>;
    using declare_variable = declare<symbol::type::VARIABLE>;
    using declare_function = declare<symbol::type::FUNCTION>;
}

#endif /* FALK_ACTIONS_HPP */
