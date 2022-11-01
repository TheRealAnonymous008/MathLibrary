#pragma once
#include "fwd.h"
#include "Exceptions.h"
#include <math.h>

namespace MathLib {
	namespace LinearAlgebra {

		template<typename T, const unsigned N, typename E>
		T SquareNorm(const VectorBase<T, N, E>& exp) {
			return Dot(exp, exp);
		}

		template<typename T, const unsigned N, typename E>
		T Norm(const VectorBase<T, N, E>& exp) {
			T norm = std::sqrt(Dot(exp, exp));
			return norm;
		}
	}
}