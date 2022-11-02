#include <iostream>
#include <chrono>
#include "../LinearAlgebra//Core.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>


#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif

#define LOOPS 1
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