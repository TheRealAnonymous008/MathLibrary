#include "pch.h"


using namespace MathLib;
using namespace MathLib::LinearAlgebra;

TEST(MatVec, MatVecEager) {
	Matrix<int, 4, 3> A = {
		{2, -3, 1},
		{1, -2, -3},
		{0, 0, 4},
		{1, 3, -1}
	};

	Vector<int, 3> x = {
		-1, 5, 2
	};

	Vector<int, 4> z = {
		-15, -17, 8, 12
	};

	Vector<int, 4> y = (A * x).Evaluate();

	ASSERT_EQ(y, z);
}

TEST(MatVec, MatrixVectorProduct) {
	Matrix<int, 4, 3> A = {
		{2, -3, 1},
		{1, -2, -3},
		{0, 0, 4},
		{1, 3, -1}
	};

	Vector<int, 3> x = {
		-1, 5, 2
	};

	Vector<int, 4> z = {
		-15, -17, 8, 12
	};

	Vector<int, 4> y = A * x;

	ASSERT_EQ(y, z);

}

TEST(MatMat, MatrixMatrixProduct) {
	Matrix<int, 4, 3> A = {
		{2, -3, 1},
		{1, -2, -3},
		{0, 0, 4},
		{1, 3, -1}
	};

	Matrix<int, 3, 2> B = {
		{2, 4},
		{-1, 0},
		{3, 1}
	};

	Matrix<int, 4, 2> C = {
		{10, 9},
		{-5, 1},
		{12, 4},
		{-4, 3}
	};

	ASSERT_EQ((A * B).Evaluate(), C);
	ASSERT_EQ((A * B), C);
	ASSERT_EQ(2 * A * B, 2 * C);
	ASSERT_EQ(A * 3 * B, 3 * C);
}

TEST(MatMat, Strassen) {
	Matrix<int, 4, 3> A = {
	{2, -3, 1},
	{1, -2, -3},
	{0, 0, 4},
	{1, 3, -1}
	};

	Matrix<int, 3, 2> B = {
		{2, 4},
		{-1, 0},
		{3, 1}
	};

	Matrix<int, 4, 2> C = {
		{10, 9},
		{-5, 1},
		{12, 4},
		{-4, 3}
	};
	
	auto M = implementation::StrassenMatrixMultiplication(A, B);

	ASSERT_EQ(M, C);
}

TEST(MatMat, BigProduct) {

	const unsigned int N = 515;
	SquareMatrix<int, N> *A = new SquareMatrix<int, N>();

	for (unsigned i = 0; i < N; ++i) {
		for (unsigned j = 0; j < N; ++j) {
			A->At(i, j) = i + j;
		}
	}

	auto M = ((*A) * (*A)).Evaluate();
	
}