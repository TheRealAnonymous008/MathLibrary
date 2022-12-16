#pragma once

#include "../../headers/Fwd.h"

namespace MathLib {
	namespace LinearAlgebra {
		template<typename T, size_type _Rows, size_type _Columns, typename Derived>
		class MatrixBase {
		public:
			T At(const index_type& r, const index_type& c) const {
				return  static_cast<Derived const&>(*this).At(r, c);
			}

			constexpr size_type Rows() const {
				return _Rows;
			}

			constexpr size_type Columns() const {
				return _Columns;
			}

			constexpr size_type Size() const {
				return _Rows * _Columns;
			}

			auto Evaluate() const{
				return static_cast<Derived const&>(*this).Evaluate();
			}
		};

		template<
			typename T, 
			size_type Rows, size_type Columns,
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

			for (index_type i = 0; i < lhs.Rows(); ++i) {
				for (index_type j = 0; j < lhs.Columns(); ++j) {
					if (left.At(i, j) != right.At(i, j))
						return false;
				}
			}
			return true;
		}

		template<
			typename T, 
			size_type Rows, size_type Columns, 
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

			for (index_type i = 0; i < lhs.Rows(); ++i) {
				for (index_type j = 0; j < lhs.Columns(); ++j) {
					if (left.At(i, j) != right.At(i, j))
						return true;
				}
			}

			return false;
		}
	}
}