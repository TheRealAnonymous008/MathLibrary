#pragma once

#include "../Natural.h"

namespace MathLib {
	namespace NumberSystems {
		namespace implementation {
			
			struct NormalizedDivModResult {
				Natural div;
				Natural mod;
				Natural D;
			};

			struct DivModResult {
				Natural div;
				Natural mod;
			};
		}
	}
}
