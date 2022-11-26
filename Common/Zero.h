#pragma once

#include <limits>

namespace MathLib {

	template<typename T>
	constexpr bool IsZero(T val) {
		return val == T();
	}

	template<>
	inline bool IsZero(int val) {
		return val == 0;
	}

	template<>
	inline bool IsZero(float val) {
		return abs(val) < std::numeric_limits <float> ::epsilon();
	}

	template<>
	inline bool IsZero(double val) {
		return abs(val) < std::numeric_limits <double> ::epsilon();
	}

	template<typename T>
	inline bool IsEqual(T x, T y){
		return IsZero(x - y);
	}
}