#pragma once

#include "PermutationMatrix.h"
#include <concepts>

namespace MathLib {
	namespace LinearAlgebra {

		namespace detail {
			template<typename T, const unsigned _Rows, const unsigned _Columns, typename Expr >
			class MatrixRowPermutation : public MatrixBase<T, _Rows, _Columns,
				MatrixRowPermutation<T, _Rows, _Columns, Expr>> {
			private:
				const Expr& expr;
				const PermutationMatrix<T, _Rows>& permutation;

			public:
				MatrixRowPermutation(const PermutationMatrix<T, _Rows>& permutation, const Expr& expr) : expr(expr), permutation(permutation)
				{
					if (permutation.Columns() != expr.Rows()) {
						throw InvalidTensorProduct();
					}
				}

				T At(const unsigned& r, const unsigned& c) const {
					return expr.At(permutation.Map(r), c);
				}

				constexpr unsigned Rows() const {
					return  expr.Rows();
				}

				constexpr unsigned Columns() const {
					return  expr.Columns();
				}

				auto Evaluate() const {
					Matrix<T, _Rows, _Columns> result;

					OPENMP_PARALLELIZE
					for (unsigned i = 0; i < _Rows; ++i) {
						for (unsigned j = 0; j < _Columns; ++j) {
							result.At(i, j) = this->At(i, j);
						}
					}

					return result;
				}
			};

			template<typename T, const unsigned _Rows, const unsigned _Columns, typename Expr >
			class MatrixColumnPermutation : public MatrixBase<T, _Rows, _Columns,
				MatrixColumnPermutation<T, _Rows, _Columns, Expr>> {
			private:
				const Expr& expr;
				const PermutationMatrix<T, _Columns>& permutation;

			public:
				MatrixColumnPermutation(const Expr& expr, const PermutationMatrix<T, _Columns>& permutation) : expr(expr), permutation(permutation)
				{
					if (expr.Columns() != permutation.Rows()) {
						throw InvalidTensorProduct();
					}
				}

				T At(const unsigned& r, const unsigned& c) const {
					return expr.At(r, permutation.Map(c));
				}

				constexpr unsigned Rows() const {
					return  expr.Rows();
				}

				constexpr unsigned Columns() const {
					return  expr.Columns();
				}

				auto Evaluate() const {
					Matrix<T, _Rows, _Columns> result;

					OPENMP_PARALLELIZE
					for (unsigned i = 0; i < _Rows; ++i) {
						for (unsigned j = 0; j < _Columns; ++j) {
							result.At(i, j) = this->At(i, j);
						}
					}

					return result;
				}
			};

			template<typename T, const unsigned N >
			class PermutationComposition : public MatrixBase<T, N, N,
				PermutationComposition<T, N>> {
			private:
				const PermutationMatrix<T, N>& left;
				const PermutationMatrix<T, N>& right;

			public:
				PermutationComposition(const PermutationMatrix<T, N>& left, const PermutationMatrix<T, N>& right) : left(left), right(right)
				{

				}

				T At(const unsigned& r, const unsigned& c) const {
					return right.At(left.Map(r), c);
				}

				constexpr unsigned Rows() const {
					return  N;
				}

				constexpr unsigned Columns() const {
					return  N;
				}

				auto Evaluate() const {
					std::vector<unsigned> arr = std::vector<unsigned>(N);

					OPENMP_PARALLELIZE
					for (unsigned i = 0; i < N; ++i) {
						arr[i] = right.Map(left.Map(i));
					}

					return PermutationMatrix<T, N>(arr);
				}
			};
		}


		template<typename T, const unsigned _Rows, const unsigned _Columns, typename Expr>
		requires IsNotIdentityMatrix<Expr, T, _Columns>
		detail::MatrixRowPermutation<T, _Rows, _Columns, Expr> operator*(
			const PermutationMatrix<T, _Rows>& lhs,
			const MatrixBase<T, _Rows, _Columns, Expr>& rhs)
		{
			return  detail::MatrixRowPermutation<T, _Rows, _Columns, Expr>(lhs, *static_cast<const Expr*>(&rhs));;
		}

		template<typename T, const unsigned _Rows, const unsigned _Columns, typename Expr>\
		requires IsNotIdentityMatrix<Expr, T, _Columns>
		detail::MatrixColumnPermutation<T, _Rows, _Columns, Expr> operator*(
			const MatrixBase<T, _Rows, _Columns, Expr>& lhs,
			const PermutationMatrix<T, _Columns>& rhs)
		{
			return  detail::MatrixColumnPermutation<T, _Rows, _Columns, Expr>(*static_cast<const Expr*>(&lhs), rhs);;
		}

		template<typename T, const unsigned N>
		detail::PermutationComposition<T, N> operator*(
			const PermutationMatrix<T, N>& lhs,
			const PermutationMatrix<T, N>& rhs)
		{
			return  detail::PermutationComposition<T, N>(lhs, rhs);;
		}
	}
}