#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <string>
#include "LineCounter.hpp"

enum class Type {
    INT
};

enum class Operator : char {
    PLUS = '+',
    MINUS = '-',
    TIMES = '*',
    DIVIDE = '/',
    PAR = '(',
    DECLARE = 'v'
};

enum class Error {
    MULTIPLE_DEFINITION,
    UNDECLARED_VARIABLE
};

namespace utils {
    class line_counter {
     public:
        static line_counter& instance() {
            static line_counter inst;
            return inst;
        }

        size_t value() const { return val; }
        line_counter& operator++() {
            ++val;
            return *this;
        }

     private:
        size_t val = 1;
        line_counter() = default;
    };

    inline line_counter& counter() {
        return line_counter::instance();
    }

    template<typename T>
    inline std::string to_string(const T& value) {
        return std::to_string(value);
    }

    inline std::string to_string(Type type) {
        return "int";
    }

    inline std::string to_string(const std::string& value) {
        return value;
    }


    inline std::string to_string(const char* value) {
        return value;
    }

    template<typename T>
    inline void echo(const T& value) {
        std::cout << value << std::endl;
    }

    inline std::string error_prefix(const std::string& type) {
        auto line = std::to_string(counter().value());
        return "[Line " + line + "] " + type + " error: ";
    }

    template<Error err>
    inline void semantic_error(const std::string&);

    template<>
    inline void semantic_error<Error::MULTIPLE_DEFINITION>(const std::string& name) {
        echo(error_prefix("semantic") + "re-declaration of variable " + name);
    }

    template<>
    inline void semantic_error<Error::UNDECLARED_VARIABLE>(const std::string& name) {
        echo(error_prefix("semantic") + "undeclared variable " + name);
    }
}

#endif /* UTILS_HPP */
