#ifndef ASZDRICK_UTILITIES_HPP
#define ASZDRICK_UTILITIES_HPP

#include <array>
#include <list>
#include <type_traits>

namespace aut {
    template<int64_t S>
    struct is_positive {
        static constexpr auto value = S > 0;
    };

    template<size_t...>
    struct maxof;

    template<size_t Last>
    struct maxof<Last> {
        static constexpr auto value = Last;
    };

    template<size_t First, size_t Second, size_t... Others>
    struct maxof<First, Second, Others...> {
        static constexpr auto value =
            First >= Second ? maxof<First, Others...>::value
                            : maxof<Second, Others...>::value;
    };

    template<typename T, typename... Args>
    struct is_oneof;

    template<typename T, typename Last>
    struct is_oneof<T, Last> {
        static constexpr auto value = std::is_same<T, Last>::value;
    };

    template<typename T, typename First, typename... Others>
    struct is_oneof<T, First, Others...> {
        static constexpr auto value =
            std::is_same<T, First>::value || is_oneof<T, Others...>::value;
    };
}

#endif /* ASZDRICK_UTILITIES_HPP */