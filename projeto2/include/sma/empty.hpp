
#ifndef SMA_EMPTY_HPP
#define SMA_EMPTY_HPP

#include "value.hpp"

namespace sma {
    template<typename Analyser>
    class empty : public sma::value<Analyser> {
     public:
        empty():
          sma::value<Analyser>::object{new ast::empty_node{}} { }
    };
}

#endif /* SMA_EMPTY_HPP */
