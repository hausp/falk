
#ifndef FALK_CONSTRUCTS_HPP
#define FALK_CONSTRUCTS_HPP

#include "types.hpp"

namespace falk {
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

    struct identifier {
        std::string name;
        symbol::type type;
    };

    struct valueof {
        identifier id;
    };
}

#endif /* FALK_CONSTRUCTS_HPP */
