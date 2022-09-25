#pragma once

#include "../Core/Core.h"

namespace MathLib {
	namespace LinearAlgebra {

		template<const unsigned ...Ns>
		class ArrayShape;

		template<typename T, const unsigned N>
		class ArrayBase;

		template<typename T, const unsigned ...Ns>
		class Array;

		template<typename T, const unsigned N>
		class Vector;

		template<typename T, const unsigned Rows, const unsigned Columns>
		class Matrix;

	}
}