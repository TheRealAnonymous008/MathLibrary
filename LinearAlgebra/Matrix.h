#pragma once
#include <initializer_list>
#include "fwd.h"


namespace MathLib {
	namespace LinearAlgebra {

		template<typename T, const unsigned Rows, const unsigned Columns>
		class Matrix {
		private:
			T body[Rows][Columns];

		public:
			Matrix() { }
			Matrix(const std::initializer_list<std::initializer_list<T>>& list) {
				int i = 0;
				for (auto x : list) {
					int j = 0;
					for (auto y : x) {
						body[i][j] = y;
						++j;
					}
					++i;
				}
			}

			constexpr unsigned Size() {
				return Rows * Columns;
			}

			constexpr unsigned Rows() { 
				return Rows; 
			}

			constexpr unsigned Columns() {
				return Columns;
			}
		};

	}
}