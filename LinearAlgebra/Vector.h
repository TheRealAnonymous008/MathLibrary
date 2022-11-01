#pragma once
#include <initializer_list>
#include <array>
#include <vector>

#include "fwd.h"
#include "Exceptions.h"

namespace MathLib {
	namespace LinearAlgebra {
		
		template<typename T, const unsigned N>
		class Vector : public VectorBase<T, N, Vector<T, N>>
		{
		private:
			std::vector<T>* body = (new std::vector<T>(N));

		public:
			Vector() {
				
			}
			
			~Vector() {

			}

			Vector(const std::initializer_list<T>& list) {
				unsigned i = 0;
				for (T obj : list) {
					(*body)[i] = obj;
					++i;
				}
			}

			void operator=(const std::initializer_list<T>& list) {
				unsigned i = 0;
				for (T obj : list) {
					(*body)[i] = obj;
					++i;
				}
			}
			
			Vector(const Vector& expr) {
				if (expr.Size() != Size()) {
					throw DimensionError();;
				}

				for (unsigned i = 0; i < Size(); ++i) {
					(*body)[i] = expr[i];
				}
			}

			void operator=(const Vector& expr) {
				if (expr.Size() != Size()) {
					throw DimensionError();;
				}

				for (unsigned i = 0; i < Size(); ++i) {
					(*body)[i] = expr[i];
				}
			}

			template<typename E>
			Vector(const VectorBase<T, N, E>& expr) {
				if (expr.Size() != Size()) {
					throw DimensionError();;
				}

				for (unsigned i = 0; i < Size(); ++i) {
					(*body)[i] = expr[i];
				}
			}

			template<typename E>
			void operator=(const VectorBase<T, N, E>& expr) {
				if (expr.Size() != Size()) {
					throw DimensionError();;
				}

				for (unsigned i = 0; i < Size(); ++i) {
					(*body)[i] = expr[i];
				}
			}

			constexpr unsigned Size() const {
				return N;
			}

			T& operator[](unsigned i) {
				if (i >= Size() || i < 0)
					throw InvalidAccess();
				return (*body)[i];
			}

			T operator[](unsigned i) const{
				if (i >= Size() || i < 0)
					throw InvalidAccess();

				return (*body)[i];
			}

			template<typename E>
			Vector& operator+=(const VectorBase<T, N, E>& expr) {

				for (unsigned i = 0; i < Size(); ++i) {
					(*body)[i] += expr[i];
				}
				return *this;
			}

			template<typename E>
			Vector& operator-=(const VectorBase<T, N, E>& expr) {
				
				for (unsigned i = 0; i < Size(); ++i) {
					(*body)[i] -= expr[i];
				}
				return *this;
			}

			Vector& operator*=(const T& c) {
				for (unsigned i = 0; i < Size(); ++i) {
					(*body)[i] *= c;
				}
				return *this;
			}

			Vector& operator/=(const T& c) {
				if (c == 0)
					throw DivisionByZero();

				for (unsigned i = 0; i < Size(); ++i) {
					(*body)[i] /= c;
				}
				return *this;
			}

			const Vector& Evaluate() const{
				return *this;
			}
		};
	}
}

