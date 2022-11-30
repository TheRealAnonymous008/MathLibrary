#pragma once 

#include "../Objects/MatrixBase.h"
#include "../Objects/VectorBase.h"
#include "../MatrixStructure/SpecialMatrices/SquareOps.h"
#include "../VectorArithmetic/UnitVector.h"
#include "../MatrixStructure/VecToMatConversions.h"

#include "LinearSystemSolver.h"

namespace MathLib {
	namespace LinearAlgebra {

		template<typename T, size_type N, typename MatExp>
		SquareMatrix<T, N> Inverse(const SquareMatrixBase<T, N, MatExp>& A) {

			std::array<Vector<T, N>, N> result; 

			for (index_type i = 0; i < N; ++i) {
				auto x = SolveLinearSystem(A, UnitVector<T, N>(i));
				result[i] = x;
			}
			return ColumnsToMatrix(result);
		}
	}
}