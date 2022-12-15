#pragma once
#include <string>

namespace MathLib {
	
	class Stringable {
	public:
		virtual std::string Str() const = 0;
	};

	std::ostream& operator<<(std::ostream& os, Stringable& obj) {
		return os << obj.Str();
	}
}