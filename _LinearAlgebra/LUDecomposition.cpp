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

TEST(LUDecomposition, WideRectangle) {

	Matrix<double, 2, 3> M = {
		{-2, 1, 3},
		{-4, 4, 1}
	};

	auto lu = PartialLU(M);
	ASSERT_TRUE(IsLower(lu.L));

	auto X = lu.P * M;
	auto Y = lu.L * lu.U;

	for (unsigned i = 0; i < 2; ++i) {
		for (unsigned j = 0; j < 3; ++j) {
			ASSERT_DOUBLE_EQ(X.At(i, j), Y.At(i, j));
		}
	}

}

TEST(LUDecomposition, TallThinRectangle) {

	Matrix<double, 3, 2> M = {
		{1, 0},
		{-4, 4},
		{-2, 1},
	};

	auto lu = PartialLU(M);
	ASSERT_TRUE(IsLower(lu.L));

	auto X = lu.P * M;
	auto Y = lu.L * lu.U;

	for (unsigned i = 0; i < 3; ++i) {
		for (unsigned j = 0; j < 2; ++j) {
			ASSERT_DOUBLE_EQ(X.At(i, j), Y.At(i, j));
		}
	}

}

TEST(LUDecomposition, TallWideRectangle) {

	Matrix<double, 3, 4> M = {
		{1, 0, 2, -1},
		{-4, 4, 1, 0},
		{-2, 1, 2, 0},
	};

	auto lu = PartialLU(M);
	ASSERT_TRUE(IsLower(lu.L));

	auto X = lu.P * M;
	auto Y = lu.L * lu.U;

	for (unsigned i = 0; i < 3; ++i) {
		for (unsigned j = 0; j < 4; ++j) {
			ASSERT_DOUBLE_EQ(X.At(i, j), Y.At(i, j));
		}
	}

}

TEST(LUDecomposition, Simple) {
	const unsigned N = 10;
	SquareMatrix<double, N> M;
	for (unsigned i = 0; i < N; ++i) {
		for (unsigned j = 0; j <= i; ++j) {
			M.At(i, j) = i + j + 1;
		}
	}

	auto lu = PartialLU(M);

	auto X = lu.P * M; 
	auto Y = lu.L * lu.U;
	
	for (unsigned i = 0; i < N; ++i) {
		for (unsigned j = 0; j < N; ++j) {
			ASSERT_DOUBLE_EQ(X.At(i, j), Y.At(i, j));
		}
	}
}


TEST(LUDecomposition, Generated) {
	const unsigned N = 100;
	SquareMatrix<double, N> M;
	for (unsigned i = 0; i < N; ++i) {
		for (unsigned j = 0; j <= N; ++j) {
			M.At(i, j) = rand() % 2 * 1e10;
		}
	}

	auto lu = PartialLU(M);

	auto X = lu.P * M;
	auto Y = lu.L * lu.U;

	for (unsigned i = 0; i < N; ++i) {
		for (unsigned j = 0; j < N; ++j) {
			if (abs(X.At(i, j) - Y.At(i, j)) >= TOLERABLE_DOUBLE_THRESHOLD)
				EXPECT_TRUE(false);
		}
	}
}

TEST(PLUQDecomposition, Nongenerated) {

	Matrix<double, 3, 3> M = {
		{8, 3, 1},
		{2, 5, 0},
		{1, 6, 12},
	};

	auto lu = FullLU(M);

	ASSERT_TRUE(IsLower(lu.L));
	ASSERT_TRUE(IsUpper(lu.U));
	ASSERT_EQ(lu.P * M * lu.Q, lu.L * lu.U);

}