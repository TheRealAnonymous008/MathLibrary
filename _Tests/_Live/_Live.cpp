#include <iostream>
#include <chrono>
#include "Statistics.h"

#include "../../LinearAlgebra/Core.h"
#include "../../LinearAlgebra/headers/LU.h"

#define LOOPS 10
using namespace MathLib::LinearAlgebra;

int main()
{
	const unsigned int N = 1000;
	const unsigned int K = 1000;
	const unsigned int M = 1000;

	Matrix<float, N, K>* A = new Matrix<float, N, K>();
	Matrix<float, K, M>* B = new Matrix<float, K, M>();
	Vector<float, N>* v = new Vector<float, N>();

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

	for (unsigned i = 0; i < v->Size(); ++i) {
		(*v)[i] = i + 1;
	}

	std::vector<double> samples;

	for (unsigned i = 0; i < LOOPS; ++i) {
		auto start = std::chrono::high_resolution_clock::now();
		*A* *B;
		auto end = std::chrono::high_resolution_clock::now();

		auto time = (end - start).count() / 1e9;
		samples.push_back(time);
	}
 
	GenerateReport(samples);

	_CrtDumpMemoryLeaks();
	return 0;
}