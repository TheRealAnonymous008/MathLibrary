#pragma once

#include "SquareOps.h"
#include <concepts>

namespace MathLib {
	namespace LinearAlgebra {

		template<typename T, size_type N>
		class IdentityMatrix : public SquareMatrixBase<T, N,
			IdentityMatrix<T, N>> {
		private:
			
		public:
			T At(index_type i, index_type j) const {
				return (i != j) ? T() : Identity<T>();
			}

			constexpr size_type Rows() const {
				return N;
			}

			constexpr size_type Columns() const {
				return N;
			}

			auto Evaluate() const {
				SquareMatrix<T, N> result;
				for (index_type i = 0; i < N; ++i) {
					result.At(i, i) = Identity<T>();
				}

				return result;
			}
		};

		template<typename Expr, typename T, size_type N>
		concept IsNotIdentityMatrix = (std::_Not_same_as<Expr, IdentityMatrix<T, N>>);

		template<typename T, size_type _Rows, size_type N, typename Expr> 
		const MatrixBase<T, _Rows, N, Expr>& operator*(
			const MatrixBase<T, _Rows, N, Expr>& lhs,
			const IdentityMatrix<T, N>& rhs)
		{
			return lhs;
		}

		template<typename T, size_type N, size_type _Columns, typename Expr>
		requires IsNotIdentityMatrix<Expr, T, N>
		const MatrixBase<T, N, _Columns, Expr>& operator*(
			const IdentityMatrix<T, N>& lhs,
			const MatrixBase<T, N, _Columns, Expr>& rhs)
		{
			return rhs;
		}
	}
}