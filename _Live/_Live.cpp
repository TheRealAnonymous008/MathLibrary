#include <iostream>
#include <chrono>
#include "../LinearAlgebra//Core.h"

#define LOOPS 1
using namespace MathLib::LinearAlgebra;

int main()
{
	const unsigned int N = 2000;
	SquareMatrix<int, N>* A = new SquareMatrix<int, N>();

	for (unsigned i = 0; i < N; ++i) {
		for (unsigned j = 0; j < N; ++j) {
			A->At(i, j) = i + j;
		}
	}

	double count = 0;

	for (unsigned i = 0; i < LOOPS; ++i) {
		auto start = std::chrono::high_resolution_clock::now();
		auto M = ((*A) * (*A)).Evaluate();
		auto end = std::chrono::high_resolution_clock::now();

		count += (end - start).count() / 1e9;
	}

	std::cout << count / LOOPS <<"s";

	_CrtDumpMemoryLeaks();
	return 0;
}