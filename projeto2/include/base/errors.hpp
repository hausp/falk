#ifndef ERRORS_HPP
#define ERRORS_HPP

#include <iostream>
#include <unordered_map>
#include "base/types.hpp"

namespace lpi {
    class context;
}

enum class Error {
    ILLEGAL_ASSIGNMENT,
    INCOMPATIBLE_TYPES,
    ARRAY_SIZE_MISMATCH,
    ROW_SIZE_MISMATCH,
    COLUMN_SIZE_MISMATCH,
    MATRIX_MULT_MISMATCH,
    NON_SQUARE_MATRIX,
    ILLEGAL_OPERATION,
    INDEX_OUT_OF_BOUNDS,
    WRONG_COLUMN_COUNT,
    UNDECLARED_VARIABLE,
    UNDECLARED_FUNCTION,
    NOT_A_VARIABLE,
    NOT_A_FUNCTION,
    NON_BOOLEAN_CONDITION,
    REDECLARATION_OF_SYMBOL,
    NOT_A_STRUCTURE,
};

namespace std {
    template<>
    struct hash<falk::type> {
        inline size_t operator()(falk::type type) const {
            return static_cast<int>(type);
        }
    };

    template<>
    struct hash<falk::struct_t> {
        inline size_t operator()(falk::struct_t type) const {
            return static_cast<int>(type);
        }
    };
}

namespace err {
    const std::unordered_map<falk::type, std::string> type_table = {
        {falk::type::REAL, "real"},
        {falk::type::COMPLEX, "complex"},
        {falk::type::BOOL, "boolean"},
    };

    const std::unordered_map<falk::struct_t, std::string> struct_type_table = {
        {falk::struct_t::SCALAR, "scalar"},
        {falk::struct_t::ARRAY, "array"},
        {falk::struct_t::MATRIX, "matrix"},
    };

    void set_context(lpi::context&);
    std::string error_prefix(const std::string&);
    void echo(const std::string&);

    template<Error>
    inline void semantic(falk::struct_t, falk::struct_t);
    template<Error>
    inline void semantic(falk::type, falk::type);
    template<Error>
    inline void semantic(size_t, size_t);
    template<Error>
    inline void semantic(const std::string&);
    template<Error>
    inline void semantic();

    template<>
    inline void semantic<Error::ILLEGAL_ASSIGNMENT>(falk::struct_t lhs,
                                                    falk::struct_t rhs) {
        echo(error_prefix("semantic") + "cannot assign " +
            struct_type_table.at(rhs) + " to " + struct_type_table.at(lhs));
    }

    template<>
    inline void semantic<Error::INCOMPATIBLE_TYPES>(falk::type lhs, falk::type rhs) {
        echo(error_prefix("semantic") + "incompatible types (" +
            type_table.at(lhs) + " and " + type_table.at(rhs) + ")");
    }

    template<>
    inline void semantic<Error::ARRAY_SIZE_MISMATCH>(size_t lhs, size_t rhs) {
        echo(error_prefix("semantic") + "array size mismatch (" +
            std::to_string(lhs) + " and " + std::to_string(rhs) + ")");
    }

    template<>
    inline void semantic<Error::ROW_SIZE_MISMATCH>(size_t lhs, size_t rhs) {
        echo(error_prefix("semantic") + "row count mismatch (" +
            std::to_string(lhs) + " and " + std::to_string(rhs) + ")");
    }

    template<>
    inline void semantic<Error::COLUMN_SIZE_MISMATCH>(size_t lhs, size_t rhs) {
        echo(error_prefix("semantic") + "column count mismatch (" +
            std::to_string(lhs) + " and " + std::to_string(rhs) + ")");
    }

    template<>
    inline void semantic<Error::MATRIX_MULT_MISMATCH>(size_t lhs, size_t rhs) {
        echo(error_prefix("semantic") + "the number of columns of the first " + 
            "matrix (" + std::to_string(lhs) + ") must be equal to the number " +
            "of rows of the second matrix (" + std::to_string(rhs) + ")");
    }

    template<>
    inline void semantic<Error::NON_SQUARE_MATRIX>(size_t lhs, size_t rhs) {
        echo(error_prefix("semantic") + "second matrix must be square (" +
            std::to_string(lhs) + " and " + std::to_string(rhs) + ")");
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
    inline void semantic<Error::UNDECLARED_VARIABLE>(const std::string& name) {
        echo(error_prefix("semantic") + "undeclared variable " + name);
    }

    template<>
    inline void semantic<Error::UNDECLARED_FUNCTION>(const std::string& name) {
        echo(error_prefix("semantic") + "undeclared function " + name);
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

    template<>
    inline void semantic<Error::NOT_A_STRUCTURE>() {
        echo(error_prefix("semantic") + "expected array or matrix, got scalar instead");
    }
}

#endif /* ERRORS_HPP */
