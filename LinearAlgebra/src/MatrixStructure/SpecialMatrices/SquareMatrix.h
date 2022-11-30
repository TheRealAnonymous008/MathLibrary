#pragma once

#include "../../Objects/MatrixBase.h"
#include "../../Objects/Matrix.h"

namespace MathLib {
	namespace LinearAlgebra {

		template<typename T, size_type N>
		using SquareMatrix = Matrix<T, N, N>;

		template<typename T, size_type N, typename Derived>
		using SquareMatrixBase = MatrixBase<T, N, N, Derived>;
	}
}