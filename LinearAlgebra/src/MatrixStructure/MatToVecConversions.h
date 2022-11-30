#pragma once

#include "../Objects/MatrixBase.h"
#include "../Objects/VectorBase.h"

#include <vector>
#include <array>

namespace MathLib {
	namespace LinearAlgebra {
		

		template<typename T, size_type _Rows, size_type _Columns, typename Expr> 
		std::array<Vector<T, _Columns>, _Rows> RowVectorDecomposition(const MatrixBase<T, _Rows, _Columns, Expr>& M) {
			
			std::array<Vector<T, _Columns>, _Rows> v;

			OPENMP_PARALLELIZE
			for (index_type row = 0; row < _Rows; ++row) {
				for (index_type column = 0; column < _Columns; ++column) {
					v[row][column] = M.At(row, column);
				}
			}

			return v;
		}

		template<typename T, size_type _Rows, size_type _Columns, typename Expr>
		Vector<T, _Columns> SelectRowVector(const MatrixBase<T, _Rows, _Columns, Expr>& M, const index_type row) {
			Vector<T, _Columns> v;

			OPENMP_PARALLELIZE
			for (index_type column = 0; column < _Columns; ++column) {
				v[column] = M.At(row, column);
			}

			return v;
		}

		template<typename T, size_type _Rows, size_type _Columns, typename Expr>
		std::array<Vector<T, _Rows>, _Columns> ColumnVectorDecomposition(const MatrixBase<T, _Rows, _Columns, Expr>& M) {

			std::array<Vector<T, _Rows>, _Columns> v;

			OPENMP_PARALLELIZE
			for (index_type row = 0; row < _Rows; ++row) {
				for (index_type column = 0; column < _Columns; ++column) {
					v[column][row] = M.At(row, column);
				}
			}

			return v;
		}

		template<typename T, size_type _Rows, const index_type _Columns, typename Expr>
		Vector<T, _Rows> SelectColumnVector(const MatrixBase<T, _Rows, _Columns, Expr>& M, const index_type column) {
			Vector<T, _Rows> v;

			OPENMP_PARALLELIZE
			for (index_type row = 0; row < _Rows; ++row) {
				v[row] = M.At(row, column);
			}

			return v;
		}
	}
}