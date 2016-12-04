
#ifndef ASZDRICK_VALUE_HOLDER_HPP
#define ASZDRICK_VALUE_HOLDER_HPP

#include "utilities.hpp"

namespace aut {
    template<typename T, int64_t S, bool = is_positive<S>::value>
    struct value_holder;

    template<typename T, int64_t S>
    struct value_holder<T, S, true> {
        using Type = std::array<T, S>;
        Type container;

        template<typename... Targs>
        value_holder(Targs...);
        bool add(T u);
        bool empty() const;
        T last() const;

     private:
        size_t size = 0;
    };

    template<typename T>
    struct value_holder<T, 0, false> {
        using Type = void;

        bool add(T u) { return false; }
        bool empty() const { return false; }
        T last() const { return T(); }
    };

    template<typename T, int64_t S>
    struct value_holder<T, S, false> {
        value_holder();
        template<typename... Targs>
        value_holder(Targs...);
        bool add(T u);
        bool empty() const;
        T last() const;
        
        using Type = std::list<T>;
        Type container;
    };
}

#include "value_holder.ipp"

#endif /* ASZDRICK_VALUE_HOLDER_HPP */
