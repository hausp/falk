
#ifndef LPI_LPA_CONTEXT_HPP
#define LPI_LPA_CONTEXT_HPP

#include "context.hpp"

// lexer-parser integration
namespace lpi {
    template<typename Lexer, typename Parser, typename Analyser>
    class lpa_context : private context {
        friend Lexer;
        friend Parser;
        friend Analyser;
     public:
        lpa_context();
        lpa_context(Analyser);

        void console_mode(bool);

        void include(const std::string&) override;
        void count_new_line() override;
        unsigned line_count() const override;
        int run();
        void clear();
        void close_file() override;
        void switch_input_stream(std::istream*);
     private:
        Lexer lexer;
        Parser parser;
        Analyser analyser;
        unsigned loc = 0;
        unsigned lines = 0;
        std::ifstream file;

        void increase_location(unsigned) override;
        unsigned location() const override;
    };
}

#include "lpa_context.ipp"

#endif /* LPI_LPA_CONTEXT_HPP */
