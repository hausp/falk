
#ifndef CURSED_OSTREAMBUF_HPP
#define CURSED_OSTREAMBUF_HPP

#include <streambuf>

namespace cursed {
    class ostreambuf : public std::streambuf {
    public:
        int_type overflow(int_type c) override;
    };
}

#endif /* CURSED_OSTREAMBUF_HPP */
