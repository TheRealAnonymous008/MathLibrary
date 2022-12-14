#pragma once

#include "../Natural.h"

namespace MathLib {
	namespace NumberSystems {
		namespace implementation {
			
			struct NormalizedDivModResult {
				Natural div;
				Natural mod;
				limb_type D;
			};
		}
	}
}
