/*
 * The MIT License (MIT)
 * 
 * Copyright (c) 2014 Krzysztof Narkiewicz <krzysztof.narkiewicz@ezaquarii.com>
 * 
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 * 
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 * 
 */

#include "Driver.hpp"

#include <sstream>

falk::Driver::Driver() :
    scanner(*this),
    parser(scanner, *this),
    loc(0) { }

int falk::Driver::parse() {
    loc = 0;
    return parser.parse();
}

void falk::Driver::clear() {
    loc = 0;
}

std::string falk::Driver::str() const {
    std::stringstream s;
    s << "adios" << std::endl;
    return s.str();
}

void falk::Driver::switchInputStream(std::istream* is) {
    scanner.switch_streams(is, NULL);
}

void falk::Driver::increaseLocation(unsigned int length) {
    loc += length;
    std::cout << "increaseLocation(): " << length << ", total = " << loc << std::endl;
}

unsigned int falk::Driver::location() const {
    return loc;
}
