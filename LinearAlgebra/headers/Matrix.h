#pragma once

#include "../fwd.h"

namespace MathLib {
	namespace LinearAlgebra {

		template<typename T, const unsigned Rows, const unsigned Columns>
		class Matrix : public Vector<T, Columns * Rows>{
		public:
			const int rows = Rows;
			const int columns = Columns;
			
			using Vector::Vector;
			using Array::At;
			using Vector::operator=;

			using Array::Reshape;

			Matrix<T, Columns, Rows> Transpose() const noexcept{
				Matrix<T, Columns, Rows> transpose;
				
				for (unsigned int i = 0; i < Rows; ++i) {
					for (unsigned int j = 0; j < Columns; ++j) {
						transpose.At({ i, j }) = this->At({ j, i });
					}
				}

				return transpose;
			}

			
		};

		template<typename T, const unsigned N>
		using SquareMatrix = Matrix<T, N, N>;
	}
}