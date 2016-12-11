
#include <iostream>
#include <sstream>
#include "base/errors.hpp"

template<typename L, typename P, typename A>
lpi::lpa_context<L,P,A>::lpa_context():
  lexer{analyser, *this},
  parser{lexer, analyser, *this} {
    err::set_context(*this);
}

template<typename L, typename P, typename A>
lpi::lpa_context<L,P,A>::lpa_context(A a):
  lexer{analyser, *this},
  parser{lexer, analyser, *this},
  analyser{std::move(a)} {
    err::set_context(*this);
}

template<typename L, typename P, typename A>
void lpi::lpa_context<L,P,A>::console_mode(bool flag) {
    analyser.console_mode(flag);
}

template<typename L, typename P, typename A>
void lpi::lpa_context<L,P,A>::include(const std::string& name) {
    file = std::ifstream(name, std::ifstream::in);
    if (file.is_open()) {
        switch_input_stream(&file);
        console_mode(false);
    } else {
        std::cout << "couldn't read file '" << name << "'" << std::endl;
    }
}

template<typename L, typename P, typename A>
void lpi::lpa_context<L,P,A>::close_file() {
    if (file.is_open()) {
        file.close();
    }
    console_mode(true);
    switch_input_stream(&std::cin);
}

template<typename L, typename P, typename A>
void lpi::lpa_context<L,P,A>::count_new_line() {
    lines++;
}

template<typename L, typename P, typename A>
unsigned lpi::lpa_context<L,P,A>::line_count() const {
    return lines;
}

template<typename L, typename P, typename A>
int lpi::lpa_context<L,P,A>::run() {
    loc = 0;
    auto res = parser.parse();
    return res;
}

template<typename L, typename P, typename A>
void lpi::lpa_context<L,P,A>::clear() {
    loc = 0;
}

template<typename L, typename P, typename A>
void lpi::lpa_context<L,P,A>::switch_input_stream(std::istream* is) {
    lexer.switch_streams(is, NULL);
}

template<typename L, typename P, typename A>
void lpi::lpa_context<L,P,A>::increase_location(unsigned length) {
    loc += length;
}

template<typename L, typename P, typename A>
unsigned int lpi::lpa_context<L,P,A>::location() const {
    return loc;
}
