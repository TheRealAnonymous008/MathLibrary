#pragma once

#include "SpecialMatrices/SquareOps.h"

namespace MathLib {
	namespace LinearAlgebra {

		template<typename T, const unsigned N, typename Exp>
		T Trace(const SquareMatrixBase<T, N, Exp>& mat) {
			T sum = T();

			for (unsigned i = 0; i < N; ++i) {
				sum += mat.At(i, i);
			}
			return sum;
		}
	}
}