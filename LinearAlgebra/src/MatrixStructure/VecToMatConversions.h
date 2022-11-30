#pragma once

#include "../Objects/MatrixBase.h"
#include "../Objects/VectorBase.h"

#include <vector>
#include <array>

namespace MathLib {
	namespace LinearAlgebra {

		template<typename T, size_type _Rows, size_type _Columns>
		Matrix<T, _Rows, _Columns> ColumnsToMatrix(const std::array<Vector<T, _Rows>, _Columns>& v) {
			Matrix<T, _Rows, _Columns> M = Matrix<T, _Rows, _Columns>();
			
			OPENMP_PARALLELIZE
			for (index_type j = 0; j < _Columns; ++j) {
				for (index_type i = 0; i < _Rows; ++i) {
					M.At(i, j) = v[j][i];
				}
			}

			return M;
		}

		template<typename T, size_type _Rows, size_type _Columns>
		Matrix<T, _Rows, _Columns> RowsToMatrix(const std::array<Vector<T, _Columns>, _Rows>& v) {
			Matrix<T, _Rows, _Columns> M = Matrix<T, _Rows, _Columns>();

			OPENMP_PARALLELIZE
			for (index_type i = 0; i < _Rows; ++i) {
				for (index_type j = 0; j < _Columns; ++j) {
					M.At(i, j) = v[i][j];
				}
			}

			return M;
		}
	}
}