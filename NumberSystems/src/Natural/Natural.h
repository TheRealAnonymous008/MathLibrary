#pragma once
#include "../../headers/Fwd.h"
#include "../../Exceptions.h"
#include "../Utils/Parse.h"

#include "NaturalBase.h"

#include <vector>

namespace MathLib {
	namespace NumberSystems {

		class Natural : public NaturalBase<Natural>{
		private:
			vector_type* body = new vector_type();

		public :
			Natural(const string_type value = "0") {
				*body = detail::Parse(value);
			}

			~Natural() {

			}

			void operator=(const string_type value) {
				*body = detail::Parse(value)
			}

			void operator=(const Natural& expr) {
				this->body = expr.body;
			}

			template<typename E>
			Natural(const NaturalBase<E>& expr) {
				*this->body = expr.Digits();
			}

			template<typename E>
			void operator=(const NaturalBase<E>& expr) {
				*this->body = expr.Digits();
			}

			const vector_type Digits() const {
				return *this->body;
			}

			const Natural& Evaluate() const{
				return *this;
			}
		};

	}
}