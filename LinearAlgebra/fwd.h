#pragma once

#include <iostream>

namespace MathLib {
	namespace LinearAlgebra {

		template<typename T, const unsigned N>
		class Vector;

		template<typename T, const unsigned Rows, const unsigned Columns>
		class Matrix;

		template<typename T, typename E>
		class VectorExpression;

		template<typename T, typename E>
		class MatrixExpression;
	}
}