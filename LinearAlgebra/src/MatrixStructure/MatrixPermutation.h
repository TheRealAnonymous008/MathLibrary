#pragma once

#include "SpecialMatrices/PermutationMatrix.h"
#include <concepts>

namespace MathLib {
	namespace LinearAlgebra {

		namespace detail {
			template<typename T, size_type _Rows, size_type _Columns, typename Expr >
			class MatrixRowPermutation : public MatrixBase<T, _Rows, _Columns,
				MatrixRowPermutation<T, _Rows, _Columns, Expr>> {
			private:
				const Matrix<T, _Rows, _Columns>& expr;
				const PermutationMatrix<T, _Rows>& permutation;

			public:
				MatrixRowPermutation(const PermutationMatrix<T, _Rows>& permutation, const Expr& expr) : 
					expr(expr.Evaluate()), permutation(permutation)
				{
					if (permutation.Columns() != expr.Rows()) {
						throw InvalidTensorProduct();
					}
				}

				T At(const index_type& r, const index_type& c) const {
					return expr.At(permutation.Map(r), c);
				}

				auto Evaluate() const {
					Matrix<T, _Rows, _Columns> result;

					OPENMP_PARALLELIZE
					for (index_type i = 0; i < _Rows; ++i) {
						for (index_type j = 0; j < _Columns; ++j) {
							result.At(i, j) = this->At(i, j);
						}
					}

					return result;
				}
			};

			template<typename T, size_type _Rows, size_type _Columns, typename Expr >
			class MatrixColumnPermutation : public MatrixBase<T, _Rows, _Columns,
				MatrixColumnPermutation<T, _Rows, _Columns, Expr>> {
			private:
				const Matrix<T, _Rows, _Columns>& expr;
				const PermutationMatrix<T, _Columns>& permutation;

			public:
				MatrixColumnPermutation(const Expr& expr, const PermutationMatrix<T, _Columns>& permutation) : 
					expr(expr.Evaluate()), permutation(permutation)
				{
					if (expr.Columns() != permutation.Rows()) {
						throw InvalidTensorProduct();
					}
				}

				T At(const index_type& r, const index_type& c) const {
					return expr.At(r, permutation.Map(c));
				}

				constexpr size_type Rows() const {
					return  expr.Rows();
				}

				constexpr size_type Columns() const {
					return  expr.Columns();
				}

				auto Evaluate() const {
					Matrix<T, _Rows, _Columns> result;

					OPENMP_PARALLELIZE
					for (index_type i = 0; i < _Rows; ++i) {
						for (index_type j = 0; j < _Columns; ++j) {
							result.At(i, j) = this->At(i, j);
						}
					}

					return result;
				}
			};

			template<typename T, size_type N >
			class PermutationComposition : public MatrixBase<T, N, N,
				PermutationComposition<T, N>> {
			private:
				const PermutationMatrix<T, N>& left;
				const PermutationMatrix<T, N>& right;

			public:
				PermutationComposition(const PermutationMatrix<T, N>& left, const PermutationMatrix<T, N>& right) : left(left), right(right)
				{

				}

				T At(const index_type& r, const index_type& c) const {
					return right.At(left.Map(r), c);
				}

				constexpr size_type Rows() const {
					return  N;
				}

				constexpr size_type Columns() const {
					return  N;
				}

				auto Evaluate() const {
					std::vector<index_type> arr = std::vector<index_type>(N);

					OPENMP_PARALLELIZE
					for (index_type i = 0; i < N; ++i) {
						arr[i] = right.Map(left.Map(i));
					}

					return PermutationMatrix<T, N>(arr);
				}
			};

			template<typename T, size_type N >
			class RowVectorPermutation : public VectorBase<T, N,
				RowVectorPermutation<T, N>> {
			private:
				const PermutationMatrix<T, N>& left;
				const Vector<T, N> right;			// TODO: This needs to be a reference, but when it is, it throws an error because it tries to modify a non-copy.

			public:
				RowVectorPermutation(const PermutationMatrix<T, N>& left, const  Vector<T, N>& right) : left(left), right(right)
				{

				}

				T operator[](const index_type& i) const {
					return right[left.Map(i)];
				}

				constexpr size_type Size() const {
					return right.Size();
				}

				auto Evaluate() const {

					Vector<T, N> result;

					OPENMP_PARALLELIZE
					for (index_type i = 0; i < N; ++i) {
						result[i] = right[left.Map(i)];
					}

					return result;
				}
			};
		}


		template<typename T, size_type _Rows, size_type _Columns, typename Expr>
		requires IsNotIdentityMatrix<Expr, T, _Columns>
		detail::MatrixRowPermutation<T, _Rows, _Columns, Expr> operator*(
			const PermutationMatrix<T, _Rows>& lhs,
			const MatrixBase<T, _Rows, _Columns, Expr>& rhs)
		{
			return  detail::MatrixRowPermutation<T, _Rows, _Columns, Expr>(lhs, *static_cast<const Expr*>(&rhs));;
		}

		template<typename T, size_type _Rows, size_type _Columns, typename Expr>\
		requires IsNotIdentityMatrix<Expr, T, _Columns>
		detail::MatrixColumnPermutation<T, _Rows, _Columns, Expr> operator*(
			const MatrixBase<T, _Rows, _Columns, Expr>& lhs,
			const PermutationMatrix<T, _Columns>& rhs)
		{
			return  detail::MatrixColumnPermutation<T, _Rows, _Columns, Expr>(*static_cast<const Expr*>(&lhs), rhs);;
		}

		template<typename T, size_type N>
		detail::PermutationComposition<T, N> operator*(
			const PermutationMatrix<T, N>& lhs,
			const PermutationMatrix<T, N>& rhs)
		{
			return  detail::PermutationComposition<T, N>(lhs, rhs);;
		}

		template<typename T, size_type N, typename Expr>
		detail::RowVectorPermutation<T, N> operator*(
			const PermutationMatrix<T, N>& lhs,
			const VectorBase<T, N, Expr>& rhs)
		{
			return  detail::RowVectorPermutation<T, N>(lhs, *static_cast<const Expr*>(&rhs));;
		}
	}
}