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

			public:
				MatrixNegation(const E& expr) : expr(expr) {

				}

				T At(const unsigned& r, const unsigned& c) const {
					if (isEvaluated) {
						return body[r][c];
					}
					return  -expr.At(r, c);
				}

				constexpr unsigned Rows() const {
					return  expr.Rows();
				}

				constexpr unsigned Columns() const {
					return  expr.Columns();
				}

				const MatrixNegation& Evaluate() {

					body = std::vector<std::vector<T>>(Rows(), std::vector<T>(Columns()));

					for (unsigned i = 0; i < Rows(); ++i) {
						for (unsigned j = 0; j < Columns(); ++j) {
							body[i][j] = -expr.At(i, j);
						}
					}

					return *this;
				}
			};
		}

		template<typename T, typename E>
		detail::MatrixNegation<T, E> operator-(const MatrixExpression<T, E>& expr) {
			return detail::MatrixNegation<T, E>(*static_cast<const E*>(&expr));
		}

	}
}