#pragma once

#include "../Objects/MatrixBase.h"
#include "../Objects/VectorBase.h"

#include <vector>
#include <array>

namespace MathLib {
	namespace LinearAlgebra {

		template<typename T, const unsigned _Rows, const unsigned _Columns>
		Matrix<T, _Rows, _Columns> ColumnsToMatrix(const std::array<Vector<T, _Rows>, _Columns>& v) {
			Matrix<T, _Rows, _Columns> M = Matrix<T, _Rows, _Columns>();
			
			OPENMP_PARALLELIZE
			for (unsigned j = 0; j < _Columns; ++j) {
				for (unsigned i = 0; i < _Rows; ++i) {
					M.At(i, j) = v[j][i];
				}
			}

			return M;
		}

		template<typename T, const unsigned _Rows, const unsigned _Columns>
		Matrix<T, _Rows, _Columns> RowsToMatrix(const std::array<Vector<T, _Columns>, _Rows>& v) {
			Matrix<T, _Rows, _Columns> M = Matrix<T, _Rows, _Columns>();

			OPENMP_PARALLELIZE
			for (unsigned i = 0; i < _Rows; ++i) {
				for (unsigned j = 0; j < _Columns; ++j) {
					M.At(i, j) = v[i][j];
				}
			}

			return M;
		}
	}
}