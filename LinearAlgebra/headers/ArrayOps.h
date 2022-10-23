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

				Array<T, Ns...>* Evaluate() {
					Array<T, Ns...>* result = new Array<T, Ns...>();

#pragma loop(hint_parallel(PARALLEL_THREADS))
					for (unsigned i = 0; i < result->Size(); ++i) {

						result->At({ i }) = lhs.At({ i }) + rhs.At({ i });
					}

					return result;
				}

			public:
				ArrayAddition(const Array<T, Ns...>& lhs, const Array<T, Ns...>& rhs) : lhs(lhs), rhs(rhs){
					Evaluate();
				}

				Array<T, Ns...> Get() {
					return *Evaluate();
				}
			};

		}
	}
}