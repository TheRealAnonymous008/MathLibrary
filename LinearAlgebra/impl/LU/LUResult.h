#pragma once

#include "../Objects/Matrix.h"
#include "../Matrix Structure/SquareOps.h"
#include "../Matrix Structure/PermutationMatrix.h"

namespace MathLib {
	namespace LinearAlgebra {

		template<typename T, const unsigned _Rows, const unsigned _Columns>
		struct PartialLUDecomposition {
			PermutationMatrix<T, _Rows> P;
			SquareMatrix<T, _Rows> L;
			Matrix<T, _Rows, _Columns> U;
		};

	}
}