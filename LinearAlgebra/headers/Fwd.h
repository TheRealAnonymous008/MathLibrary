#pragma once

#include <iostream>
#include "../Core.h"

namespace MathLib {
	namespace LinearAlgebra {

		using size_type = const unsigned;
		using index_type = int;

		template<typename T, size_type N>
		class Vector;

		template<typename T, size_type Rows, size_type Columns>
		class Matrix;

		template<typename T, size_type N, typename E>
		class VectorBase;

		template<typename T, size_type Rows, size_type Columns, typename E>
		class MatrixBase;
	}
}