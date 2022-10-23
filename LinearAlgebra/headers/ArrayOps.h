#pragma once
#include "../fwd.h"

namespace MathLib {
	namespace LinearAlgebra {

		namespace detail {

			template<typename T, const unsigned ...Ns>
			class ArrayAddition : public Lazy<Array<T, Ns...>>{
			private:
				const Array<T, Ns...>& lhs;
				const Array<T, Ns...>& rhs;

				Array<T, Ns...>* result;

			public:
				ArrayAddition(const Array<T, Ns...>& lhs, const Array<T, Ns...>& rhs) : lhs(lhs), rhs(rhs){
					result = new Array<T, Ns...>();

#pragma loop(hint_parallel(PARALLEL_THREADS))
					for (unsigned i = 0; i < result->Size(); ++i) {
						(*result)[i] = lhs[i] + rhs[i];
					}
				}

				const Array<T, Ns...>& Get() {
					return std::move(*result);
				}
			};

		}
	}
}