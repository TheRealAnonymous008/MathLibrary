#pragma once
#include "fwd.h"
#include "Exceptions.h"

namespace MathLib {
	namespace LinearAlgebra {

		namespace detail {
			template<typename T, const unsigned _Rows, const unsigned _Columns, typename LHS, typename RHS>
			class MatrixSubtraction : public MatrixExpression<T, _Rows, _Columns, 
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

				T At(const unsigned& r, const unsigned& c) const {
					return  lhs.At(r, c) - rhs.At(r, c);
				}

				constexpr unsigned Rows() const {
					return  _Rows;
				}

				constexpr unsigned Columns() const {
					return  _Columns;
				}

				auto Evaluate() const {

					Matrix<T,  _Rows, _Columns> result;

					for (unsigned i = 0; i < Rows(); ++i) {
						for (unsigned j = 0; j < Columns(); ++j) {
							result.At(i, j) = lhs.At(i, j) - rhs.At(i, j);
						}
					}

					return result;
				}
			};
		}

		
		template<
			typename T, 
			const unsigned _Rows, const unsigned _Columns, 
			typename LHS, typename RHS
		>

		detail::MatrixSubtraction<T, _Rows, _Columns, LHS, RHS> operator-(
			const MatrixExpression<T, _Rows, _Columns, LHS>& lhs, 
			const MatrixExpression<T, _Rows, _Columns, RHS>& rhs) 
		{
			return detail::MatrixSubtraction<T, _Rows, _Columns, LHS, RHS>(*static_cast<const LHS*>(&lhs), *static_cast<const RHS*>(&rhs));
		}

	}
}