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

	ASSERT_TRUE(IsUpper(A));
	//ASSERT_TRUE(IsUpper(A + A));
}