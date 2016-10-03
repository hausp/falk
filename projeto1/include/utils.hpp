#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <string>
#include <unordered_map>

enum class PrimitiveType {
    INT, FLOAT, BOOL, VOID, ANY
};

enum class Operator {
    EQUAL,
    NOT_EQUAL,
    GREATER_THAN,
    LESS_THAN,
    GREATER_EQUAL_THAN,
    LESS_EQUAL_THAN,
    AND,
    OR,
    NOT,
    PLUS,
    MINUS,
    TIMES,
    DIVIDE,
    UNARY_MINUS,
    ASSIGN,
    PAR,
    CAST,
    TEST,
};

enum class Error {
    MULTIPLE_DEFINITION,
    UNDECLARED_VARIABLE,
    INCOMPATIBLE_OPERANDS,
    INCOMPATIBLE_ASSIGNMENT,
    INCOMPATIBLE_TEST,
    DECLARED_BUT_NEVER_DEFINED,
    MULTIPLE_DEFINITION_FN,
    WRONG_PARAM_COUNT,
    INCOMPATIBLE_PARAM,
    INCOMPATIBLE_INDEX,
    NON_ARRAY_INDEX,
    NOT_A_POINTER,
    TYPE_ERROR,
};

struct Type {
    PrimitiveType base;
    size_t ptr_count;

    Type() = default;
    Type(PrimitiveType t) : base(t), ptr_count(0) {}
};

inline bool operator==(const Type& lhs, const PrimitiveType& rhs) {
    return lhs.base == rhs && lhs.ptr_count == 0;
}

inline bool operator!=(const Type& lhs, const PrimitiveType& rhs) {
    return !(lhs == rhs);
}

inline bool operator==(const Type& lhs, const Type& rhs) {
    return lhs.base == rhs.base && lhs.ptr_count == rhs.ptr_count;
}

inline bool operator!=(const Type& lhs, const Type& rhs) {
    return !(lhs == rhs);
}

namespace std {
    template<>
    struct hash<PrimitiveType> {
        inline size_t operator()(PrimitiveType type) const {
            return static_cast<int>(type);
        }
    };

    template<>
    struct hash<Operator> {
        inline size_t operator()(Operator op) const {
            return static_cast<int>(op);
        }
    };
}

namespace utils {
    const std::unordered_map<PrimitiveType, std::string> type_table = {
        {PrimitiveType::INT, "int"},
        {PrimitiveType::FLOAT, "float"},
        {PrimitiveType::BOOL, "bool"},
    };

    const std::unordered_map<Operator, std::string> operator_table = {
        {Operator::EQUAL, "=="},
        {Operator::NOT_EQUAL, "!="},
        {Operator::GREATER_THAN, ">"},
        {Operator::LESS_THAN, "<"},
        {Operator::GREATER_EQUAL_THAN, ">="},
        {Operator::LESS_EQUAL_THAN, "<="},
        {Operator::AND, "&"},
        {Operator::OR, "|"},
        {Operator::NOT, "!"},
        {Operator::PLUS, "+"},
        {Operator::MINUS, "-"},
        {Operator::TIMES, "*"},
        {Operator::DIVIDE, "/"},
    };

    const std::unordered_map<PrimitiveType, std::string> printable_type_table = {
        {PrimitiveType::INT, "integer"},
        {PrimitiveType::FLOAT, "float"},
        {PrimitiveType::BOOL, "boolean"},
    };

    const std::unordered_map<Operator, std::string> printable_operator_table = {
        {Operator::EQUAL, "equal"},
        {Operator::NOT_EQUAL, "different"},
        {Operator::GREATER_THAN, "greater than"},
        {Operator::LESS_THAN, "less than"},
        {Operator::GREATER_EQUAL_THAN, "greater or equal than"},
        {Operator::LESS_EQUAL_THAN, "less or equal than"},
        {Operator::AND, "and"},
        {Operator::OR, "or"},
        {Operator::NOT, "negation"},
        {Operator::PLUS, "addition"},
        {Operator::MINUS, "subtraction"},
        {Operator::TIMES, "multiplication"},
        {Operator::DIVIDE, "division"},
        {Operator::UNARY_MINUS, "unary minus"},
        {Operator::ASSIGN, "attribution"},
        {Operator::TEST, "test"},
    };

    struct literal {
        char* value;
        Type type;
    };

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

    inline std::string to_string(PrimitiveType type) {
        return type_table.at(type);
    }

    inline std::string to_string(const Type& type) {
        auto base = to_string(type.base);
        for (auto i = 0; i < type.ptr_count; i++) {
            base += " ref";
        }
        return base;
    }

    inline std::string to_string(Operator op) {
        return operator_table.at(op);
    }

    inline std::string to_printable_string(PrimitiveType type) {
        return printable_type_table.at(type);
    }

    inline std::string to_printable_string(Operator op) {
        return printable_operator_table.at(op);
    }

    inline std::string to_printable_string(const Type& type) {
        auto base = to_printable_string(type.base);
        for (auto i = 0; i < type.ptr_count; i++) {
            base += " pointer";
        }
        return base;
    }

    inline std::string to_string(const char* value) {
        return value;
    }

    inline bool can_coerce(Type target, Type source) {
        return target == PrimitiveType::FLOAT && source == PrimitiveType::INT;
    }

    inline bool type_matches(Type target, Type source) {
        return target == source;
    }

    template<typename T>
    inline void echo(const T& value) {
        std::cerr << value << std::endl;
    }

    inline std::string error_prefix(const std::string& type) {
        auto line = std::to_string(counter().value());
        return "[Line " + line + "] " + type + " error: ";
    }

    template<Error err>
    inline void semantic_error(const std::string&);
    template<Error err>
    inline void semantic_error(Operator, Type, Type);
    template<Error err>
    inline void semantic_error(Type, Type);
    template<Error err>
    inline void semantic_error(Type);
    template<Error err>
    inline void semantic_error(const std::string&, size_t, size_t);
    template<Error err>
    inline void semantic_error(const std::string&, Type, Type);
    template<Error err>
    inline void semantic_error();

    template<>
    inline void semantic_error<Error::MULTIPLE_DEFINITION>(const std::string& name) {
        echo(error_prefix("semantic") + "re-declaration of variable " + name);
    }

    template<>
    inline void semantic_error<Error::MULTIPLE_DEFINITION_FN>(const std::string& name) {
        echo(error_prefix("semantic") + "re-declaration of function " + name);
    }

    template<>
    inline void semantic_error<Error::UNDECLARED_VARIABLE>(const std::string& name) {
        echo(error_prefix("semantic") + "undeclared variable " + name);
    }

    template<>
    inline void semantic_error<Error::INCOMPATIBLE_OPERANDS>(Operator op, Type expected, Type actual) {
        auto op_name = to_printable_string(op);
        auto expected_str = to_printable_string(expected);
        auto actual_str = to_printable_string(actual);
        echo(error_prefix("semantic") + op_name + " operation expected "
            + expected_str + " but received " + actual_str);
    }

    template<>
    inline void semantic_error<Error::INCOMPATIBLE_ASSIGNMENT>(Type expected, Type actual) {
        semantic_error<Error::INCOMPATIBLE_OPERANDS>(Operator::ASSIGN, expected, actual);
    }

    template<>
    inline void semantic_error<Error::INCOMPATIBLE_TEST>(Type received) {
        semantic_error<Error::INCOMPATIBLE_OPERANDS>(Operator::TEST, PrimitiveType::BOOL, received);
    }

    template<>
    inline void semantic_error<Error::DECLARED_BUT_NEVER_DEFINED>(const std::string& name) {
        echo(error_prefix("semantic") + "function " + name + " is declared but never defined");
    }

    template<>
    inline void semantic_error<Error::WRONG_PARAM_COUNT>(const std::string& name,
                                                         size_t expected,
                                                         size_t actual) {
        echo(error_prefix("semantic") + "function " + name + " expects "
            + std::to_string(expected) + " parameters but received " + std::to_string(actual));
    }

    template<>
    inline void semantic_error<Error::INCOMPATIBLE_PARAM>(const std::string& name,
                                                          Type expected,
                                                          Type actual) {
        auto expected_str = to_printable_string(expected);
        auto actual_str = to_printable_string(actual);
        echo(error_prefix("semantic") + "parameter " + name + " expected "
            + expected_str + " but received " + actual_str);
    }

    template<>
    inline void semantic_error<Error::INCOMPATIBLE_INDEX>(Type expected,
                                                          Type actual) {
        auto expected_str = to_printable_string(expected);
        auto actual_str = to_printable_string(actual);
        echo(error_prefix("semantic") + "index operator expects "
            + expected_str + " but received " + actual_str);
    }

    template<>
    inline void semantic_error<Error::NON_ARRAY_INDEX>() {
        echo(error_prefix("semantic") + "index operator expects an array");
    }

    template<>
    inline void semantic_error<Error::NOT_A_POINTER>() {
        echo(error_prefix("semantic") + "reference operation expects a pointer");
    }

    template<>
    inline void semantic_error<Error::TYPE_ERROR>() {
        echo(error_prefix("semantic") + "invalid operand type");
    }
}

#endif /* UTILS_HPP */
