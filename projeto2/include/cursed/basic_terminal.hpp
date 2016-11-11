
#ifndef CURSED_CURSE_HPP
#define CURSED_CURSE_HPP

#include <string>

namespace cursed {
    class basic_terminal {
     public:
        virtual std::string get_line() = 0;
    };
}

#endif /* CURSED_CURSE_HPP */
