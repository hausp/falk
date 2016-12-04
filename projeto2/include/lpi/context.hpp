
#ifndef LPI_CONTEXT_HPP
#define LPI_CONTEXT_HPP

namespace lpi {
    // Class to interface with lexer and parser without
    // stuck with templates deduction
    class context {
     public:
        virtual void include(const std::string&) = 0;
        virtual void increase_location(unsigned) = 0;
        virtual unsigned location() const = 0;
        virtual void count_new_line() = 0;
        virtual unsigned line_count() const = 0;
    };

    template<typename Context>
    void lexical_error(const Context& context, const std::string& message) {
        std::cout << "[Line " << context.line_count() << "] lexical error: ";
        std::cout << message;
    }
}

#endif /* LPI_CONTEXT_HPP */
