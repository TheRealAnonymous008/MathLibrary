#pragma once
#include "fwd.h"

namespace MathLib {
	namespace LinearAlgebra {
		template<typename T, typename E>
		class MatrixExpression {
		private:

		public:
			T At(const unsigned& r, const unsigned& c) const {
				return  static_cast<E const&>(*this).At(r, c);
			}

			unsigned Rows() const {
				return  static_cast<E const&>(*this).Rows();
			}

			unsigned Columns() const {
				return  static_cast<E const&>(*this).Columns();
			}

			template<typename Result>
			Result Evaluate() {
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