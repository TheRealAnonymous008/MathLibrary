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

			std::array<Vector<T, N>, N> result = SolveLinearSystem(A, IdentityMatrix<T, N>());
			return ColumnsToMatrix(result);
		}
	}
}