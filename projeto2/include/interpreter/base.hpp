
#ifndef FALK_INTERPRETER_REAL_HPP
#define FALK_INTERPRETER_REAL_HPP

#include <cmath>

namespace falk {
	// As Ghabriel wishes
	double pow<double>(const double& d1, const double& d2) {
		return std::pow(d1, d2);
	}

	std::complex pow<std::complex>(const std::complex& c1, const std::complex& c2) {
		return std::pow(c1, c2);
	}
}

#endif /* FALK_INTERPRETER_REAL_HPP */
