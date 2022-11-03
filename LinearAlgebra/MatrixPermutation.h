#pragma once

#include "PermutationMatrix.h"

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
					if (expr.Columns() != permutation.Rows()) {
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

					for (unsigned i = 0; i < _Rows; ++i) {
						for (unsigned j = 0; j < _Columns; ++j) {
							result.At(i, j) = this->At(i, j);
						}
					}

					return result;
				}
			};
		}


		template<typename T, const unsigned _Rows, const unsigned _Columns, typename Expr>
		detail::MatrixRowPermutation<T, _Rows, _Columns, Expr> operator*(
			const PermutationMatrix<T, _Rows>& lhs,
			const MatrixBase<T, _Rows, _Columns, Expr>& rhs)
		{
			return  detail::MatrixRowPermutation<T, _Rows, _Columns, Expr>(lhs, *static_cast<const Expr*>(&rhs));;
		}

	}
}