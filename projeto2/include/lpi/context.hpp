
#ifndef LPI_CONTEXT_HPP
#define LPI_CONTEXT_HPP

namespace lpi {
    // Class to interface with lexer and parser without
    // stuck with templates deduction
    class context {
     public:
        virtual void increase_location(unsigned) = 0;
        virtual unsigned location() const = 0;
    };
}

#endif /* LPI_CONTEXT_HPP */
