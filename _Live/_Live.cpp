#include <iostream>
#include <chrono>
#include "../LinearAlgebra//Core.h"

#define LOOPS 1
using namespace MathLib::LinearAlgebra;

int main()
{
	const unsigned int N = 2000;
	const unsigned int K = 2000;
	const unsigned int M = 2000;

	Matrix<float, N, K>* A = new Matrix<float, N, K>();
	Matrix<float, K, M>* B = new Matrix<float, K, M>();

	for (unsigned i = 0; i < A->Rows(); ++i) {
		for (unsigned j = 0; j < A->Columns(); ++j) {
			A->At(i, j) = i + j + 0.0f;
		}
	}

	for (unsigned i = 0; i < B->Rows(); ++i) {
		for (unsigned j = 0; j < B->Columns(); ++j) {
			B->At(i, j) = i * j - 1.0f;
		}
	}

	double count = 0;

	for (unsigned i = 0; i < LOOPS; ++i) {
		auto start = std::chrono::high_resolution_clock::now();
		auto M = ((*A) * (*B)).Evaluate();
		auto end = std::chrono::high_resolution_clock::now();

		count += (end - start).count() / 1e9;
	}

	std::cout << count / LOOPS <<"s";

	_CrtDumpMemoryLeaks();
	return 0;
}