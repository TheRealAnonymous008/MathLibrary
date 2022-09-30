#pragma once

#include <stdexcept>

namespace MathLib {
	namespace Exceptions {

		class InvalidTensorAccess : public std::exception {
		public:
			std::string what() {
				return "Invalid Access for Tensor";
			}
		};

		class DivideByZero : public std::exception {
		public:
			std::string what() {
				return "Tried to Divide by 0";
			}
		};

		class InvalidTensorReshape : public std::exception {
		public:
			std::string what() {
				return "Cannot Reshape this array.";
			}
		};

		class InvalidTensorSlice : public std::exception {
		public:
			std::string what() {
				return "Slice parameters are in bad form.";
			}
		};
	}
}