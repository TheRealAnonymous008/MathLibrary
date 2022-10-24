#include "pch.h"

using namespace MathLib::LinearAlgebra;

TEST(VectorInit, WithConstructor) {
	Vector<float, 10> v1 = Vector<float, 10>({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});

	ASSERT_TRUE(v1.Size() == 10);
	ASSERT_TRUE(v1[2] == 3);
	ASSERT_TRUE(v1[7] == 8);
	ASSERT_THROW(v1[10], InvalidAccess);
}

TEST(VectorInit, WithAssignment) {
	Vector<float, 10> v1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	ASSERT_TRUE(v1.Size() == 10);
	ASSERT_TRUE(v1[2] == 3);
	ASSERT_TRUE(v1[7] == 8);
	ASSERT_THROW(v1[10], InvalidAccess);
}

TEST(VectorInit, WithExpression) {
	Vector<int, 10> v1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	Vector<int, 10> v2 = v1;

	ASSERT_TRUE(v1[1] == v2[1]);
	ASSERT_TRUE(v1[4] == v2[4]);
	ASSERT_TRUE(v1[9] == v2[9]);
}

TEST(VectorOperations, Addition) {
	Vector<int, 10> v1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	Vector<int, 10> v2 = { 9, 8, 7, 5, 4, 3, 6, 6, 6, 1 };

	Vector<int, 10> v = v1 + v2;

	for (size_t i = 0; i < 10; ++i) {
		ASSERT_TRUE(v[i] == v1[i] + v2[i]);
	}
}

TEST(VectorOperations, MultiAdd) {
	Vector<int, 10> v1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	Vector<int, 10> v2 = { 9, 8, 7, 5, 4, 3, 6, 6, 6, 1 };
	Vector<int, 10> v3 = { -1, 8, 6, 5, 3, 0, -5, -6, -1, 1 };

	Vector<int, 10> v = v1 + v2 + v3;

	for (size_t i = 0; i < 10; ++i) {
		ASSERT_TRUE(v[i] == v1[i] + v2[i] + v3[i]);
	}

	ASSERT_TRUE((v1 + v2) == (v2 + v1));

}


TEST(VectorOperations, MatrixSubtraction) {
	Vector<int, 10> v1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	Vector<int, 10> v2 = { 9, 8, 7, 5, 4, 3, 6, 6, 6, 1 };

	Vector<int, 10> v = v1 - v2;

	for (size_t i = 0; i < 10; ++i) {
		ASSERT_TRUE(v[i] == v1[i] - v2[i]);
	}
}

TEST(VectorOperations, MatrixNegation) {
	Vector<int, 10> v1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	Vector<int, 10> v = -v1;

	for (size_t i = 0; i < 10; ++i) {
		ASSERT_TRUE(v[i] == -v1[i]);
	}
}

TEST(VectorOperations, BigOps) {
	const unsigned N = 1000 * 1000;

	Vector<int, N> v = *(new Vector<int, N>());
	Vector<int, N> w = *(new Vector<int, N>());

	for (unsigned i = 0; i < v.Size(); ++i) {
		v[i] = 2 * i + 1;
		w[i] = i * i;
	}

	Vector<int, N> x = v + w;

	for (unsigned i = 0; i < N; ++i) {
		ASSERT_TRUE(x[i] == (i + 1) * (i + 1));
	}
}