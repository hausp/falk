
#ifndef FALK_DRIVER_HPP
#define FALK_DRIVER_HPP

#include "Scanner.hpp"
#include "Parser.hpp"

namespace falk {
    class Driver {
        public:
            Driver();

            int parse();
            void clear();
            std::string str() const;
            
            void switchInputStream(std::istream*);

            friend class Parser;
            friend class Scanner;
            
        private:            
            void increaseLocation(unsigned int);

            unsigned int location() const;
            
        private:
            Scanner scanner;
            Parser parser;
            unsigned int loc;
    };

}

#endif /* FALK_DRIVER_HPP */
