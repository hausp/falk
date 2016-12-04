
#ifndef FALK_ACTIONS_HPP
#define FALK_ACTIONS_HPP

#include "types.hpp"
#include "ev/variable.hpp"

namespace falk {
    
    struct block {
        static constexpr int arity() { return -1; }
    };

    struct conditional {
        static constexpr size_t arity() { return 3; }
    };

    struct declare_variable {
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
        static constexpr size_t arity() { return 1; }
    };

    struct valueof {
        static constexpr size_t arity() { return 1; }
    };

    struct var_id {
        static constexpr size_t arity() { return 2; }

        std::string id;
        std::pair<int64_t, int64_t> index = {-1, -1};
    };

    struct fun_id {
        static constexpr size_t arity() { return 1; }

        std::string id;
        size_t number_of_params;
    };

    struct create_structure {
        static constexpr int arity() { return -1; }
    };

    struct parameter {
        var_id vid;
        structural::type s_type;
    };

    using parameters = std::vector<falk::parameter>;

    struct declare_function {
        static constexpr size_t arity() { return 1; }
        
        std::string id;
        parameters params;
    };

    struct print {
        static constexpr size_t arity() { return 1; }

        template<typename T>
        ev::variable operator()(const T& value, structural::type type) const {
            std::cout << "res = " << value << std::endl;
            return {value, type};
        }
    };
}

#endif /* FALK_ACTIONS_HPP */
