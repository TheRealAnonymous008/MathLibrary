#pragma once

#include "../Objects/fwd.h"

#include <vector>

namespace MathLib {
	namespace LinearAlgebra {

		template<typename T, const unsigned _Rows, const unsigned _Columns>
		Matrix<T, _Rows, _Columns> ColumnsToMatrix(const Vector<Vector<T, _Rows>, _Columns>& v) {
			Matrix<T, _Rows, _Columns> M = Matrix<T, _Rows, _Columns>();
			
			for (unsigned j = 0; j < _Columns; ++j) {
				for (unsigned i = 0; i < _Rows; ++i) {
					//std::cout << i << " " << j << " " << &v[j][i] << "\n";
					M.At(i, j) = v[j][i];
				}
			}

			return M;
		}

		template<typename T, const unsigned _Rows, const unsigned _Columns>
		Matrix<T, _Rows, _Columns> RowsToMatrix(const Vector<Vector<T, _Columns>, _Rows>& v) {
			Matrix<T, _Rows, _Columns> M = Matrix<T, _Rows, _Columns>();

			for (unsigned i = 0; i < _Rows; ++i) {
				for (unsigned j = 0; j < _Columns; ++j) {
					//std::cout << i << " " << j << " " << &v[i][j] << "\n";
					M.At(i, j) = v[i][j];
				}
			}

			return M;
		}
	}
}