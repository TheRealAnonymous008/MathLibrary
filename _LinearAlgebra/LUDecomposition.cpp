#include "pch.h"
#include "../../MathLibrary//LinearAlgebra//LU.h"

using namespace MathLib;
using namespace MathLib::LinearAlgebra;

TEST(LUDecomposition, Simple) {
	SquareMatrix<double, 5> M;

	for (unsigned i = 0; i < 5; ++i) {
		for (unsigned j = 0; j < 5; ++j) {
			M.At(i, j) = i * sqrt(j) + j * sqrt(i + 1) + 1;
		}
	}

	auto lu  =LUDecomposition(M);
}