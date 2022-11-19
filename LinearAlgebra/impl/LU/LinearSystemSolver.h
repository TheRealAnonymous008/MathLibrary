#pragma once 

#include "../Objects/MatrixBase.h"
#include "../Objects/VectorBase.h"
#include "../Matrix Structure/SquareOps.h"

namespace MathLib {
	namespace LinearAlgebra {
		template<typename T, const unsigned N, typename MatExp, typename VecExp>
		Vector<T, N> ForwardSolve(const SquareMatrixBase<T, N, MatExp>& A, const VectorBase<T, N, VecExp>& y) {
			Vector<T, N> x;

			for (unsigned i = 0; i < N; ++i) {
				T total = 0;

				for (unsigned j = 0; j < i; ++j) {
					total += A.At(i, j) * x[j];
				}
				x[i] = (y[i] - total) / A.At(i, i);
			}

			return x;
		}
	}
}