#pragma once

#include "../Core/Core.h"

namespace MathLib {
	namespace LinearAlgebra {

		template<typename T, const unsigned N>
		class Array;

		template<typename T, const unsigned N, const unsigned ...Ns>
		class MultiArray;

		template<typename T, const unsigned N>
		class Vector;

		template<typename T, const unsigned Rows, const unsigned Columns>
		class Matrix;

	}
}