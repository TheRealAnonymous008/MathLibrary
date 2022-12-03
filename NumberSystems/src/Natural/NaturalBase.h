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
				
				vector_type digits = Digits();
				for (auto itr = digits.begin(); itr != digits.end() - 1; ++itr) {
					result = detail::ToStringWithPad(*itr) + result;
				}

				result = detail::ToStringNoPad(digits[digits.size() - 1]) + result;

				return result;
			}

			const size_type Size() const {
				return Digits().size();
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