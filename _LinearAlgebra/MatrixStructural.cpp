#include "pch.h"

using namespace MathLib;
using namespace MathLib::LinearAlgebra;
TEST(MtatrixTranspose, Transpose) {
	Matrix<int, 4, 3> A = {
		{2, -3, 1},
		{1, -2, -3},
		{0, 0, 4},
		{1, 3, -1}
	};

	auto AT = Transpose(A);
	
	for (unsigned i = 0; i < 4; ++i) {
		for (unsigned j = 0; j < 3; ++j) {
			ASSERT_EQ(A.At(i, j), AT.At(j, i));
		}
	}

}

TEST(MtatrixTranspose, TransposeWithOps) {
	Matrix<int, 4, 3> A = {
		{2, -3, 1},
		{4, -2, -3},
		{3, 0, 4},
		{1, 3, 1}
	};

	Matrix<int, 4, 3> B = {
		{5, 4, -2},
		{1, 2, 0},
		{0, -1, 1},
		{6, 3, -1}
	};

	ASSERT_EQ(Transpose(3 * A) + Transpose(2 * B), Transpose(3 * A + 2 * B));

}

TEST(MatrixSlicing, MatrixSlicing) {
	Matrix<int, 10, 10> A;

	for (unsigned i = 0; i < 10; ++i) {
		for (unsigned j = 0; j < 10; ++j) {
			A.At(i, j) = 10 * i + j;
		}
	}

	unsigned r = 2;
	unsigned c = 3;
	Matrix<int, 5, 5> B = Slice<5, 5>(A, r, c);

	for (unsigned i = 0; i < B.Rows(); ++i) {
		for (unsigned j = 0; j < B.Columns(); ++j) {
			ASSERT_EQ(B.At(i, j) , (i + r) * 10 + (j + c));
		}
	}
}

TEST(MatrixBlocking, PadNoOffset) {
	Matrix<int, 10, 10> A;

	for (unsigned i = 0; i < 10; ++i) {
		for (unsigned j = 0; j < 10; ++j) {
			A.At(i, j) = 10 * i + j;
		}
	}

	Matrix<int, 20, 20> padded = PlaceBlock<20, 20>(A);

	ASSERT_EQ(padded.At(1, 15), 0);
	ASSERT_EQ(padded.At(19, 19), 0);
	ASSERT_EQ(padded.At(4, 5), 45);
	ASSERT_EQ(padded.At(1, 7), 17);
}


TEST(MatrixBlocking, PadWithOffset) {
	Matrix<int, 10, 10> A;

	for (unsigned i = 0; i < 10; ++i) {
		for (unsigned j = 0; j < 10; ++j) {
			A.At(i, j) = 10 * i + j;
		}
	}

	Matrix<int, 20, 20> padded = PlaceBlock<20, 20>(A, 3, 2);

	ASSERT_EQ(padded.At(1, 15), 0);
	ASSERT_EQ(padded.At(19, 19), 0);
	ASSERT_EQ(padded.At(2, 1), 0);
	ASSERT_EQ(padded.At(7, 4), 42);
	ASSERT_EQ(padded.At(4, 9), 17);
}

TEST(MatrixBlocking, BlockInsertion) {
	Matrix<int, 10, 10> A;
	for (unsigned i = 0; i < 10; ++i) {
		for (unsigned j = 0; j < 10; ++j) {
			A.At(i, j) = 1;
		}
	}

	Matrix<int, 20, 20> B;
	PlaceBlock(B, A);

	for (unsigned i = 0; i < 20; ++i) {
		for (unsigned j = 0; j < 20; ++j) {
			if (i < 10 && j < 10) {
				ASSERT_EQ(B.At(i, j), 1);
			}
			else {
				ASSERT_EQ(B.At(i, j), 0);
			}
		}
	}
}

TEST(SquareMat, UpperMat) {
	SquareMatrix<double, 4> A = {
		{1.2, 2.3,	3.4,	4.5},
		{0,   1.2,	-2.1,	4.7},
		{0,   0,	-6.1,	9.2},
		{0,   0,	0,		3.2},
	};

	SquareMatrix<double, 4> B = {
		{0.7, -3.2,	0.2,	0},
		{0,   1.4,	-1.1,	3.7},
		{0,   0,	0,		0.9},
		{0,   0,	0,		-1.2},
	};

	ASSERT_TRUE(IsUpper(A));
	ASSERT_TRUE(IsUpper(B));
	ASSERT_TRUE(IsUpper(3.0 * A + 2.0 * B));

	ASSERT_TRUE(IsLower(Transpose(A)));
	ASSERT_TRUE(IsLower(Transpose(B)));
}

TEST(SquareMat, LowerMat) {
	SquareMatrix<double, 4> A = {
		{1.2,	0,		0,		0},
		{-1.2,  0.2,	0,		0},
		{3.4,   4.7,	4.1,	0},
		{-0.2,  3.5,	0,		-1.4},
	};

	SquareMatrix<double, 4> B = {
		{5.5,	0,		0,		0},
		{-1.2,	-6.3,	0,		0},
		{-1.4,	4.4,	9.2,	0},
		{1.2,	0,		2.7,	1.2},
	};

	ASSERT_TRUE(IsLower(A));
	ASSERT_TRUE(IsLower(B));
	ASSERT_TRUE(IsLower(3.0 * A + 2.0 * B));

	ASSERT_TRUE(IsUpper(Transpose(A)));
	ASSERT_TRUE(IsUpper(Transpose(B)));
}

TEST(SquareMat, DiagonalMat) {
	SquareMatrix<int, 6> A;
	SquareMatrix<int, 6> B;

	for (unsigned i = 0; i < 6; ++i) {
		A.At(i, i) = i * 2 + 1;
		B.At(i, i) = i * i - 1;
	}

	ASSERT_TRUE(IsDiagonal(A));
	ASSERT_TRUE(IsDiagonal(B));
	ASSERT_TRUE(IsDiagonal(2 * A + 3 * B));

	ASSERT_TRUE(IsUpper(A));
	ASSERT_TRUE(IsLower(A));
	ASSERT_TRUE(IsSymmetric(A));
}

TEST(SqureMat, SymmetricMat){
	SquareMatrix<int, 6> A;

	for (unsigned i = 0; i < 6; ++i) {
		for (unsigned j = 0; j < 6; ++j) {
			A.At(i, j) = 2 * i - i * j + j * j;
		}
	}

	ASSERT_TRUE(IsSymmetric(A * Transpose(A)));
	ASSERT_TRUE(IsSymmetric(Transpose(A) * A));
}

TEST(SquareMat, EmptyMat) {
	SquareMatrix<int, 143> A;

	ASSERT_TRUE(IsUpper(A));
	ASSERT_TRUE(IsLower(A));
	ASSERT_TRUE(IsDiagonal(A));
	ASSERT_TRUE(IsSymmetric(A));
}

TEST(SquareMat, IdentityMat) {
	auto I = IdentityMatrix<int, 10>();

	for (unsigned i = 0; i < 10; ++i) {
		for (unsigned j = 0; j < 10; ++j) {
			if (i != j) {
				ASSERT_EQ(I.At(i, j), 0);
			} else {
				ASSERT_EQ(I.At(i, j), 1);
			}
		}
	}
}

TEST(Permutation, Permutation) {
	auto P = PermutationMatrix<int, 6>();
	ASSERT_EQ(P.At(3, 3), 1);

	P.Permute(1, 2);

	ASSERT_EQ(P.At(1, 1), 0);
	ASSERT_EQ(P.At(2, 2), 0);
	ASSERT_EQ(P.At(1, 2), 1);
	ASSERT_EQ(P.At(2, 1), 1);
}