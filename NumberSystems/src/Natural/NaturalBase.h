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

				vector_type digits = Digits();
				if (digits.size() == 0) {
					return "0";
				}

				std::string result = "";
				for (auto itr = digits.begin(); itr != digits.end() - 1; ++itr) {
					result = detail::ToStringWithPad(*itr) + result;
				}

				result = detail::ToStringNoPad(digits[digits.size() - 1]) + result;

				return result;
			}

			limb_type operator[](index_type idx) const {
				return this->Digits()[idx];
			}

			const size_type Size() const {
				return Digits().size();
			}

			const vector_type Digits() const{
				return static_cast<Derived const&>(*this).Digits();
			}

			auto Evaluate() const {
				return  static_cast<Derived const&>(*this).Evaluate();
			}
		};
	}
}