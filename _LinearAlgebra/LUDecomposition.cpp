#include "pch.h"
#include "../../MathLibrary//LinearAlgebra//LU.h"

using namespace MathLib;
using namespace MathLib::LinearAlgebra;

TEST(LUDecomposition, Simple) {
	SquareMatrix<double, 10> M;

	for (unsigned i = 0; i < 10; ++i) {
		for (unsigned j = 0; j < 10; ++j) {
			M.At(i, j) = i * sqrt(j) + j * sqrt(i + 1) + 1;
		}
	}

	auto lu  =LUDecomposition(M);

	ASSERT_TRUE(IsLower(lu.L));
	ASSERT_TRUE(IsUpper(lu.U));
	ASSERT_EQ(M, lu.L * lu.U);
}