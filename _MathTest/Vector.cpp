#include "pch.h"


using namespace MathLib::LinearAlgebra;

TEST(VectorOps, ScalarMultiplication1) {
	const unsigned int N = 100;
	Vector<float, N> v;

	for (int i = 0; i < N; ++i) {
		v[i] = (float) i;
	}

	const auto& w = v * 2;
	for (int i = 0; i < N; ++i) {
		ASSERT_FLOAT_EQ(w[i], v[i] * 2);
	}

	ASSERT_TRUE(v + v == v * 2);
	v *= 2;
	ASSERT_TRUE(w == v);
	ASSERT_TRUE(3 * v == v * 3);
}

TEST(VectorOps, ScalarMultiplication2) {
	const unsigned int N = 100;
	float c = 23;
	Vector<float, N> v;

	for (int i = 0; i < N; ++i) {
		v[i] = (float)i;
	}

	auto w = v;
	v *= c;

	for (int i = 0; i < N; ++i) {
		ASSERT_FLOAT_EQ(w[i] * c, v[i]);
	}
}

TEST(VectorOps, ScalarMultPlusArithmetic) {
	const unsigned int N = 100;
	int c = 2;
	Vector<int, N> v;
	Vector<int, N> w;
	for (int i = 0; i < N; ++i) {
		v[i] = i;
	}
	
	ASSERT_TRUE(v * c - v == v);
}

TEST(VectorOps, ScalarDivisionPass) {
	const unsigned int N = 100;
	float c = -10.25;
	Vector<float, N> v;

	for (int i = 0; i < N; ++i) {
		v[i] = (float)i;
	}

	auto w = v;
	v /= c;

	for (int i = 0; i < N; ++i) {
		ASSERT_FLOAT_EQ(w[i] / c, v[i]);
	}
}

TEST(VectorOps, ScalarDivisionFail) {
	const unsigned int N = 100;
	float c = 0;
	Vector<float, N> v;

	for (int i = 0; i < N; ++i) {
		v[i] = (float)i;
	}

	ASSERT_THROW(v / c, MathLib::Exceptions::DivideByZero);
	ASSERT_THROW(v /= c, MathLib::Exceptions::DivideByZero);
}

TEST(VectorOps, DotProduct) {
	Vector<float, 4> v = { 1.0f, -0.5f, 3.4f, 2.7f };
	Vector<float, 4> w = { 2.0f, 6.2f, 0.0f, -10.0f };
	
	ASSERT_FLOAT_EQ(v.Dot(w),  w.Dot(v));
	ASSERT_FLOAT_EQ(v.Dot(w),  2.0f - 3.1f + 0 - 27.0f);
}

TEST(VectorOps, Norm1) {
	Vector<float, 3> v;
	v[0] = 3;
	v[1] = 4;
	v[2] = -1;

	ASSERT_FLOAT_EQ(v.SquareNorm(), 26.0f);
	ASSERT_FLOAT_EQ(v.Norm(), std::sqrt(26.0f));
}