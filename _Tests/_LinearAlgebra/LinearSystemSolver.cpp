#include "pch.h"
#include "../../../MathLibrary/LinearAlgebra/impl/LU/LUCore.h"

using namespace MathLib;
using namespace MathLib::LinearAlgebra;

TEST(SOLESolver, Forward) {
	SquareMatrix<double, 3> A = {
		{2, 0, 0},
		{0, -1, 0},
		{4, 1, 5}
	};
	Vector<double, 3> y = { 1, 2, 3 };

	auto x = ForwardSolve(A, y);
	ASSERT_EQ(A * x, y);
}

TEST(SOLESolver, ForwardBig) {
	const unsigned N = 10;
	SquareMatrix<double, N> M;

	for (unsigned i = 0; i < N; ++i) {
		for (unsigned j = 0; j < i; ++j) {
			M.At(i, j) = i * j + 1;
		}
		M.At(i, i) = 1;
	}

	Vector<double, N> y;

	for (unsigned i = 0; i < N; ++i) {
		y[i] = i + 1;
	}

	auto x = ForwardSolve(M, y);
	ASSERT_EQ(M * x, y);
}

TEST(SOLESolver, Backward) {
	SquareMatrix<double, 3> A = {
		{2, 16, -3},
		{0, -1, 1},
		{0, 0, 7}
	};
	Vector<double, 3> y = { 1, 2, 3 };

	auto x = BackwardSolve(A, y);
	auto v = A * x;

	for (unsigned i = 0; i < 3; ++i) {
		if (abs(v[i] - y[i]) >= TOLERABLE_DOUBLE_THRESHOLD)
			EXPECT_TRUE(false);
	}
}

TEST(SOLESolver, BackwardBig) {
	const unsigned N = 10;
	SquareMatrix<double, N> M;

	for (unsigned i = 0; i < N; ++i) {
		for (unsigned j = i + 1; j < N; ++j) {
			M.At(i, j) = (N - i) * (N - j) + 1;
		}
		M.At(i, i) = 1;
	}

	Vector<double, N> y;

	for (unsigned i = 0; i < N; ++i) {
		y[i] = N - i;
	}

	auto x = BackwardSolve(M, y);
	auto v = M * x;

	for (unsigned i = 0; i < N; ++i) {
		if (abs(v[i] - y[i]) >= TOLERABLE_DOUBLE_THRESHOLD)
			EXPECT_TRUE(false);
	}
}

TEST(SolveSystem, Basic) {
	SquareMatrix<double, 3> A = {
		{2, 3, 1},
		{4, 1, 5},
		{0, -1, 4},
	};
	Vector<double, 3> y = { 1, 2, 3 };

	auto x = SolveLinearSystem(A, y);
	auto v = A * x;

	for (unsigned i = 0; i < 3; ++i) {
		if (abs(v[i] - y[i]) >= TOLERABLE_DOUBLE_THRESHOLD)
			EXPECT_TRUE(false);
	}
}

TEST(SolveSystem, Inverse) {
	SquareMatrix<double, 3> A = {
		{2, 3, 1},
		{4, 1, 5},
		{0, -1, 4},
	};

	auto AI = Inverse(A);
	auto I = IdentityMatrix<double, 3>();
	auto X = AI * A;

	for (unsigned i = 0; i < 3; ++i) {
		for (unsigned j = 0; j < 3; ++j) {
			if (abs(X.At(i, j) - I.At(i, j)) >= TOLERABLE_DOUBLE_THRESHOLD) {
				EXPECT_TRUE(false);
			}
		}
	}
}

