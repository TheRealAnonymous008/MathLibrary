#pragma once

#include "../../../LinearAlgebra/Core.h"

#include <random>

namespace Benchmarking {

	namespace Generator {

		std::random_device dev;
		std::mt19937_64 rng(dev());

		template<const unsigned N>
		MathLib::LinearAlgebra::Vector<double, N> Vector() {
			std::uniform_real_distribution<double> dist;

			MathLib::LinearAlgebra::Vector<double, N> vector;

			for (unsigned i = 0; i < N; ++i) {
				vector[i] = dist(rng);
			}

			return vector;
		}

		inline double Scalar() {
			std::uniform_real_distribution<double> dist;
			return dist(rng);
		}
	}
}