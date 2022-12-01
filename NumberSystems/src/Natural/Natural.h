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
			std::vector<data_type>* body = new std::vector<data_type>();

		public :
			Natural(const string_type value = "0") {
				*body = detail::Parse(value);
			}

			const string_type Val() const {
				std::string result = "";
				for (data_type data : *body) {
					result += std::to_string(data);
				}

				return result;
			}

			const std::vector<data_type> Digits() const {
				return *this->body;
			}

			const Natural& Evaluate() const{
				return *this;
			}
		};

	}
}