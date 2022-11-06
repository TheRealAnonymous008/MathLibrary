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

	const unsigned int N = 1000;
	SquareMatrix<int, N> *A = new SquareMatrix<int, N>();

	for (unsigned i = 0; i < N; ++i) {
		for (unsigned j = 0; j < N; ++j) {
			A->At(i, j) = i + j;
		}
	}

	auto M = ((*A) * (*A)).Evaluate();
	
	unsigned row = 275;
	unsigned column = 842;

	int sum = 0;
	for (unsigned k = 0; k < N; k++) {
		sum += A->At(row, k) * A->At(k, column);
	}

	ASSERT_EQ(M.At(row, column), sum);
}

TEST(Identity, SquareMatMul) {
	const unsigned N = 10;

	auto I = IdentityMatrix<int, N>();
	auto A = SquareMatrix<int, N>();

	for (unsigned i = 0; i < N; ++i) {
		for (unsigned j = 0; j < N; ++j) {
			A.At(i, j) = 2 * i - i * j + j * j;
		}
	}

	ASSERT_EQ(A * I, A);
	ASSERT_EQ(I * A, A);
	ASSERT_EQ(I * I, I);
	ASSERT_EQ(I * I * A, I * A * I);
}

TEST(Identity, NonSquareMatmul) {
	Matrix<int, 4, 3> A = {
		{2, -3, 1},
		{1, -2, -3},
		{0, 0, 4},
		{1, 3, -1}
	};

	auto Ir = IdentityMatrix<int, 4>();
	auto Ic = IdentityMatrix<int, 3>();

	ASSERT_EQ(Ir * A, A);
	ASSERT_EQ(A * Ic, A);
}

TEST(Permutation, RowPermutation) {
	const unsigned N = 4;

	auto P = PermutationMatrix<int, N>();
	auto A = SquareMatrix<int, N>();

	for (unsigned i = 0; i < N; ++i) {
		for (unsigned j = 0; j < N; ++j) {
			A.At(i, j) = i;
		}
	}
	

	P.Permute(0, 2);
	P.Permute(1, 3);
	P.Permute(2, 1);

	A = P * A;

	ASSERT_EQ(A.At(0, 0), 2);
	ASSERT_EQ(A.At(1, 0), 0);
	ASSERT_EQ(A.At(2, 0), 3);
	ASSERT_EQ(A.At(3, 0), 1);
}

TEST(Permutation, ColumnPermutation) {
	const unsigned N = 4;

	auto P = PermutationMatrix<int, N>();
	auto A = SquareMatrix<int, N>();

	for (unsigned i = 0; i < N; ++i) {
		for (unsigned j = 0; j < N; ++j) {
			A.At(i, j) = j;
		}
	}

	P.Permute(0, 1);
	P.Permute(1, 3);
	P.Permute(2, 0);

	A= A * P;

	ASSERT_EQ(A.At(0, 0), 2);
	ASSERT_EQ(A.At(0, 1), 3);
	ASSERT_EQ(A.At(0, 2), 1);
	ASSERT_EQ(A.At(0, 3), 0);
}

TEST(Permutation, IdentityPermutation) {
	const unsigned N = 4;

	auto P = PermutationMatrix<int, N>();
	auto I = IdentityMatrix<int, N>();

	ASSERT_EQ(P, I);
	P.Permute(0, 1);
	P.Permute(1, 3);
	P.Permute(2, 0);

	ASSERT_EQ(I * P, P);
	ASSERT_EQ(P * I, P);
}

TEST(Permutation, PermutationComposition) {
	const unsigned N = 4;

	auto P = PermutationMatrix<int, N>();
	auto Q = PermutationMatrix<int, N>();
	
	P.Permute(1, 3);
	P.Permute(2, 3);

	Q.Permute(3, 1);
	Q.Permute(0, 1);

	ASSERT_EQ((P.Evaluate() * Q.Evaluate()).Evaluate(), (P * Q).Evaluate().Evaluate());
}