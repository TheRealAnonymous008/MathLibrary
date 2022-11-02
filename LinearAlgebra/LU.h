#pragma once

#include "fwd.h"
#include "MatOps.h"

namespace MathLib {
	namespace LinearAlgebra{

		template<typename T, const unsigned N>
		struct LUDecompositionResult {
			const SquareMatrix<T, N>& U;
			const SquareMatrix<T, N>& L;
		};

		namespace implementation {
			template<typename T, const unsigned N>
			LUDecompositionResult<T, N> DoolittleLU(SquareMatrix<T, N> M) {
				return LUDecompositionResult<T, N>{ M, M };
			}
		}

		template<typename T, const unsigned N, typename Expr>
		LUDecompositionResult<T, N> LUDecomposition(SquareMatrixBase<T, N, Expr>& expr) {
			return implementation::DoolittleLU(expr.Evaluate());
		}

	}
}