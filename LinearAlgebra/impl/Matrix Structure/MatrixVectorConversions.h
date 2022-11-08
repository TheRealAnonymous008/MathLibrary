#pragma once

#include "../Objects/fwd.h"

#include <vector>

namespace MathLib {
	namespace LinearAlgebra {
		

		template<typename T, const unsigned _Rows, const unsigned _Columns, typename Expr> 
		Vector<Vector<T, _Columns>, _Rows> RowVectorDecomposition(const MatrixBase<T, _Rows, _Columns, Expr>& M) {
			
			Vector<Vector<T, _Columns>, _Rows> v;

			OPENMP_PARALLELIZE
			for (unsigned row = 0; row < _Rows; ++row) {
				for (unsigned column = 0; column < _Columns; ++column) {
					v[row][column] = M.At(row, column);
				}
			}

			return v;
		}

		template<typename T, const unsigned _Rows, const unsigned _Columns, typename Expr>
		Vector<T, _Columns> SelectRowVector(const MatrixBase<T, _Rows, _Columns, Expr>& M, const unsigned row) {
			Vector<T, _Columns> v;

			OPENMP_PARALLELIZE
			for (unsigned column = 0; column < _Columns; ++column) {
				v[column] = M.At(row, column);
			}

			return v;
		}

		template<typename T, const unsigned _Rows, const unsigned _Columns, typename Expr>
		Vector<Vector<T, _Rows>, _Columns> ColumnVectorDecomposition(const MatrixBase<T, _Rows, _Columns, Expr>& M) {

			Vector<Vector<T, _Rows>, _Columns> v;

			OPENMP_PARALLELIZE
				for (unsigned row = 0; row < _Rows; ++row) {
					for (unsigned column = 0; column < _Columns; ++column) {
						v[column][row] = M.At(row, column);
					}
				}

			return v;
		}

		template<typename T, const unsigned _Rows, const unsigned _Columns, typename Expr>
		Vector<T, _Rows> SelectColumnVector(const MatrixBase<T, _Rows, _Columns, Expr>& M, const unsigned column) {
			Vector<T, _Rows> v;

			OPENMP_PARALLELIZE
				for (unsigned row = 0; row < _Rows; ++row) {
					v[row] = M.At(row, column);
				}

			return v;
		}
	}
}