#pragma once

#pragma once
#include "fwd.h"

namespace MathLib {
	namespace LinearAlgebra {

		template<typename T, const unsigned N>
		using SquareMatrix = Matrix<T, N, N>;

		template<typename T, const unsigned N>
		bool IsUpper(const SquareMatrix<T, N>& mat) {
			for (unsigned i = 1; i < N; ++i) {
				for (unsigned j = 0; j < i - 1; ++j) {
					if (mat.At(i, j) != T()) {
						return false;
					}
				}
			}
			return true;
		}

		template<typename T, const unsigned N>
		bool IsLower(const SquareMatrix<T, N>& mat) {
			for (unsigned i = 0; i < N; ++i) {
				for (unsigned j = i + 1; j < N; ++j) {
					if (mat.At(i, j) != T()) {
						return false;
					}
				}
			}
			return true;
		}
	}
}