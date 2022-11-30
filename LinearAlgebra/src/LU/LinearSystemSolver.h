#pragma once 

#include "../Objects/MatrixBase.h"
#include "../Objects/VectorBase.h"

#include "../MatrixStructure/SpecialMatrices/SquareOps.h"

#include "LUResult.h"
#include "PartialLU.h"

namespace MathLib {
	namespace LinearAlgebra {
		template<typename T, size_type N, typename MatExp, typename VecExp>
		Vector<T, N> ForwardSolve(const SquareMatrixBase<T, N, MatExp>& A, const VectorBase<T, N, VecExp>& y) {
			Vector<T, N> x;

			for (index_type i = 0; i < N; ++i) {
				T total = 0;

				for (index_type j = 0; j < i; ++j) {
					total += A.At(i, j) * x[j];
				}
				x[i] = (y[i] - total) / A.At(i, i);
			}

			return x;
		}

		template<typename T, size_type N, typename MatExp, typename VecExp>
		Vector<T, N> BackwardSolve(const SquareMatrixBase<T, N, MatExp>& A, const VectorBase<T, N, VecExp>& y) {
			Vector<T, N> x;

			for (int i = N - 1; i >= 0; --i) {
				T total = 0;

				for (int j = N - 1; j > i; --j) {
					total += A.At(i, j) * x[j];
				}

				x[i] = (y[i] - total) / A.At(i, i);
			}

			return x;
		}

		template<typename T, size_type N, typename MatExp, typename VecExp>
		Vector<T, N> SolveLinearSystem(const SquareMatrixBase<T, N, MatExp>& A, const VectorBase<T, N, VecExp>& y) {
			PartialLUResult lu = PartialLU(A);

			Vector<T, N> v = ForwardSolve(lu.L, lu.P * y);
			Vector<T, N> x = BackwardSolve(lu.U, v);

			return x;
		}

		template<typename T, size_type N, typename MatExp, typename VecExp>
		Vector<T, N> SolveLinearSystem(const SquareMatrixBase<T, N, MatExp>& A, 
			const std::vector<VectorBase<T, N, VecExp>> & ys
		) {
			PartialLUResult lu = PartialLU(A);
			std::vector<VectorBase<T, N, VecExp>>& result;

			for (index_type i = 0; i < ys.size(); ++i) {
				Vector<T, N> v = ForwardSolve(lu.L, lu.P * ys[i]);
				Vector<T, N> x = BackwardSolve(lu.U, v);
				result.push_back(x);
			}

			return result;
		}
	}
}