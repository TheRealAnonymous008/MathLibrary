#pragma once
#include "fwd.h"
#include "Exceptions.h"

namespace MathLib {
	namespace LinearAlgebra {

		namespace detail {
			template<typename T, const unsigned N, typename LHS, typename RHS>
			class VectorAddition : public VectorExpression<T, N,
				VectorAddition<T, N, LHS, RHS>> {
			private:
				const LHS& lhs;
				const RHS& rhs;

			public:
				VectorAddition(const LHS& lhs, const RHS& rhs) : lhs(lhs), rhs(rhs) {
					if (lhs.Size() != rhs.Size()) {
						throw InvalidBinaryOperation();
					}
				}

				T operator[](const unsigned& i) const {
					return lhs[i] + rhs[i];
				}

				constexpr unsigned Size() const {
					return  rhs.Size();
				}

				auto Evaluate() const{

					Vector<T, N> result;

					for (unsigned i = 0; i < Size(); ++i) {
						result[i] = lhs[i] + rhs[i];
					}

					return result;
				}
			};
		}

		

		template<
			typename T, 
			const unsigned N, 
			typename LHS, typename RHS
		>
		detail::VectorAddition<T, N, LHS, RHS> operator+(
			const VectorExpression<T, N, LHS>& lhs, 
			const VectorExpression<T, N, RHS>& rhs) 
		{
			return detail::VectorAddition<T, N, LHS, RHS>(*static_cast<const LHS*>(&lhs), *static_cast<const RHS*>(&rhs));
		}

	}
}