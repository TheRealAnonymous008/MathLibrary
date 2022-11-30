#include "../../headers/Fwd.h"
#include "NaturalBase.h"

#include "../../Exceptions.h"

namespace MathLib {
	namespace NumberSystems {

		class Natural : NaturalBase{
		private:
			string_type value;

		public :
			Natural(string_type value = "0") : value(value) {

			}

			string_type Val() const {
				return this->value;
			}
		};

	}
}