#pragma once
#include "fwd.h"

namespace MathLib {
	namespace LinearAlgebra {

		template<
			const unsigned _NRows, const unsigned _NCols,
			typename T, typename Expr,
			const unsigned _Rows, const unsigned _Columns
		>
		Matrix<T, _NRows, _NCols> PlaceBlock(const MatrixExpression<T, _Rows, _Columns, Expr>& M,
			const unsigned x = 0,
			const unsigned y = 0) {

			Matrix<T, _NRows, _NCols> result;

			for (unsigned i = 0; i < M.Rows(); ++i) {
				for (unsigned j = 0; j < M.Columns(); ++j) {
					result.At(x + i, y + j) = M.At(i, j);
				}
			}

			return result;
		}

		template<
			const unsigned _NRows, const unsigned _NCols,
			typename T, typename Expr,
			const unsigned _Rows, const unsigned _Columns
		>
		void PlaceBlock(Matrix<T, _NRows, _NCols>& result, const MatrixExpression<T, _Rows, _Columns, Expr>& M,
			const unsigned x = 0,
			const unsigned y = 0) {

			for (unsigned i = 0; i < _Rows; ++i) {
				for (unsigned j = 0; j < _Columns; ++j) {
					result.At(x + i, y + j) = M.At(i, j);
				}
			}
		}
	}
}