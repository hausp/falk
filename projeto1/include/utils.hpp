#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <string>

enum class Type {
    INT
};

enum class Error {
    MULTIPLE_DEFINITION,
    UNDECLARED_VARIABLE
};

namespace utils {
    template<typename T>
    inline std::string to_string(const T& value) {
        return std::to_string(value);
    }

    // Type to string
    inline std::string to_string(Type type) {
        return "";
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

    inline std::string error_prefix(const std::string& type, size_t line) {
        return "[Line " + std::to_string(line) + "] " + type + " error: ";
    }

    template<Error err>
    inline void semantic_error(size_t, const std::string&);

    template<>
    inline void semantic_error<Error::MULTIPLE_DEFINITION>(size_t line, const std::string& name) {
        echo(error_prefix("semantic", line) + "re-declaration of variable " + name);
    }

    template<>
    inline void semantic_error<Error::UNDECLARED_VARIABLE>(size_t line, const std::string& name) {
        echo(error_prefix("semantic", line) + "undeclared variable " + name);
    }
}

#endif /* UTILS_HPP */
