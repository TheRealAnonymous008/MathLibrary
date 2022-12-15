#pragma once

#include "Natural.h"
#include "../../Exceptions.h"

namespace MathLib {
	namespace NumberSystems {

		template<typename Expr>
		unsigned long long ToULL(const NaturalBase<Expr>& expr) {
			auto digits = expr.Evaluate().Digits();
			unsigned long long result = 0; 
			
			for (auto d : digits) {
				auto next = result * LIMB_BASE + d;
				if (next < result) {
					throw NarrowingConversionError();
				}

				result = next;
			}

			return result;
		}

	}
}