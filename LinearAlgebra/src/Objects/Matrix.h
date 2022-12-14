#pragma once

#include "../../headers/Fwd.h"
#include "../../Exceptions.h"

#include <execution>
#include <initializer_list>
#include <vector>

namespace MathLib {
	namespace LinearAlgebra {

		template<typename T, typename size_type _Rows, size_type _Columns>
		class Matrix : public MatrixBase<T, _Rows, _Columns, Matrix<T, _Rows, _Columns>>, public Stringable{
		private:
			std::vector<T>* body = new std::vector<T>(_Rows * _Columns);

			index_type GetIndex(index_type i, index_type j) const {
				return i * _Columns + j;
			}

			void CopyBody(const std::vector<T>& other) {
				std::copy(std::execution::par_unseq, other.begin(), other.end(), this->body->begin());
			}

		public:
			Matrix() {
				
			}

			~Matrix() {
				delete body;
			}

			Matrix(const std::initializer_list<std::initializer_list<T>>& list) {
				index_type i = 0;
				for (auto x : list) {
					index_type j = 0;
					for (auto y : x) {
						this->At(i, j) = y;
						++j;
					}
					++i;
				}
			}

			void operator=(const std::initializer_list<std::initializer_list<T>>& list) {
				index_type i = 0;
				for (auto x : list) {
					index_type j = 0;
					for (auto y : x) {
						this->At(i, j) = y;
						++j;
					}
					++i;
				}
			}

			Matrix(const Matrix& expr) {
				CopyBody(*(expr.body));
			}

			void operator=(const Matrix& expr) {
				CopyBody(*(expr.body));
			}

			template<typename E>
			Matrix(const MatrixBase<T, _Rows, _Columns, E>& expr) {
				Matrix eval = expr.Evaluate();
				CopyBody(*(eval.body));
			}

			template<typename E>
			void operator=(const MatrixBase<T, _Rows, _Columns, E>& expr) {
				Matrix eval = expr.Evaluate();
				CopyBody(*(eval.body));
			}			

			T& At(const index_type& r, const index_type& c) {
				return (*body)[GetIndex(r, c)];
			}

			T At(const index_type& r, const index_type& c) const {
				return (*body)[GetIndex(r, c)];
			}


			template<typename E>
			const Matrix& operator+=(const MatrixBase<T, _Rows, _Columns, E>& expr) {
				
				auto eval = expr.Evaluate();

				OPENMP_PARALLELIZE
				for (index_type i = 0; i < _Rows; ++i) {
					for (index_type j = 0; j < _Columns; ++j) {
						this->At(i, j) += eval.At(i, j);
					}
				}

				return *this;
			}

			template<typename E>
			const Matrix& operator-=(const MatrixBase<T, _Rows, _Columns,  E>& expr) {

				auto eval = expr.Evaluate();

				OPENMP_PARALLELIZE
				for (index_type i = 0; i < _Rows; ++i) {
					for (index_type j = 0; j < _Columns; ++j) {
						this->At(i, j) -= eval.At(i, j);
					}
				}
				return *this;
			}

			const Matrix& operator*=(const T& c) {

				OPENMP_PARALLELIZE
				for (index_type i = 0; i < _Rows; ++i) {
					for (index_type j = 0; j < _Columns; ++j) {
						this->At(i, j) *= c;
					}
				}
				return *this;
			}

			const Matrix& operator/=(const T& c) {
				if (c == 0)
					throw DivisionByZero();

				OPENMP_PARALLELIZE
				for (index_type i = 0; i < _Rows; ++i) {
					for (index_type j = 0; j < _Columns; ++j) {
						this->At(i, j) /= c;
					}
				}
				return *this;
			}

			const Matrix& Evaluate() const{
				return (*this);
			}

			std::string Str() const {

				std::ostringstream oss;

				for (index_type i = 0; i < _Rows; ++i) {
					for (index_type j = 0; j < _Columns; ++j) {
						oss << this->At(i, j) << " ";
					}
					oss << "\n";
				}

				return oss.str();
			}
		};

	}
}