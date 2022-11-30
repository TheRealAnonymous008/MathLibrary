#pragma once

#include "../../Exceptions.h"

#include "../Objects/VectorBase.h"
#include "../Objects/Vector.h"

namespace MathLib {
	namespace LinearAlgebra {

		namespace detail {
			template<typename T, size_type N, typename LHS, typename RHS>
			class VectorAddition : public VectorBase<T, N,
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

				T operator[](const index_type& i) const {
					return lhs[i] + rhs[i];
				}

				constexpr size_type Size() const {
					return  rhs.Size();
				}

				auto Evaluate() const{

					Vector<T, N> result;

					OPENMP_PARALLELIZE
					for (index_type i = 0; i < N; ++i) {
						result[i] = lhs[i] + rhs[i];
					}

					return result;
				}
			};
		}

		

		template<typename T, size_type N, typename LHS, typename RHS>
		detail::VectorAddition<T, N, LHS, RHS> operator+(
			const VectorBase<T, N, LHS>& lhs, 
			const VectorBase<T, N, RHS>& rhs) 
		{
			return detail::VectorAddition<T, N, LHS, RHS>(*static_cast<const LHS*>(&lhs), *static_cast<const RHS*>(&rhs));
		}

	}
}