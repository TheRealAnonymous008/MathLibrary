#pragma once

#include "../../headers/Fwd.h"

#include <concepts>

namespace MathLib {
	namespace NumberSystems {
		
		template<typename Derived>
		class NaturalBase {
			
		};

		template<class T>
		concept IsNaturalNumber = requires(T t) {
			[] <typename X>(NaturalBase<X>&) {}(t);
		};
	}
}