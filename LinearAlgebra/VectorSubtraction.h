#pragma once
#include "fwd.h"
#include "Exceptions.h"

namespace MathLib {
	namespace LinearAlgebra {

		namespace detail {
			template<typename T, const unsigned N, typename LHS, typename RHS>
			class VectorSubtraction : public VectorBase<T, N,
				VectorSubtraction<T, N, LHS, RHS>> {
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

				auto Evaluate() const{

					Vector<T, N> result;

					for (unsigned i = 0; i < N; ++i) {
						result[i] = lhs[i] - rhs[i];
					}

					return result;
				}
			};
		}

		

		template<typename T, const unsigned N,typename LHS, typename RHS>
		detail::VectorSubtraction<T, N, LHS, RHS> operator-(
			const VectorBase<T, N, LHS>& lhs, 
			const VectorBase<T, N, RHS>& rhs) 
		{
			return detail::VectorSubtraction<T, N, LHS, RHS>(*static_cast<const LHS*>(&lhs), *static_cast<const RHS*>(&rhs));
		}

	}
}