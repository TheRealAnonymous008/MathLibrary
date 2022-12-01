#pragma once

#include "Natural.h"

namespace MathLib {
	namespace NumberSystems {

		namespace detail {

			template<typename LHS, typename RHS>
			class NaturalAddition : NaturalBase<NaturalAddition> {
			private:
				const LHS& lhs;
				const RHS& rhs;

			public: 
				NaturalAddition(const LHS& lhs, const RHS& rhs) : lhs(lhs), rhs(rhs) {
					
				}

			};
		}

		template<typename LHS, typename RHS>
		detail::NaturalAddition<LHS, RHS> operator+(
			const NaturalBase<LHS>& lhs,
			const NaturalBase<RHS>& rhs)
		{
			return detail::NaturalAddition(*static_cast<const LHS*>(&lhs), *static_cast<const RHS*>(&rhs));
		}

	}
}