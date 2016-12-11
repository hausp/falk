
#include <ncurses.h>
#include "aut/cursed/ostreambuf.hpp"

cursed::ostreambuf::int_type cursed::ostreambuf::overflow(int_type c) {
    addch(c);
    return c;
}