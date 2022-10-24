#pragma once
#include "fwd.h"
#include "Exceptions.h"

namespace MathLib {
	namespace LinearAlgebra {

		namespace detail {
			template<typename T, typename LHS>
			class VectorNegation : public VectorExpression<T, VectorNegation<T, LHS>> {
			private:
				const LHS& lhs;

			public:
				VectorNegation(const LHS& lhs) : lhs(lhs) {

				}

				T operator[](const unsigned& i) const {
					return -lhs[i];
				}

				unsigned Size() const {
					return  lhs.Size();
				}
			};
		}

		using namespace detail;

		template<typename T, typename LHS>
		VectorNegation<T, LHS> operator-(const VectorExpression<T, LHS>& lhs) {
			return VectorNegation<T, LHS>(*static_cast<const LHS*>(&lhs));
		}

	}
}