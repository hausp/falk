#include "base/Driver.hpp"

#include <iostream>

falk::Driver::Driver() :
    scanner{analyser, *this},
    parser{scanner, analyser, *this},
    loc{0} { }

int falk::Driver::parse() {
    loc = 0;
    std::cout << "falk> ";
    auto res = parser.parse();
    std::cout << "called quit!" << std::endl;
    return res;
}

void falk::Driver::clear() {
    loc = 0;
}

void falk::Driver::switch_input_stream(std::istream* is) {
    scanner.switch_streams(is, NULL);
}

void falk::Driver::increase_location(unsigned length) {
    loc += length;
}

unsigned int falk::Driver::location() const {
    return loc;
}
