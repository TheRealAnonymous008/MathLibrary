#pragma once

#include "../../headers/Fwd.h"

#include <concepts>

namespace MathLib {
	namespace NumberSystems {
		
		template<typename Derived>
		class NaturalBase {
		private:

		public:
			const string_type Val() const {
				std::string result = "";
				for (data_type data : Digits()) {
					result += std::to_string(data);
				}

				return result;
			}

			const vector_type Digits() const {
				return static_cast<Derived const&>(*this).Digits();
			}

			auto Evaluate() const {
				return  static_cast<Derived const&>(*this).Evaluate();
			}
		};
	}
}