#pragma once
#include <initializer_list>
#include <array>
#include <vector>
#include "fwd.h"

namespace MathLib {
	namespace LinearAlgebra {
		
		template<typename T, const unsigned N>
		class Vector : public VectorExpression<T, Vector<T, N>>
		{
		private:
			std::vector<T> body = std::vector<T>(N);

		public:
			Vector() {
				
			}
			
			~Vector() {

			}

			Vector(const std::initializer_list<T>& list) {
				size_t i = 0;
				for (T obj : list) {
					body[i] = obj;
					++i;
				}
			}

			void operator=(const std::initializer_list<T>& list) {
				size_t i = 0;
				for (T obj : list) {
					body[i] = obj;
					++i;
				}
			}

			template<typename E>
			Vector(const VectorExpression<T, E>& expr) {
				for (size_t i = 0; i < Size(); ++i) {
					body[i] = expr[i];
				}
			}

			template<typename E>
			void operator=(const VectorExpression<T, E>& expr) {
				for (size_t i = 0; i < Size(); ++i) {
					body[i] = expr[i];
				}
			}

			constexpr size_t Size() const{
				return N;
			}

			T& operator[](size_t i) {
				if (i >= Size() || i < 0)
					throw InvalidAccess();
				return body[i];
			}

			T operator[](size_t i) const{
				if (i >= Size() || i < 0)
					throw InvalidAccess();

				return body[i];
			}
		};
	}
}

