#pragma once

#include "Natural.h"

namespace MathLib {
	namespace NumberSystems {

		namespace detail {

			template<typename Expr>
			class NaturalNot : public NaturalBase<NaturalNot<Expr>> {
			private:
				const Expr& expr;

				Natural result;
				void Calculate() {

					size_type size = expr.Size();
					result.AddTrailingZeros(size);
					OPENMP_PARALLELIZE
					for (index_type i = 0; i < size; ++i) {
						result[i] = (~expr[i]) & ((1 << (LIMB_BASE_POWER)) - 1);
					}
				}


			public:
				NaturalNot(const Expr& expr) : expr(expr) {
					Calculate();
				}

				const vector_type Digits() const {
					return result.Digits();
				}

				auto Evaluate() const {
					return result;
				}

			};
		}

		template<typename Expr>
		detail::NaturalNot<Expr> operator~(const NaturalBase<Expr>& expr) {
			return detail::NaturalNot(*static_cast<const Expr*>(&expr));
		}

	}
}