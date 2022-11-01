#pragma once

#include <iostream>
#include "../Common/Core.h"

namespace MathLib {
	namespace LinearAlgebra {

		template<typename T, const unsigned N>
		class Vector;

		template<typename T, const unsigned Rows, const unsigned Columns>
		class Matrix;

		template<typename T, const unsigned N, typename E>
		class VectorBase;

		template<typename T, const unsigned Rows, const unsigned Columns, typename E>
		class MatrixBase;
	}
}