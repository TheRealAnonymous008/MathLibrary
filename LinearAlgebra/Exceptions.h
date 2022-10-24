#pragma once

#include <exception>
#include <string>

namespace MathLib {
	namespace LinearAlgebra {

		class InvalidAccess : public std::exception {
		public:
			std::string what() {
				return "ITried to access with an out of bounds index.";
			}
		};

		class InvalidBinaryOperation : public std::exception {
		public:
			std::string what() {
				return "Tried to perform a binary operation on tensors of different sizes.";
			}
		};
	}
}