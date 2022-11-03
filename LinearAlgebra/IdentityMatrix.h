#pragma once

#include "fwd.h"
#include "SquareOps.h"

namespace MathLib {
	namespace LinearAlgebra {

		template<typename T, const unsigned N>
		class IdentityMatrix : public SquareMatrixBase<T, N,
			IdentityMatrix<T, N>> {
		private:

		public:
			T At(unsigned i, unsigned j) const {
				return (i != j) ? T() : Identity<T>();
			}

			constexpr unsigned Rows() const {
				return N;
			}

			constexpr unsigned Columns() const {
				return N;
			}

			auto Evaluate() const {
				SquareMatrix<T, N> result;
				for (unsigned i = 0; i, N; ++i) {
					result.At(i, i) = Identity<T>();
				}

				return result;
			}
		};

		template<typename T, const unsigned N>
		const IdentityMatrix<T, N>& operator*(
			const IdentityMatrix<T, N>& lhs,
			const IdentityMatrix<T, N>& rhs)
		{
			return lhs;
		}

		template<typename T, const unsigned N, typename Expr>
		const SquareMatrixBase<T, N, Expr>& operator*(
			const SquareMatrixBase<T, N, Expr>& lhs,
			const IdentityMatrix<T, N>& rhs)
		{
			return lhs;
		}

		template<typename T, const unsigned N, typename Expr>
		const SquareMatrixBase<T, N, Expr>& operator*(
			const IdentityMatrix<T, N>& lhs,
			const SquareMatrixBase<T, N, Expr>& rhs)
		{
			return rhs;
		}
	}
}