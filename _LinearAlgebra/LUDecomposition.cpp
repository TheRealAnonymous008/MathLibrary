#include "pch.h"
#include "../../MathLibrary/LinearAlgebra/impl/LU/LUCore.h"

using namespace MathLib;
using namespace MathLib::LinearAlgebra;


TEST(LUDecomposition, Nongenerated) {
	
	Matrix<double, 3, 3> M = {
		{3, 8, 1},
		{5, 2, 0},
		{6, 1, 12},
	};

	auto lu = PartialLU(M);

	ASSERT_TRUE(IsLower(lu.L));
	ASSERT_TRUE(IsUpper(lu.U));
	ASSERT_EQ(lu.P * M, lu.L * lu.U);

}


TEST(LUDecomposition, Simple) {
	const unsigned N = 100;
	SquareMatrix<double, N> M;

	for (unsigned i = 0; i < N; ++i) {
		for (unsigned j = 0; j < N; ++j) {
			M.At(i, j) = N * N - 2 * i * j;
		}
	}

	auto lu = PartialLU(M);

	ASSERT_TRUE(IsLower(lu.L));
	ASSERT_TRUE(IsUpper(lu.U));
	ASSERT_EQ(lu.P * M, lu.L * lu.U);

}