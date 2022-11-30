#pragma once

#include "../Objects/MatrixBase.h"
#include "../Objects/Matrix.h"

namespace MathLib {
	namespace LinearAlgebra {

		template<size_type _NRows, size_type _NCols, typename T, typename Expr, size_type _Rows, size_type _Columns>
		Matrix<T, _NRows, _NCols> PlaceBlock(const MatrixBase<T, _Rows, _Columns, Expr>& M,
			const index_type x = 0,
			const index_type y = 0) {

			Matrix<T, _NRows, _NCols> result;

			OPENMP_PARALLELIZE
			for (index_type i = 0; i < _Rows; ++i) {
				for (index_type j = 0; j < _Columns; ++j) {
					result.At(x + i, y + j) = M.At(i, j);
				}
			}

			return result;
		}

		template<size_type _NRows, size_type _NCols, typename T, typename Expr, size_type _Rows, size_type _Columns>
		void PlaceBlock(Matrix<T, _NRows, _NCols>& result, const MatrixBase<T, _Rows, _Columns, Expr>& M,
			const index_type x = 0,
			const index_type y = 0) 
		{

			OPENMP_PARALLELIZE
			for (index_type i = 0; i < _Rows; ++i) {
				for (index_type j = 0; j < _Columns; ++j) {
					result.At(x + i, y + j) = M.At(i, j);
				}
			}
		}
	}
}