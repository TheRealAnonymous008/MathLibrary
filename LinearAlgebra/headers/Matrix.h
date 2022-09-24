#pragma once

#include "../fwd.h"

namespace MathLib {
	namespace LinearAlgebra {

		template<typename T, const unsigned Rows, const unsigned Columns>
		class Matrix : public MultiArray<T, Rows, Columns>{
		public:
			const int rows = Rows;
			const int columns = Columns;
			
			using MultiArray::MultiArray;
			using MultiArray::operator=;
			using MultiArray::operator[];

			Matrix<T, Columns, Rows> Transpose() const noexcept{
				Matrix<T, Columns, Rows> transpose;
				
				for (unsigned int i = 0; i < Rows; ++i) {
					for (unsigned int j = 0; j < Columns; ++j) {
						transpose[j][i] = this->body[i][j];
					}
				}

				return transpose;
			}

			
		};

		template<typename T, const unsigned N>
		using SquareMatrix = Matrix<T, N, N>;
	}
}