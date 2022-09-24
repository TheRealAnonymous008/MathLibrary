#pragma once

#include <type_traits>

namespace MathLib {
	template <typename Condition, typename T = void>
	using EnableIf = typename std::enable_if<Condition::value, T>::type;
}