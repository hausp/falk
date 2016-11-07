
#ifndef FALK_DRIVER_HPP
#define FALK_DRIVER_HPP

#include "base/definitions.hpp"
#include "Parser.hpp"
#include "Scanner.hpp"

namespace falk {
    class Driver {
        friend class Parser;
        friend class Scanner;
     public:
        Driver();

        int parse();
        void clear();
        
        void switch_input_stream(std::istream*);
     private:
        Analyser analyser;
        Scanner scanner;
        Parser parser;
        unsigned int loc;

        void increase_location(unsigned);
        unsigned int location() const;
    };
}

#endif /* FALK_DRIVER_HPP */
