#pragma once

#include "../../../LinearAlgebra/Core.h"

#include <algorithm>  
#include <limits>
#include <random>

namespace Benchmarking {

	namespace Generator {

		std::random_device dev;
		std::mt19937_64 rng(dev());

		template<const unsigned N>
		MathLib::LinearAlgebra::Vector<double, N> Vector() {
			std::uniform_real_distribution<double> dist(std::numeric_limits<double>::min(), std::numeric_limits<double>::max());

			MathLib::LinearAlgebra::Vector<double, N> vector;

			for (unsigned i = 0; i < N; ++i) {
				vector[i] = dist(rng);
			}

			return vector;
		}

		template<const unsigned Rows, const unsigned Columns>
		MathLib::LinearAlgebra::Matrix<double, Rows, Columns> Matrix() {
			std::uniform_real_distribution<double> dist(std::numeric_limits<double>::min(), std::numeric_limits<double>::max());

			MathLib::LinearAlgebra::Matrix<double, Rows, Columns> matrix;

			for (unsigned i = 0; i < Rows; ++i) {
				for (unsigned j = 0; j < Columns; ++j) {
					matrix.At(i, j) = dist(rng);
				}
			}

			return matrix;
		}

		inline double Scalar() {
			std::uniform_real_distribution<double> dist(std::numeric_limits<double>::min(), std::numeric_limits<double>::max());
			return dist(rng);
		}

		template<const unsigned N>
		std::vector<unsigned long long> Permutation() {
			std::vector<unsigned long long> arr = std::vector<unsigned long long>(N);
			
			for (auto i = 0; i < N; ++i) {
				arr[i] = i;
			}

			std::shuffle(arr.begin(), arr.end(), rng);
			return arr;
		}
	}
}