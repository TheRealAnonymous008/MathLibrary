#pragma once
#include <initializer_list>
#include "fwd.h"


namespace MathLib {
	namespace LinearAlgebra {

		template<typename T, const unsigned _Rows, const unsigned _Columns>
		class Matrix {
		private:
			std::vector<std::vector<T>> body = std::vector<std::vector<T>>(_Rows, std::vector<int>(_Columns));

		public:
			Matrix() {
				
			}

			~Matrix() {

			}

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
				return _Rows * _Columns;
			}

			constexpr unsigned Rows() { 
				return _Rows;
			}

			constexpr unsigned Columns() {
				return _Columns;
			}

			T& At(const unsigned& r, const unsigned& c) {
				if (r >= Rows() || r < 0 || c >= Columns() || c < 0)
					throw InvalidAccess();
				return body[r][c];
			}

			T operator[](size_t i) const {
				if (r >= Rows() || r < 0 || c >= Columns() || c < 0)
					throw InvalidAccess();

				return body[i];
			}
		};

	}
}