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
	//Matrix<int, 5, 5> B = Slice(A, r, c);

	//for (unsigned i = 0; i < B.Rows(); ++i) {
	//	for (unsigned j = 0; j < B.Columns(); ++j) {
	//		ASSERT_EQ(B.At(i, j) , (i + r) * 10 + (j + c));
	//	}
	//}
}