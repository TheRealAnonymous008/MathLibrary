#pragma once

#include "../../headers/Fwd.h"

namespace MathLib {
	namespace NumberSystems {

		template<typename Derived>
		class RealBase {

		protected:

		public:
			auto Evaluate() const {
				return static_cast<Derived const&>(*this).Evaluate();
			}
		};
	}
}