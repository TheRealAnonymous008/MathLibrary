#pragma once

#include "../../headers/Fwd.h"

namespace MathLib {
	namespace NumberSystems {
		
		template<typename Derived>
		class NaturalBase {
		protected:
			
		public:
			auto Evaluate() const {
				return  static_cast<Derived const&>(*this).Evaluate();
			}
		};
	}
}