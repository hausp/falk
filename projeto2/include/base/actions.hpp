
#ifndef FALK_ACTIONS_HPP
#define FALK_ACTIONS_HPP

#include "types.hpp"

namespace falk {
    using identifier = std::string;

    struct block {
        static constexpr int arity() {
            return -1;
        }
    };

    struct conditional {
        static constexpr size_t arity() {
            return 3;
        }
    };

    template<symbol::type>
    struct declare;

    template<>
    struct declare<symbol::type::VARIABLE> {
        static constexpr size_t arity() { return 1; }
        
        identifier id;
        structural::type s_type;
        fundamental::type f_type;
    };

    struct loop {
        static constexpr size_t arity() {
            return 2;
        }
    };

    struct valueof {
        identifier id;
    };

    struct index_access {
        static constexpr size_t arity() {
            return 3;
        }
    };

    struct retrieve {
        static constexpr size_t arity() {
            return 3;
        }
    };

    using declare_variable = falk::declare<symbol::type::VARIABLE>;
}

#endif /* FALK_ACTIONS_HPP */
