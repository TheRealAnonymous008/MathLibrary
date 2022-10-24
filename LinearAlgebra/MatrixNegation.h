#pragma once
#include "fwd.h"
#include "Exceptions.h"

namespace MathLib {
	namespace LinearAlgebra {

		namespace detail {
			template<typename T, typename E>
			class MatrixNegation : public MatrixExpression<T, MatrixNegation<T, E>> {
			private:
				const E& expr;
				E* result;

			public:
				MatrixNegation(const E& expr) : expr(expr) {

				}

				T At(const unsigned& r, const unsigned& c) const {
					return  -expr.At(r, c);
				}

				constexpr unsigned Rows() const {
					return  expr.Rows();
				}

				constexpr unsigned Columns() const {
					return  expr.Columns();
				}

				E Evaluate() {
					delete result;
					result = new E();

					for (unsigned i = 0; i < Rows(); ++i) {
						for (unsigned j = 0; j < Columns(); ++j) {
							result->At(i, j) = lhs.At(i, j) + rhs.At(i, j);
						}
					}

					return *result;
				}
			};
		}

		template<typename T, typename E>
		detail::MatrixNegation<T, E> operator-(const MatrixExpression<T, E>& expr) {
			return detail::MatrixNegation<T, E>(*static_cast<const E*>(&expr));
		}

	}
}