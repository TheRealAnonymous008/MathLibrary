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

				std::shared_ptr<Array<T, Ns...>> result;

			public:
				ArrayAddition(const Array<T, Ns...>& lhs, const Array<T, Ns...>& rhs) : lhs(lhs), rhs(rhs){
					result = std::make_shared<Array<T, Ns...>>();

#pragma loop(hint_parallel(PARALLEL_THREADS))
					for (unsigned i = 0; i < result->Size(); ++i) {
						(*result)[i] = lhs[i] + rhs[i];
					}
				}

				const Array<T, Ns...>& Get() {
					return std::move(*result);
				}
			};


			template<typename T, const unsigned ...Ns>
			class ArraySubtraction : public Lazy<Array<T, Ns...>> {
			private:
				const Array<T, Ns...>& lhs;
				const Array<T, Ns...>& rhs;

				std::shared_ptr<Array<T, Ns...>> result;

			public:
				ArraySubtraction(const Array<T, Ns...>& lhs, const Array<T, Ns...>& rhs) : lhs(lhs), rhs(rhs) {
					result = std::make_shared<Array<T, Ns...>>();

#pragma loop(hint_parallel(PARALLEL_THREADS))
					for (unsigned i = 0; i < result->Size(); ++i) {
						(*result)[i] = lhs[i] - rhs[i];
					}
				}

				const Array<T, Ns...>& Get() {
					return std::move(*result);
				}
			};

			template<typename T, const unsigned ...Ns>
			class ArrayMultiplication : public Lazy<Array<T, Ns...>> {
			private:
				const Array<T, Ns...>& lhs;
				const Array<T, Ns...>& rhs;

				std::shared_ptr<Array<T, Ns...>> result;

			public:
				ArrayMultiplication(const Array<T, Ns...>& lhs, const Array<T, Ns...>& rhs) : lhs(lhs), rhs(rhs) {
					result = std::make_shared<Array<T, Ns...>>();

#pragma loop(hint_parallel(PARALLEL_THREADS))
					for (unsigned i = 0; i < result->Size(); ++i) {
						(*result)[i] = lhs[i] * rhs[i];
					}
				}

				const Array<T, Ns...>& Get() {
					return std::move(*result);
				}
			};

			template<typename T, const unsigned ...Ns>
			class ArrayDivision : public Lazy<Array<T, Ns...>> {
			private:
				const Array<T, Ns...>& lhs;
				const Array<T, Ns...>& rhs;

				std::shared_ptr<Array<T, Ns...>> result;

			public:
				ArrayDivision(const Array<T, Ns...>& lhs, const Array<T, Ns...>& rhs) : lhs(lhs), rhs(rhs) {
					result = std::make_shared<Array<T, Ns...>>();

#pragma loop(hint_parallel(PARALLEL_THREADS))
					for (unsigned i = 0; i < result->Size(); ++i) {

						if (rhs[i] == 0) {
							throw Exceptions::DivideByZero();
						}

						(*result)[i] = lhs[i] / rhs[i];
					}
				}

				const Array<T, Ns...>& Get() {
					return std::move(*result);
				}
			};

			template<typename T, const unsigned ...Ns>
			class ArrayScalarProduct : public Lazy<Array<T, Ns...>> {
			private:
				const Array<T, Ns...>& lhs;
				const T& rhs;

				std::shared_ptr<Array<T, Ns...>> result;

			public:
				ArrayScalarProduct(const Array<T, Ns...>& lhs, const T& rhs) : lhs(lhs), rhs(rhs) {
					result = std::make_shared<Array<T, Ns...>>();

#pragma loop(hint_parallel(PARALLEL_THREADS))
					for (unsigned i = 0; i < result->Size(); ++i) {
						(*result)[i] = lhs[i] * rhs;
					}
				}

				const Array<T, Ns...>& Get() {
					return std::move(*result);
				}
			};

			template<typename T, const unsigned ...Ns>
			class ArrayScalarQuotient : public Lazy<Array<T, Ns...>> {
			private:
				const Array<T, Ns...>& lhs;
				const T& rhs;

				std::shared_ptr<Array<T, Ns...>> result;

			public:
				ArrayScalarQuotient(const Array<T, Ns...>& lhs, const T& rhs) : lhs(lhs), rhs(rhs) {
					if (rhs == 0) {
						throw Exceptions::DivideByZero();
					}

					result = std::make_shared<Array<T, Ns...>>();

#pragma loop(hint_parallel(PARALLEL_THREADS))
					for (unsigned i = 0; i < result->Size(); ++i) {
						(*result)[i] = lhs[i] / rhs;
					}
				}

				const Array<T, Ns...>& Get() {
					return std::move(*result);
				}
			};

		}
	}
}