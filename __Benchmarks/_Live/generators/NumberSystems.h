#pragma once

#include "../../../NumberSystems/Core.h"

#include <random>

namespace Benchmarking {
	
	namespace Generator {

		std::random_device dev;
		std::mt19937_64 rng(dev());

		template<const unsigned N>
		std::string NumericString() {
			std::string result = "";
			std::uniform_int_distribution<std::mt19937::result_type> dist(0, 9);

			for (unsigned i = 0; i < N; ++i) {
				auto digit = dist(rng);
				result += std::to_string(digit);
			}

			return result;
		}

		template<const unsigned N>
		MathLib::NumberSystems::Natural NaturalNumber() {
			return MathLib::NumberSystems::Natural(NumericString<N>());
		}

		template<const unsigned N>
		MathLib::NumberSystems::Integer Integer() {
			std::uniform_int_distribution<std::mt19937::result_type> dist(0, 1);
			auto x = dist(rng);
			MathLib::NumberSystems::IntegerSign sign; 
			if (x == 0) {
				sign = MathLib::NumberSystems::IntegerSign::POSITIVE;
			}
			else {
				sign = MathLib::NumberSystems::IntegerSign::NEGATIVE;
			}

			return MathLib::NumberSystems::Integer(sign, NaturalNumber<N>());

		}
	}
}