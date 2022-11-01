#include <iostream>
#include <chrono>
#include "../LinearAlgebra//Core.h"

constexpr unsigned LOOPS = 10;
using namespace MathLib::LinearAlgebra;

int main()
{
	const unsigned int N = 1000;
	SquareMatrix<int, N> A;

	for (unsigned i = 0; i < N; ++i) {
		for (unsigned j = 0; j < N; ++j) {
			A.At(i, j) = i + j;
		}
	}

	auto average = 0.0;

	for (unsigned i = 0; i < LOOPS; ++i) {
		auto start = std::chrono::high_resolution_clock::now();
		auto M = (A * A).Evaluate();
		auto end = std::chrono::high_resolution_clock::now();

		average += (end - start).count();
	}
	std::cout << (average / 1e9) / LOOPS <<"s";

	return 0;
}