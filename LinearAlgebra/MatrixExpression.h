#pragma once
#include "fwd.h"

namespace MathLib {
	namespace LinearAlgebra {
		template<typename T, const unsigned _Rows, const unsigned _Columns, typename Derived>
		class MatrixBase {
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
			const MatrixBase<T, Rows, Columns, LHS>& lhs, 
			const MatrixBase<T, Rows, Columns, RHS>& rhs) 
		{
			if (lhs.Rows() != rhs.Rows()) 
				return false;
			if (lhs.Columns() != rhs.Columns())
				return false;

			auto left = lhs.Evaluate();
			auto right = rhs.Evaluate();

			for (unsigned i = 0; i < lhs.Rows(); ++i) {
				for (unsigned j = 0; j < lhs.Columns(); ++j) {
					if (left.At(i, j) != right.At(i, j))
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
			const MatrixBase<T, Rows, Columns, LHS>& lhs, 
			const MatrixBase<T, Rows, Columns, RHS>& rhs) 
		{
			if (lhs.Rows() != rhs.Rows())
				return false;
			if (lhs.Columns() != rhs.Columns())
				return false;

			auto left = lhs.Evaluate();
			auto right = rhs.Evaluate();

			for (unsigned i = 0; i < lhs.Rows(); ++i) {
				for (unsigned j = 0; j < lhs.Columns(); ++j) {
					if (left.At(i, j) != right.At(i, j))
						return true;
				}
			}

			return false;
		}
	}
}