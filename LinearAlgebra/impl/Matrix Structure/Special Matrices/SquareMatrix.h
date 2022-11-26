#pragma once

#include "../../Objects/MatrixBase.h"
#include "../../Objects/Matrix.h"

namespace MathLib {
	namespace LinearAlgebra {

		template<typename T, const unsigned N>
		using SquareMatrix = Matrix<T, N, N>;

		template<typename T, const unsigned N, typename Derived>
		using SquareMatrixBase = MatrixBase<T, N, N, Derived>;
	}
}