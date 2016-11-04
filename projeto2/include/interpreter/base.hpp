
#ifndef FALK_INTERPRETER_REAL_HPP
#define FALK_INTERPRETER_REAL_HPP

#include <cmath>
#include <complex>

namespace {
	using complex = std::complex<double>;
}

namespace falk {
	// As Ghabriel wishes
	double pow<double>(const double& d1, const double& d2) {
		return std::pow(d1, d2);
	}

	complex pow<complex>(const complex& c1, const complex& c2) {
		return std::pow(c1, c2);
	}
}

#endif /* FALK_INTERPRETER_REAL_HPP */
