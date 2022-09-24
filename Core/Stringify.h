#pragma once

#include <string>

#include "Template.h"

namespace MathLib {

	class Stringable {
	public:
		virtual std::string ToString() = 0;
	};

	template<
		typename T ,
		typename = EnableIf<std::is_arithmetic<T>>
	>
	std::string Stringify(T& val) {
		return std::to_string(val);
	}

	inline std::string Stringify(std::string& val) {
		return val;
	}

	inline std::string Stringify(Stringable& val) {
		return val.ToString();
	}
}