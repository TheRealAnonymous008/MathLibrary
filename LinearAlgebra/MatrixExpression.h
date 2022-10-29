#pragma once
#include "fwd.h"

namespace MathLib {
	namespace LinearAlgebra {
		template<typename T, const unsigned Rows, const unsigned Columns, typename Derived>
		class MatrixExpression {
		public:
			T At(const unsigned& r, const unsigned& c) const {
				return  static_cast<Derived const&>(*this).At(r, c);
			}

			constexpr unsigned Rows() const {
				return  static_cast<Derived const&>(*this).Rows();
			}

			constexpr unsigned Columns() const {
				return  static_cast<Derived const&>(*this).Columns();
			}

			auto Evaluate() const{
				return static_cast<Derived const&>(*this).Evaluate();
			}
		};

		template<
			typename T, 
			const unsigned Rows, const unsigned Columns,
			typename LHS, typename RHS
		>
		bool operator==(
			const MatrixExpression<T, Rows, Columns, LHS>& lhs, 
			const MatrixExpression<T, Rows, Columns, RHS>& rhs) 
		{
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

		template<
			typename T, 
			const unsigned Rows, const unsigned Columns, 
			typename LHS, typename RHS
		>
		bool operator!=(
			const MatrixExpression<T, Rows, Columns, LHS>& lhs, 
			const MatrixExpression<T, Rows, Columns, RHS>& rhs) 
		{
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