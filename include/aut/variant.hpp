
#ifndef ASZDRICK_VARIANT_HPP
#define ASZDRICK_VARIANT_HPP

#include <memory>
#include <type_traits>
#include <utility>

#include "utilities.hpp"

namespace aut {
    template<typename... Ts>
    class variant;

    class abstract_holder {
     public:
        virtual ~abstract_holder() { }
    };

    template<typename T>
    class holder : public abstract_holder {
        template<typename...>
        friend class variant;
     public:
        holder(T obj):
          object{std::move(obj)} { }
        ~holder() { }
     private:
        T object;
    };

    template<typename... Ts>
    class variant {
        template<typename T>
        using is_valid_type = std::enable_if_t<aut::is_oneof<T, Ts...>::value, T>;
     public: 
        variant() = default;

        template<typename T, typename = is_valid_type<T>>
        variant(T value):
          data{new holder<T>{value}},
          type_code{typeid(T).hash_code()} { }

        template<typename T>
        bool is() {
            return (type_code == typeid(T).hash_code());
        }

        bool valid() {
            return (type_code != typeid(void));
        }

        template<typename T>
        T& value() {
            return dynamic_cast<holder<T>*>(data.get())->object;
        }

        template<typename T>
        const T& value() const {
            return dynamic_cast<holder<T>*>(data.get())->object;
        }

     private:
        std::unique_ptr<abstract_holder> data;
        size_t type_code = typeid(void).hash_code();
    };
}
#endif /* ASZDRICK_VARIANT_HPP */
