#pragma once
#include "fwd.h"
#include "Exceptions.h"

namespace MathLib {
	namespace LinearAlgebra {

		namespace detail {
			template<typename T, typename LHS, typename RHS>
			class VectorSubtraction : public VectorExpression<T, VectorSubtraction<T, LHS, RHS>> {
			private:
				const LHS& lhs;
				const RHS& rhs;

			public:
				VectorSubtraction(const LHS& lhs, const RHS& rhs) : lhs(lhs), rhs(rhs) {
					if (lhs.Size() != rhs.Size()) {
						throw InvalidBinaryOperation();
					}
				}

				T operator[](const unsigned& i) const {
					return lhs[i] - rhs[i];
				}

				constexpr unsigned Size() const {
					return  rhs.Size();
				}

				template<typename Q = T, const unsigned N>
				Vector<Q, N> Evaluate() {

					Vector<Q, N> result;

					for (unsigned i = 0; i < Size(); ++i) {
						result[i] = lhs[i] - rhs[i];
					}

					return result;
				}
			};
		}

		

		template<typename T, typename LHS, typename RHS>
		detail::VectorSubtraction<T, LHS, RHS> operator-(const VectorExpression<T, LHS>& lhs, const VectorExpression<T, RHS>& rhs) {
			return detail::VectorSubtraction<T, LHS, RHS>(*static_cast<const LHS*>(&lhs), *static_cast<const RHS*>(&rhs));
		}

	}
}