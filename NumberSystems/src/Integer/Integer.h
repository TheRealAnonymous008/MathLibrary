#pragma once
#include "../../headers/Fwd.h"
#include "../../Exceptions.h"
#include "../Utils/Parse.h"

#include "IntegerBase.h"

#include <vector>

namespace MathLib {
	namespace NumberSystems {

		enum IntegerSign {
			POSITIVE = 0,
			NEGATIVE = 1
		};

		class Integer : public IntegerBase<Integer> {
		private:
			bool sign = POSITIVE;
			vector_type* body = new vector_type();


		public:
			Integer() {

			}

		};
	}
}