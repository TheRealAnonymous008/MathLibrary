#pragma once

#include "Natural.h"

namespace MathLib {
	namespace NumberSystems {

		namespace detail {

			template<typename LHS, typename RHS>
			class NaturalAddition : NaturalBase<NaturalAddition<LHS, RHS>> {
			private:
				const LHS& lhs;
				const RHS& rhs;

			public: 
				NaturalAddition(const LHS& lhs, const RHS& rhs) : lhs(lhs), rhs(rhs) {
					
				}

			};
		}

		template<typename LHS, typename RHS>
		requires IsNaturalNumber<LHS> && IsNaturalNumber<RHS>
		detail::NaturalAddition<LHS, RHS> operator+(
			const LHS& lhs,
			const RHS& rhs)
		{
			return detail::NaturalAddition(lhs, rhs);
		}

	}
}