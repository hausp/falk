#ifndef ERRORS_HPP
#define ERRORS_HPP

#include <iostream>

enum class Error {
    INCOMPATIBLE_TYPES,
    INCOMPATIBLE_OPERANDS,
    ILLEGAL_OPERATION,
    INDEX_OUT_OF_BOUNDS,
    WRONG_COLUMN_COUNT,
    UNDEFINED_VARIABLE,
    UNDEFINED_FUNCTION,
    NOT_A_VARIABLE,
    NOT_A_FUNCTION,
    NON_BOOLEAN_CONDITION,
    REDECLARATION_OF_SYMBOL,
};

namespace err {
    template<Error>
    inline void semantic(size_t, size_t);
    template<Error>
    inline void semantic(const std::string&);
    template<Error>
    inline void semantic();

    inline std::string error_prefix(const std::string& type) {
        auto line = std::to_string(0); // TODO
        return "[Line " + line + "] " + type + " error: ";
    }

    inline void echo(const std::string& message) {
        std::cout << message << std::endl;
    }

    template<>
    inline void semantic<Error::INDEX_OUT_OF_BOUNDS>(size_t limit, size_t actual) {
        echo(error_prefix("semantic") + "index out of bounds (limit " +
            std::to_string(limit) + ", actual = " + std::to_string(actual) + ")");
    }

    template<>
    inline void semantic<Error::WRONG_COLUMN_COUNT>(size_t expected, size_t actual) {
        echo(error_prefix("semantic") + "mismatching column count (expected " +
            std::to_string(expected) + ", got " + std::to_string(actual) + ")");
    }

    template<>
    inline void semantic<Error::UNDEFINED_VARIABLE>(const std::string& name) {
        echo(error_prefix("semantic") + "undefined variable " + name);
    }

    template<>
    inline void semantic<Error::UNDEFINED_FUNCTION>(const std::string& name) {
        echo(error_prefix("semantic") + "undefined function " + name);
    }

    template<>
    inline void semantic<Error::NOT_A_VARIABLE>(const std::string& name) {
        echo(error_prefix("semantic") + name + " is not a variable");
    }

    template<>
    inline void semantic<Error::NOT_A_FUNCTION>(const std::string& name) {
        echo(error_prefix("semantic") + name + " is not a function");
    }

    template<>
    inline void semantic<Error::REDECLARATION_OF_SYMBOL>(const std::string& name) {
        echo(error_prefix("semantic") + "re-declaration of symbol " + name);
    }

    template<>
    inline void semantic<Error::ILLEGAL_OPERATION>(const std::string& extra) {
        echo(error_prefix("semantic") + "illegal operation: " + extra);
    }

    template<>
    inline void semantic<Error::ILLEGAL_OPERATION>() {
        echo(error_prefix("semantic") + "illegal operation");
    }

    template<>
    inline void semantic<Error::NON_BOOLEAN_CONDITION>() {
        echo(error_prefix("semantic") + "non-boolean condition");
    }
}

#endif /* ERRORS_HPP */
