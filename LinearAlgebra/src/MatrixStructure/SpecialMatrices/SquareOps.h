#pragma once

#include "SquareMatrix.h"

namespace MathLib {
	namespace LinearAlgebra {

		template<typename T, size_type N, typename Exp>
		bool IsUpper(const SquareMatrixBase<T, N, Exp>& mat) {
			for (index_type i = 1; i < N; ++i) {
				for (index_type j = 0; j < i - 1; ++j) {
					if (mat.At(i, j) != T()) {
						return false;
					}
				}
			}
			return true;
		}

		template<typename T, size_type N, typename Exp>
		bool IsLower(const SquareMatrixBase<T, N, Exp>& mat) {
			for (index_type i = 0; i < N; ++i) {
				for (index_type j = i + 1; j < N; ++j) {
					if (mat.At(i, j) != T()) {
						return false;
					}
				}
			}
			return true;
		}

		template<typename T, size_type N, typename Exp>
		bool IsDiagonal(const SquareMatrixBase<T, N, Exp>& mat) {
			for (index_type i = 0; i < N; ++i) {
				for (index_type j = 0; j < N; ++j) {
					if (i != j && mat.At(i, j) != T()) {
						return false;
					}
				}
			}

			return true;
		}

		template<typename T, size_type N, typename Exp>
		bool IsSymmetric(const SquareMatrixBase<T, N, Exp>& mat) {
			for (index_type i = 0; i < N; ++i) {
				for (index_type j = i + 1; j < N; ++j) {
					if (mat.At(i, j) != mat.At(j, i)) {
						return false;
					}
				}
			}
			return true;
		}
	}
}