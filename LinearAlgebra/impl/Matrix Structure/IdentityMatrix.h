#pragma once

#include "SquareOps.h"
#include <concepts>

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
				for (unsigned i = 0; i < N; ++i) {
					result.At(i, i) = Identity<T>();
				}

				return result;
			}
		};

		template<typename Expr, typename T, const unsigned N>
		concept IsNotIdentityMatrix = (std::_Not_same_as<Expr, IdentityMatrix<T, N>>);

		template<typename T, const unsigned _Rows, const unsigned N, typename Expr> 
		const MatrixBase<T, _Rows, N, Expr>& operator*(
			const MatrixBase<T, _Rows, N, Expr>& lhs,
			const IdentityMatrix<T, N>& rhs)
		{
			return lhs;
		}

		template<typename T, const unsigned N, const unsigned _Columns, typename Expr>
		requires IsNotIdentityMatrix<Expr, T, N>
		const MatrixBase<T, N, _Columns, Expr>& operator*(
			const IdentityMatrix<T, N>& lhs,
			const MatrixBase<T, N, _Columns, Expr>& rhs)
		{
			return rhs;
		}
	}
}