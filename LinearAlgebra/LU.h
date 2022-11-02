#pragma once

#include "fwd.h"
#include "MatOps.h"

namespace MathLib {
	namespace LinearAlgebra{

		template<typename T, const unsigned N>
		struct LUDecompositionResult {
			SquareMatrix<T, N> U;
			SquareMatrix<T, N> L;
		};

		namespace implementation {
			template<typename T, const unsigned N>
			LUDecompositionResult<T, N> DoolittleLU(SquareMatrix<T, N> M) {
				LUDecompositionResult<T, N> result;

				for (unsigned i = 0; i < N; ++i) {

					for (unsigned j = i; j < N; ++j) {

						T sum = T();
						for (unsigned k = 0; k < i; ++k) {
							sum += result.L.At(i, k) * result.U.At(k, j);
						}

						result.U.At(i, j) = M.At(i, j) - sum;
					}

					result.L.At(i, i) = Types::Identity<T>();

					for (unsigned j = i + 1; j < N; ++j) {

						T sum = T();
						for (unsigned k = 0; k < i; k++)
							sum += result.L.At(j, k) * result.U.At(k, i);

						result.L.At(j, i) = (M.At(j, i) - sum) / result.U.At(i, i);
					}
				}

				return result;
			}
		}

		template<typename T, const unsigned N, typename Expr>
		LUDecompositionResult<T, N> LUDecomposition(SquareMatrixBase<T, N, Expr>& expr) {
			return implementation::DoolittleLU(expr.Evaluate());
		}

	}
}