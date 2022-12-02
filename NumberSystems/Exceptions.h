#pragma once 

#include <exception>
#include <string>

namespace MathLib{
	namespace NumberSystems {
		
		class InvalidNumericString : public std::exception {
		public:
			std::string what() {
				return "Argument for constructor for number type is invalid. String should only contain digits.";
			}
		};

	}
}