
#include <iostream>
#include "base/definitions.hpp"
#include "cursed/overterm.hpp"
#include "lpi/lpa_context.hpp"
#include "scanner.hpp"

#include "base/sma/value.hpp"

struct complex_type {
    static constexpr size_t arity() { return 6; };
    int x = 666;
};

std::ostream& operator<<(std::ostream& out, const complex_type& c) {
    return out << c.x;
}

class analyser {
 public:
    void analyse(int a) {
        std::cout << "int: " << a << std::endl;
    }

    void analyse(complex_type& c, const std::array<std::unique_ptr<ast::node<analyser>>, 6>& list) {
        std::cout << "complex_type: " << c << std::endl;
    }
};

int main(int, char **) {
    // falk::sma::value<analyser> value = complex_type{333};
    // auto node = value.get_node();
    // analyser an;

    // node->traverse(an);

    cursed::overterm<true> terminal;

    lpi::lpa_context<falk::scanner, falk::parser, falk::analyser> context;
    
    return context.run();
}
