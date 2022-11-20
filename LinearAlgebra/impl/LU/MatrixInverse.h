#pragma once 

#include "../Objects/MatrixBase.h"
#include "../Objects/VectorBase.h"
#include "../Matrix Structure/SquareOps.h"
#include "../Vector Arithmetic/UnitVector.h"

#include "LinearSystemSolver.h"

namespace MathLib {
	namespace LinearAlgebra {

		template<typename T, const unsigned N, typename MatExp>
		SquareMatrix<T, N> Inverse(const SquareMatrixBase<T, N, MatExp>& A) {

			std::vector<Vector<T, N>> result; 

			for (unsigned i = 0; i < N; ++i) {
				auto x = SolveLinearSystem(A, UnitVector<T, i, N>());
				result.push_back(x);
			}
			return 
		}
	}
}