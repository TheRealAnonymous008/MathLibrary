#include "pch.h"
#include "../../MathLibrary/LinearAlgebra/impl/LU/LUCore.h"

using namespace MathLib;
using namespace MathLib::LinearAlgebra;

TEST(LUDecomposition, Simple) {
	const unsigned N = 10;
	SquareMatrix<double, N> M;

	for (unsigned i = 0; i < N; ++i) {
		for (unsigned j = 0; j < N; ++j) {
			M.At(i, j) = (i) * sqrt(j) + (j) * sqrt(i + 1) + 1;
		}
	}

	auto lu  =	PartialLU(M);

	ASSERT_TRUE(IsLower(lu.L));
	ASSERT_TRUE(IsUpper(lu.U));
	ASSERT_EQ(M, lu.L * lu.U);
}