#pragma once
#include "fwd.h"

namespace MathLib {
	namespace LinearAlgebra {
		template<typename T, typename E>
		class MatrixExpression {
		public:
			T At(const unsigned& r, const unsigned& c) const {
				return  static_cast<E const&>(*this).At(r, c);
			}

			constexpr unsigned Rows() const {
				return  static_cast<E const&>(*this).Rows();
			}

			constexpr unsigned Columns() const {
				return  static_cast<E const&>(*this).Columns();
			}

			template<typename Q = T, const unsigned _Rows, const unsigned _Columns>
			Matrix<Q, _Rows, _Columns> Evaluate() const{
				return static_cast<E const&>(*this).Evaluate();
			}
		};

		template<typename T, typename LHS, typename RHS>
		bool operator==(const MatrixExpression<T, LHS>& lhs, const MatrixExpression<T, RHS>& rhs) {
			if (lhs.Rows() != rhs.Rows()) 
				return false;
			if (lhs.Columns() != rhs.Columns())
				return false;

			for (unsigned i = 0; i < lhs.Rows(); ++i) {
				for (unsigned j = 0; j < lhs.Columns(); ++j) {
					if (lhs.At(i, j) != rhs.At(i, j))
						return false;
				}
			}
			return true;
		}

		template<typename T, typename LHS, typename RHS>
		bool operator!=(const MatrixExpression<T, LHS>& lhs, const MatrixExpression<T, RHS>& rhs) {
			if (lhs.Rows() != rhs.Rows())
				return false;
			if (lhs.Columns() != rhs.Columns())
				return false;

			for (unsigned i = 0; i < lhs.Rows(); ++i) {
				for (unsigned j = 0; j < lhs.Columns(); ++j) {
					if (lhs.At(i, j) != rhs.At(i, j))
						return true;
				}
			}
			return false;
		}
	}
}