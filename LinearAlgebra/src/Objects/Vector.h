#pragma once

#include "../../headers/Fwd.h"
#include "../../Exceptions.h"

#include <initializer_list>
#include <vector>

namespace MathLib {
	namespace LinearAlgebra {
		
		template<typename T, size_type N>
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
				index_type i = 0;
				for (T obj : list) {
					(*body)[i] = obj;
					++i;
				}
			}

			void operator=(const std::initializer_list<T>& list) {
				index_type i = 0;
				for (T obj : list) {
					(*body)[i] = obj;
					++i;
				}
			}
			
			Vector(const Vector& expr) {
				if (expr.Size() != Size()) {
					throw DimensionError();;
				}

				OPENMP_PARALLELIZE
				for (index_type i = 0; i < Size(); ++i) {
					(*body)[i] = expr[i];
				}
			}

			void operator=(const Vector& expr) {
				if (expr.Size() != Size()) {
					throw DimensionError();;
				}

				OPENMP_PARALLELIZE
				for (index_type i = 0; i < Size(); ++i) {
					(*body)[i] = expr[i];
				}
			}

			template<typename E>
			Vector(const VectorBase<T, N, E>& expr) {
				if (expr.Size() != Size()) {
					throw DimensionError();;
				}

				auto eval = expr.Evaluate();
				OPENMP_PARALLELIZE
				for (index_type i = 0; i < Size(); ++i) {
					(*body)[i] = eval[i];
				}
			}

			template<typename E>
			void operator=(const VectorBase<T, N, E>& expr) {
				if (expr.Size() != Size()) {
					throw DimensionError();;
				}

				auto eval = expr.Evaluate();
				for (index_type i = 0; i < Size(); ++i) {
					(*body)[i] = eval[i];
				}
			}

			constexpr size_type Size() const {
				return N;
			}

			T& operator[](index_type i) {
				return (*body)[i];
			}

			T operator[](index_type i) const{
				return (*body)[i];
			}

			template<typename E>
			Vector& operator+=(const VectorBase<T, N, E>& expr) {

				auto eval = expr.Evaluate();

				OPENMP_PARALLELIZE
				for (index_type i = 0; i < Size(); ++i) {
					(*body)[i] += eval[i];
				}
				return *this;
			}

			template<typename E>
			Vector& operator-=(const VectorBase<T, N, E>& expr) {

				auto eval = expr.Evaluate();

				OPENMP_PARALLELIZE
				for (index_type i = 0; i < Size(); ++i) {
					(*body)[i] -= eval[i];
				}
				return *this;
			}

			Vector& operator*=(const T& c) {

				OPENMP_PARALLELIZE
				for (index_type i = 0; i < Size(); ++i) {
					(*body)[i] *= c;
				}
				return *this;
			}

			Vector& operator/=(const T& c) {
				if (c == 0)
					throw DivisionByZero();

				OPENMP_PARALLELIZE
				for (index_type i = 0; i < Size(); ++i) {
					(*body)[i] /= c;
				}
				return *this;
			}

			const Vector& Evaluate() const{
				return *this;
			}

			void Log() const {
				for (index_type i = 0; i < N; ++i) {
					std::cout << (*this)[i] << " ";
				}
				std::cout << "\n";
			}
		};
	}
}

