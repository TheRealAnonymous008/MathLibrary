#pragma once 

#include "Extern.h"

#include <iostream>
#include <math.h>
#include <vector>

namespace MathLib {
	namespace NumberSystems {

		const unsigned LIMB_BASE_POWER = 30;
		const unsigned LIMB_BASE_RADIX = 2;
		const unsigned long long LIMB_BASE = static_cast<const unsigned long long>(pow(LIMB_BASE_RADIX, LIMB_BASE_POWER));
		const unsigned long long MAX_LIMB_VALUE = LIMB_BASE - 1;

		using string_type = std::string;
		using index_type = unsigned long long;
		using size_type = size_t;
		using signed_size_type = long long;
		using signed_index_type = long long;
		using limb_type = unsigned long long;
		using vector_type = std::vector<limb_type>;

		template<typename Derived>
		class NumberBase;

		class Natural;

		template<typename Derived>
		class IntegerBase;

		class Integer;

		template<typename Derived>
		class RealBase;

		class Real;

		namespace detail {
			template<typename F, typename LHS, typename RHS> class Addition {};
			template<typename F, typename LHS, typename RHS> class Subtraction {};
			template<typename F, typename LHS, typename RHS> class Multiplication {};
			template<typename F, typename LHS, typename RHS> class Division {};
			template<typename F, typename LHS, typename RHS> class Modulo {};

			template<typename F, typename Expr> class Negation {};
			template<typename F, typename Expr> class Not {};

			template<typename F, typename LHS, typename RHS> class And {};
			template<typename F, typename LHS, typename RHS> class Or {};
			template<typename F, typename LHS, typename RHS> class Xor {};
			template<typename F, typename LHS, typename RHS> class LeftShift {};
			template<typename F, typename LHS, typename RHS> class RightShift {};

			template<typename F, typename Expr> class Sin {};
			template<typename F, typename Expr> class Cos {};
			template<typename F, typename Expr> class Tan {};
			template<typename F, typename Expr> class Csc {};
			template<typename F, typename Expr> class Sec {};
			template<typename F, typename Expr> class Cot {};

			template<typename F, typename Expr> class Sqrt {};
			template<typename F, typename Expr> class Square {};
			template<typename F, typename Expr> class Factorial {};

			template<typename F, typename Base, typename Power> class Pow {};
		}
	}
}