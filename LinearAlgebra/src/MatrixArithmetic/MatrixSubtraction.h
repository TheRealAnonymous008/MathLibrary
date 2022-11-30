#pragma once

#include "../../Exceptions.h"

#include "../Objects/Matrix.h"
#include "../Objects/MatrixBase.h"

namespace MathLib {
	namespace LinearAlgebra {

		namespace detail {
			template<typename T, size_type _Rows, size_type _Columns, typename LHS, typename RHS>
			class MatrixSubtraction : public MatrixBase<T, _Rows, _Columns, 
				MatrixSubtraction<T, _Rows, _Columns, LHS, RHS>> {
			private:
				const LHS& lhs;
				const RHS& rhs;
				RHS* result = nullptr;

			public:
				MatrixSubtraction(const LHS& lhs, const RHS& rhs) : lhs(lhs), rhs(rhs) {
					if (lhs.Rows() != rhs.Rows() || lhs.Columns() != rhs.Columns()) {
						throw InvalidBinaryOperation();
					}
				}

				T At(const index_type& r, const index_type& c) const {
					return  lhs.At(r, c) - rhs.At(r, c);
				}

				constexpr size_type Rows() const {
					return  _Rows;
				}

				constexpr size_type Columns() const {
					return  _Columns;
				}

				auto Evaluate() const {

					Matrix<T,  _Rows, _Columns> result;

					OPENMP_PARALLELIZE
					for (index_type i = 0; i < _Rows; ++i) {
						for (index_type j = 0; j < _Columns; ++j) {
							result.At(i, j) = lhs.At(i, j) - rhs.At(i, j);
						}
					}

					return result;
				}
			};
		}

		
		template<typename T,  size_type _Rows, size_type _Columns, typename LHS, typename RHS>
		detail::MatrixSubtraction<T, _Rows, _Columns, LHS, RHS> operator-(
			const MatrixBase<T, _Rows, _Columns, LHS>& lhs, 
			const MatrixBase<T, _Rows, _Columns, RHS>& rhs) 
		{
			return detail::MatrixSubtraction<T, _Rows, _Columns, LHS, RHS>(*static_cast<const LHS*>(&lhs), *static_cast<const RHS*>(&rhs));
		}

	}
}