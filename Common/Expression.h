#pragma once

namespace MathLib {
	template<typename Result, typename Expr>
	class Expression {
	private:

	public:
		Result Evaluate() {
			return static_cast<Expr const&>(*this).Evaluate();
		}
	};
}