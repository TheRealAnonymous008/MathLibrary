#include "../../headers/Fwd.h"
#include "../../Exceptions.h"

#include "NaturalBase.h"

#include <vector>

namespace MathLib {
	namespace NumberSystems {

		class Natural : NaturalBase{
		private:
			std::vector<data_type>* body = new std::vector<unsigned>();

			std::vector<data_type> Parse(std::string str) {
				size_type N = str.size();
				std::vector<data_type> result;

				for (index_type i = 0; i < N; i += DIGIT_BASE_POWER) {
					result.push_back(stoi(str.substr(i, DIGIT_BASE_POWER)));
				}

				return result;
			}

		public :
			Natural(const string_type& value = "0") {
				*body = Parse(value);
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
		};

	}
}