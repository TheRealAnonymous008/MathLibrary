#pragma once
#include <initializer_list>
#include "fwd.h"
#include "Exceptions.h"


namespace MathLib {
	namespace LinearAlgebra {

		template<typename T, const unsigned _Rows, const unsigned _Columns>
		class Matrix : public MatrixExpression<T, Matrix<T, _Rows, _Columns>>{
		private:
			std::vector<std::vector<T>> body = std::vector<std::vector<T>>(_Rows, std::vector<T>(_Columns));

		public:
			Matrix() {
				
			}

			~Matrix() {

			}

			Matrix(const std::initializer_list<std::initializer_list<T>>& list) {
				unsigned i = 0;
				for (auto x : list) {
					unsigned j = 0;
					for (auto y : x) {
						body[i][j] = y;
						++j;
					}
					++i;
				}
			}

			void operator=(const std::initializer_list<std::initializer_list<T>>& list) {
				unsigned i = 0;
				for (auto x : list) {
					unsigned j = 0;
					for (auto y : x) {
						body[i][j] = y;
						++j;
					}
					++i;
				}
			}

			template<typename E>
			Matrix(const MatrixExpression<T, E>& expr) {
				if (expr.Rows() != Rows() || expr.Columns() != Columns()) {
					throw DimensionError();;
				}

				for (unsigned i = 0; i < _Rows; ++i) {
					for (unsigned j = 0; j < _Columns; ++j) {
						body[i][j] = expr.At(i, j);
					}
				}
			}

			template<typename E>
			void operator=(const MatrixExpression<T, E>& expr) {
				if (expr.Rows() != Rows() || expr.Columns() != Columns()) {
					throw DimensionError();;
				}

				for (unsigned i = 0; i < _Rows; ++i) {
					for (unsigned j = 0; j < _Columns; ++j) {
						body[i][j] = expr.At(i, j);
					}
				}
			}

			

			constexpr unsigned Size() const{
				return _Rows * _Columns;
			}

			constexpr unsigned Rows() const{ 
				return _Rows;
			}

			constexpr unsigned Columns() const{
				return _Columns;
			}

			T& At(const unsigned& r, const unsigned& c) {
				if (r >= Rows() || r < 0 || c >= Columns() || c < 0)
					throw InvalidAccess();
				return body[r][c];
			}

			T At(const unsigned& r, const unsigned& c) const {
				if (r >= Rows() || r < 0 || c >= Columns() || c < 0)
					throw InvalidAccess();

				return body[r][c];
			}


			template<typename E>
			Matrix& operator+=(const MatrixExpression<T, E>& expr) {
				for (unsigned i = 0; i < Rows(); ++i) {
					for (unsigned j = 0; j < Columns(); ++j) {
						body[i][j] += expr.At(i, j);
					}
				}
				return *this;
			}

			template<typename E>
			Matrix& operator-=(const MatrixExpression<T, E>& expr) {
				for (unsigned i = 0; i < Rows(); ++i) {
					for (unsigned j = 0; j < Columns(); ++j) {
						body[i][j] -= expr.At(i, j);
					}
				}
				return *this;
			}

			Matrix& operator*=(const T& c) {
				for (unsigned i = 0; i < Rows(); ++i) {
					for (unsigned j = 0; j < Columns(); ++j) {
						body[i][j] *= c;
					}
				}
				return *this;
			}

			Matrix& operator/=(const T& c) {
				if (c == 0)
					throw DivisionByZero();

				for (unsigned i = 0; i < Rows(); ++i) {
					for (unsigned j = 0; j < Columns(); ++j) {
						body[i][j] /= c;
					}
				}
				return *this;
			}
		};

	}
}