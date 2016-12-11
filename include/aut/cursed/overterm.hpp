
#ifndef CURSED_OVERTERM_HPP
#define CURSED_OVERTERM_HPP

#include "stream_overrider.hpp"
#include "terminal.hpp"

namespace cursed {
    template<bool Override>
    class overterm;

    template<>
    class overterm<true> {
     public:
        overterm():
          overrider{term.istream(), term.ostream()} { }
     private:
        cursed::terminal term;
        cursed::stream_overrider overrider;
    };
}

#endif /* CURSED_OVERTERM_HPP */
