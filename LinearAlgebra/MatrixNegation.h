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
					return  -expr.At(r, c);
				}

				unsigned Rows() const {
					return  expr.Rows();
				}

				unsigned Columns() const {
					return  expr.Columns();
				}
			};
		}

		template<typename T, typename E>
		detail::MatrixNegation<T, E> operator-(const MatrixExpression<T, E>& expr) {
			return detail::MatrixNegation<T, E>(*static_cast<const E*>(&expr));
		}

	}
}