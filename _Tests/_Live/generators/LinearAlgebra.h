#pragma once

#include "../../../LinearAlgebra/Core.h"

#include <random>

namespace Benchmarking {

	namespace Generator {

		std::random_device dev;
		std::mt19937_64 rng(dev());

		template<const unsigned N>
		MathLib::LinearAlgebra::Vector<double, N> Vector() {
			std::uniform_real_distribution<std::mt19937::result_type> dist;

			MathLib::LinearAlgebra::Vector<double, N> vector;

			for (unsigned i = 0; i < N; ++i) {
				vector[i] = dis(rng);
			}

			return vector;
		}
	}
}