#pragma once
#include "fwd.h"
#include "Exceptions.h"

namespace MathLib {
	namespace LinearAlgebra {

		namespace detail {
			template<typename T, typename LHS, typename RHS>
			class MatrixAddition : public MatrixExpression<T, MatrixAddition<T, LHS, RHS>> {
			private:
				const LHS& lhs;
				const RHS& rhs;
				RHS* result = nullptr;

			public:
				MatrixAddition(const LHS& lhs, const RHS& rhs) : lhs(lhs), rhs(rhs) {
					if (lhs.Rows() != rhs.Rows() || lhs.Columns() != rhs.Columns()) {
						throw InvalidBinaryOperation();
					}
				}

				T At(const unsigned& r, const unsigned& c) const {
					return  lhs.At(r, c) + rhs.At(r, c);
				}

				unsigned Rows() const {
					return  rhs.Rows();
				}

				unsigned Columns() const {
					return  rhs.Columns();
				}

				RHS Evaluate() {
					result = new RHS();

					for (unsigned i = 0; i < Rows(); ++i) {
						for (unsigned j = 0; j < Columns(); ++j) {
							result->At(i, j) = lhs.At(i, j) + rhs.At(i, j);
						}
					}

					return *result;
				}
			};
		}

		template<typename T, typename LHS, typename RHS>
		detail::MatrixAddition<T, LHS, RHS> operator+(const MatrixExpression<T, LHS>& lhs, const MatrixExpression<T, RHS>& rhs) {
			return detail::MatrixAddition<T, LHS, RHS>(*static_cast<const LHS*>(&lhs), *static_cast<const RHS*>(&rhs));
		}
	}
}