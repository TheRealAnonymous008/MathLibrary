#include "pch.h"

using namespace MathLib::LinearAlgebra;

TEST(MatrixInit, BasicInitilizer01) {
	Matrix<int, 2, 3> matrix;
	ASSERT_TRUE(matrix.rows == 2);
	ASSERT_TRUE(matrix.columns == 3);
}

TEST(MatrixInit, BasicInitializer02) {
	Matrix<int, 100, 100>* matrix = new Matrix<int, 100, 100>();

	for (unsigned int i = 0; i < 100; ++i) {
		for (unsigned int j = 0; j < 100; ++j) {
			auto k = matrix->At({ i, j });
			ASSERT_TRUE(k == 0);
		}
	}
}

TEST(MatrixInit, SquareMatrixInitializer) {
	SquareMatrix<int, 20> matrix;
	ASSERT_TRUE(matrix.rows == matrix.columns);
}

TEST(MatrixInit, InitWithInitializerList) {
	Matrix<int, 3, 4> A = {
		1, 2, 3, 0,
		4, 5, 6, -1,
		7, 8, 9, -2
	};

	ASSERT_TRUE(A.At({ 2, 1 }) == 8);
	ASSERT_TRUE(A.At({ 1, 3 }) == -1);
	ASSERT_TRUE(A.At({ 0, 2}) == 3);
}

TEST(MatrixEquality, Equality) {
	Matrix<int, 3, 4> A;
	Matrix<int, 3, 4> B;
	
	for (unsigned int i = 0; i < 3; ++i) {
		for (unsigned int j = 0; j < 4; ++j) {
			A.At({ i, j }) = i * j;
			B.At({ i, j }) = i * j;
		}
	}

	ASSERT_TRUE(A == B);
	ASSERT_FALSE(A != B);
}

TEST(MatrixInequality, Inequality) {
	Matrix<int, 3, 4> A;
	Matrix<int, 3, 4> B;

	for (unsigned int i = 0; i < 3; ++i) {
		for (unsigned int j = 0; j < 4; ++j) {
			A.At({ i, j }) = i * j;
			B.At({ i, j }) = i * j;
		}
	}

	A.At({ 1,1 }) = -1;

	ASSERT_TRUE(A != B);
	ASSERT_FALSE(A == B);
}

TEST(MatrixTranspose, Transpose1) {
	Matrix<int, 3, 4> A = {
		1, 2, 3, 0	,
		4, 5, 6, -1,
		7, 8, 9, -2
	};

	Matrix<int, 4, 3> B = {
		1, 4, 7,
		2, 5, 8,
		3, 6, 9,
		0, -1, -2
	};

	ASSERT_TRUE(A.Size() == B.Size() && A.Size() == 12);

	ASSERT_TRUE(A.Transpose() == B);
	ASSERT_TRUE(A.Transpose().Transpose() == A);
	ASSERT_TRUE(B.Transpose() == A);
	ASSERT_TRUE(B.Transpose().Transpose() == B);
}

TEST(MatrixOps, Addition) {
	Matrix<int, 3, 4> A = {
		1, 2, 3, 0,
		4, 5, 6, -1,
		7, 8, 9, -2
	};

	Matrix<int, 3, 4> B = {
		-1, 1, 7, 0,
		3, 4, 8, 0,
		2, 0, -10, -4
	};

	Matrix<int, 3, 4> C = {
		0, 3, 10, 0,
		7, 9, 14, -1,
		9, 8, -1, -6
	};

	ASSERT_TRUE(A + B == B + A);
	ASSERT_TRUE(C == B + A);
	ASSERT_TRUE(C - A == B);
}

TEST(MatrixOps, ScalarMultiplication) {
	Matrix<int, 3, 4> A = {
		1, 2, 3, 0,
		4, 5, 6, -1,
		7, 8, 9, -2
	};
	Matrix<int, 3, 4> B = {
		2, 4, 6, 0,
		8, 10, 12, -2,
		14, 16, 18, -4
	};
	
	ASSERT_TRUE(2 * A == A * 2);
	ASSERT_TRUE(2 * A == B);
	ASSERT_TRUE(B / 2 == A);
}

TEST(MatVecMultiplication, Test1) {
	Matrix<int, 3, 4> A = {
		1, 2, 3, 0,
		4, 5, 6, -1,
		7, 8, 9, -2
	};

	Vector<int, 4> x = {
		0, 0, 0, 1
	};

	Vector<int, 3> y{
		0, -1, -2
	};

	ASSERT_TRUE(A * x == y);
}

TEST(MatMatMultiplication, Test1) {
	Matrix<int, 4, 4> A = {
	1, 2, 3, 0,
	4, 5, 6, -1,
	7, 8, 9, -2,
	-3, -4, 0, 0
	};

	auto B = A.Transpose();
	A* B;
}

TEST(MatMatMultiplication, Test2) {
	Matrix<int, 2, 2> A = {
		1, 2,
		4, 5
	};

	auto B = A.Transpose();
	A* B;
}