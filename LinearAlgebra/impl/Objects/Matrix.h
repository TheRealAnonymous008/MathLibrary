#pragma once

#include "fwd.h"
#include "../../Exceptions.h"

#include <initializer_list>
#include <vector>

namespace MathLib {
	namespace LinearAlgebra {

		template<typename T, typename const unsigned _Rows, const unsigned _Columns>
		class Matrix : public MatrixBase<T, _Rows, _Columns, Matrix<T, _Rows, _Columns>>{
		private:
			std::vector<T>* body = new std::vector<T>(_Rows * _Columns);

			unsigned GetIndex(unsigned i, unsigned j) const {
				return i * _Columns + j;
			}

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
						this->At(i, j) = y;
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
						this->At(i, j) = y;
						++j;
					}
					++i;
				}
			}

			Matrix(const Matrix& expr) {
				if (expr.Rows() != Rows() || expr.Columns() != Columns()) {
					throw DimensionError();;
				}

				OPENMP_PARALLELIZE
				for (unsigned i = 0; i < _Rows; ++i) {
					for (unsigned j = 0; j < _Columns; ++j) {
						this->At(i, j) = expr.At(i, j);
					}
				}
			}

			void operator=(const Matrix& expr) {
				if (expr.Rows() != Rows() || expr.Columns() != Columns()) {
					throw DimensionError();;
				}

				OPENMP_PARALLELIZE
				for (unsigned i = 0; i < _Rows; ++i) {
					for (unsigned j = 0; j < _Columns; ++j) {
						this->At(i, j) = expr.At(i, j);
					}
				}
			}

			template<typename E>
			Matrix(const MatrixBase<T, _Rows, _Columns, E>& expr) {
				if (expr.Rows() != Rows() || expr.Columns() != Columns()) {
					throw DimensionError();;
				}

				auto eval = expr.Evaluate();

				OPENMP_PARALLELIZE
				for (unsigned i = 0; i < _Rows; ++i) {
					for (unsigned j = 0; j < _Columns; ++j) {
						this->At(i, j) = eval.At(i, j);
					}
				}
			}

			template<typename E>
			void operator=(const MatrixBase<T, _Rows, _Columns, E>& expr) {
				if (expr.Rows() != Rows() || expr.Columns() != Columns()) {
					throw DimensionError();;
				}

				auto eval = expr.Evaluate();

				OPENMP_PARALLELIZE
				for (unsigned i = 0; i < _Rows; ++i) {
					for (unsigned j = 0; j < _Columns; ++j) {
						this->At(i, j) = eval.At(i, j);
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

			T& SafeAt(const unsigned& r, const unsigned& c) {
				if (r >= Rows() || c >= Columns())
					throw InvalidAccess();
				return (*body)[GetIndex(r, c)];
			}

			T SafeAt(const unsigned& r, const unsigned& c) const {
				if (r >= Rows() || c >= Columns())
					throw InvalidAccess();

				return (*body)[GetIndex(r, c)];
			}

			T& At(const unsigned& r, const unsigned& c) {
				return (*body)[GetIndex(r, c)];
			}

			T At(const unsigned& r, const unsigned& c) const {
				return (*body)[GetIndex(r, c)];
			}


			template<typename E>
			const Matrix& operator+=(const MatrixBase<T, _Rows, _Columns, E>& expr) {
				
				auto eval = expr.Evaluate();

				OPENMP_PARALLELIZE
				for (unsigned i = 0; i < Rows(); ++i) {
					for (unsigned j = 0; j < Columns(); ++j) {
						this->At(i, j) += eval.At(i, j);
					}
				}

				return *this;
			}

			template<typename E>
			const Matrix& operator-=(const MatrixBase<T, _Rows, _Columns,  E>& expr) {

				auto eval = expr.Evaluate();

				OPENMP_PARALLELIZE
				for (unsigned i = 0; i < Rows(); ++i) {
					for (unsigned j = 0; j < Columns(); ++j) {
						this->At(i, j) -= eval.At(i, j);
					}
				}
				return *this;
			}

			const Matrix& operator*=(const T& c) {

				OPENMP_PARALLELIZE
				for (unsigned i = 0; i < Rows(); ++i) {
					for (unsigned j = 0; j < Columns(); ++j) {
						this->At(i, j) *= c;
					}
				}
				return *this;
			}

			const Matrix& operator/=(const T& c) {
				if (c == 0)
					throw DivisionByZero();

				OPENMP_PARALLELIZE
				for (unsigned i = 0; i < Rows(); ++i) {
					for (unsigned j = 0; j < Columns(); ++j) {
						this->At(i, j) /= c;
					}
				}
				return *this;
			}

			const Matrix& Evaluate() const{
				return (*this);
			}

			void Log() const {
				for (unsigned i = 0; i < _Rows; ++i) {
					for (unsigned j = 0; j < _Columns; ++j) {
						std::cout << this->At(i, j) << " ";
					}
					std::cout << "\n";
				}
			}
		};

	}
}