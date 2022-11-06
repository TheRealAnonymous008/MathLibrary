#pragma once

#include "../Objects/MatrixBase.h"
#include "../Objects/Matrix.h"
#include "../Matrix Structure/SquareOps.h"
#include "LUResult.h"

namespace MathLib {
	namespace LinearAlgebra{

		namespace implementation {

			template<typename T, const unsigned _Rows, const unsigned _Columns>
			PartialLUDecomposition<T, _Rows, _Columns> DoolittleLU(const Matrix<T, _Rows, _Columns>& M) {
				auto LU = PartialLUDecomposition<T, _Rows, _Columns>();

				for (unsigned i = 0; i < _Rows; ++i) {
					
				}

				return LU;
			}
		}

		template<typename T, const unsigned _Rows, const unsigned _Columns, typename Expr>
		PartialLUDecomposition<T, _Rows, _Columns> PartialLU(MatrixBase<T, _Rows, _Columns, Expr>& expr) {
			return implementation::DoolittleLU(expr.Evaluate());
		}

	}
}