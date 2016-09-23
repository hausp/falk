#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <string>

enum class Type {
    INT
};

enum class Error {
    MULTIPLE_DEFINITION
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

    template<Error err>
    inline void error();

    template<>
    inline void error<Error::MULTIPLE_DEFINITION>() {
        echo("YOU ARE DUMB AS FUCK");
    }
}

#endif /* UTILS_HPP */
