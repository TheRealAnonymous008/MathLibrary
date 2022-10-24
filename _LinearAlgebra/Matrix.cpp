#include "pch.h"

using namespace MathLib::LinearAlgebra;

TEST(MatrixInit, MatContructor) {
	Matrix<int, 4, 4> M = {
		{1, 2, 3, 4}, 
		{5, 6, 7, 8}, 
		{9, 10, 11, 12}, 
		{13, 14, 15, 16} 
	};
	
	ASSERT_EQ(M.At(0, 1), 2);
}
