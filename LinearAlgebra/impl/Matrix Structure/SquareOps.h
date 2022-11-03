#pragma once

#include "../Objects/MatrixBase.h"
#include "../Objects/Matrix.h"

namespace MathLib {
	namespace LinearAlgebra {

		template<typename T, const unsigned N>
		using SquareMatrix = Matrix<T, N, N>;

		template<typename T, const unsigned N, typename Derived>
		using SquareMatrixBase = MatrixBase<T, N, N, Derived>;

		template<typename T, const unsigned N, typename Exp>
		bool IsUpper(const SquareMatrixBase<T, N, Exp>& mat) {
			for (unsigned i = 1; i < N; ++i) {
				for (unsigned j = 0; j < i - 1; ++j) {
					if (mat.At(i, j) != T()) {
						return false;
					}
				}
			}
			return true;
		}

		template<typename T, const unsigned N, typename Exp>
		bool IsLower(const SquareMatrixBase<T, N, Exp>& mat) {
			for (unsigned i = 0; i < N; ++i) {
				for (unsigned j = i + 1; j < N; ++j) {
					if (mat.At(i, j) != T()) {
						return false;
					}
				}
			}
			return true;
		}

		template<typename T, const unsigned N, typename Exp>
		bool IsDiagonal(const SquareMatrixBase<T, N, Exp>& mat) {
			for (unsigned i = 0; i < N; ++i) {
				for (unsigned j = 0; j < N; ++j) {
					if (i != j && mat.At(i, j) != T()) {
						return false;
					}
				}
			}

			return true;
		}

		template<typename T, const unsigned N, typename Exp>
		bool IsSymmetric(const SquareMatrixBase<T, N, Exp>& mat) {
			for (unsigned i = 0; i < N; ++i) {
				for (unsigned j = i + 1; j < N; ++j) {
					if (mat.At(i, j) != mat.At(j, i)) {
						return false;
					}
				}
			}
			return true;
		}
	}
}