#include <iostream>
#include <chrono>
#include "../LinearAlgebra//Core.h"

using namespace MathLib::LinearAlgebra;

int main()
{
	const unsigned int N = 1000;
	SquareMatrix<int, N>* A = new SquareMatrix<int, N>();

	for (unsigned i = 0; i < N; ++i) {
		for (unsigned j = 0; j < N; ++j) {
			A->At(i, j) = i + j;
		}
	}

	auto start = std::chrono::high_resolution_clock::now();

	auto M = ((*A) * (*A)).Evaluate();

	auto end = std::chrono::high_resolution_clock::now();

	std::cout << (end - start).count() / 1e9<<"s";

	return 0;
}