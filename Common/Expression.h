#pragma once

namespace MathLib {
	template<typename Expr>
	class Expression {
	private:

	public:
		template<typename Result>
		Result Evaluate() {
			return static<Expr const&>(*this).Evaluate();
		}
	};
}