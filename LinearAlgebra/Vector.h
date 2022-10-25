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
				unsigned i = 0;
				for (T obj : list) {
					body[i] = obj;
					++i;
				}
			}

			void operator=(const std::initializer_list<T>& list) {
				unsigned i = 0;
				for (T obj : list) {
					body[i] = obj;
					++i;
				}
			}

			template<typename E>
			Vector(const VectorExpression<T, E>& expr) {
				if (expr.Size() != Size()) {
					throw DimensionError();;
				}

				for (unsigned i = 0; i < Size(); ++i) {
					body[i] = expr[i];
				}
			}

			template<typename E>
			void operator=(const VectorExpression<T, E>& expr) {
				if (expr.Size() != Size()) {
					throw DimensionError();;
				}

				for (unsigned i = 0; i < Size(); ++i) {
					body[i] = expr[i];
				}
			}

			constexpr unsigned Size() const {
				return N;
			}

			T& operator[](unsigned i) {
				if (i >= Size() || i < 0)
					throw InvalidAccess();
				return body[i];
			}

			T operator[](unsigned i) const{
				if (i >= Size() || i < 0)
					throw InvalidAccess();

				return body[i];
			}

			template<typename E>
			Vector& operator+=(const VectorExpression<T, E>& expr) {
				for (unsigned i = 0; i < Size(); ++i) {
					body[i] += expr[i];
				}
				return *this;
			}

			template<typename E>
			Vector& operator-=(const VectorExpression<T, E>& expr) {
				for (unsigned i = 0; i < Size(); ++i) {
					body[i] -= expr[i];
				}
				return *this;
			}

			Vector& operator*=(const T& c) {
				for (unsigned i = 0; i < Size(); ++i) {
					body[i] *= c;
				}
				return *this;
			}

			Vector& operator/=(const T& c) {
				if (c == 0)
					throw DivisionByZero();

				for (unsigned i = 0; i < Size(); ++i) {
					body[i] /= c;
				}
				return *this;
			}

			const Vector& Evaluate() {
				return *this;
			}
		};
	}
}

