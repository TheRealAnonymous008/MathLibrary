#pragma once

namespace MathLib {
	template<typename Operation, typename ...Args>
	class Expression {
	private:
		Args...args;

	public:
		Expression(Args... args) {
			this->args = args;
		}


	};
}