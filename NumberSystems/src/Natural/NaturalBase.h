#pragma once

#include "../../headers/Fwd.h"

#include "../Utils/ReverseParse.h"

#include <concepts>

namespace MathLib {
	namespace NumberSystems {
		
		template<typename Derived>
		class NaturalBase {
		private:
			
		public:
			const string_type Val() const {
				return detail::ReverseParse(Digits());
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