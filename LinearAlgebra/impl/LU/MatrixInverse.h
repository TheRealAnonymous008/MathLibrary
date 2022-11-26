#pragma once 

#include "../Objects/MatrixBase.h"
#include "../Objects/VectorBase.h"
#include "../Matrix Structure/Special Matrices/SquareOps.h"
#include "../Vector Arithmetic/UnitVector.h"
#include "../Matrix Structure/VecToMatConversions.h"

#include "LinearSystemSolver.h"

namespace MathLib {
	namespace LinearAlgebra {

		template<typename T, const unsigned N, typename MatExp>
		SquareMatrix<T, N> Inverse(const SquareMatrixBase<T, N, MatExp>& A) {

			std::array<Vector<T, N>, N> result; 

			for (unsigned i = 0; i < N; ++i) {
				auto x = SolveLinearSystem(A, UnitVector<T, N>(i));
				result[i] = x;
			}
			return ColumnsToMatrix(result);
		}
	}
}