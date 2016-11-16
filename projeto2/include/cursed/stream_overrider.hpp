
#ifndef CURSED_STREAM_OVERRIDER_HPP
#define CURSED_STREAM_OVERRIDER_HPP

#include <iostream>

namespace cursed {
    class stream_overrider {
     public:
        stream_overrider(std::istream&, std::ostream&,
                         std::istream& = std::cin,
                         std::ostream& = std::cout);
        ~stream_overrider();
     private:
        std::istream& insrc;
        std::ostream& outsrc;
        std::streambuf * const insrc_buffer;
        std::streambuf * const outsrc_buffer;
    };

    stream_overrider::stream_overrider(std::istream& input,
                                       std::ostream& output,
                                       std::istream& insrc,
                                       std::ostream& outsrc):
      insrc{insrc},
      outsrc{outsrc},
      insrc_buffer{insrc.rdbuf()},
      outsrc_buffer{outsrc.rdbuf()} {
        insrc.rdbuf(input.rdbuf());
        outsrc.rdbuf(output.rdbuf());
    }

    stream_overrider::~stream_overrider() {
        insrc.rdbuf(insrc_buffer);
        outsrc.rdbuf(outsrc_buffer);
    }
}

#endif /* CURSED_STREAM_OVERRIDER_HPP */
