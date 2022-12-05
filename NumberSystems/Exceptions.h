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

		class InvalidSubtractionOperation : public std::exception {
		public:
			std::string what() {
				return "Trying to perform a subtaction operation will yield a result not in the number system.";
			}
		};
	}
}