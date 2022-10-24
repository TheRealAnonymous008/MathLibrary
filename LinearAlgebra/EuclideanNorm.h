#pragma once
#include "fwd.h"
#include "Exceptions.h"
#include <math.h>

namespace MathLib {
	namespace LinearAlgebra {

		template<typename T, typename E>
		T SquareNorm(const VectorExpression<T, E>& exp) {
			return Dot(exp, exp);
		}

		template<typename T, typename E>
		T Norm(const VectorExpression<T, E>& exp) {
			T norm = std::sqrt(Dot(exp, exp));
			return norm;
		}
	}
}