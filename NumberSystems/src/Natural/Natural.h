#pragma once
#include "../../headers/Fwd.h"
#include "../../Exceptions.h"
#include "../Utils/Parse.h"

#include "NaturalBase.h"

#include <vector>

namespace MathLib {
	namespace NumberSystems {

		class Natural : public NaturalBase<Natural>{
		private:
			vector_type* body = new vector_type();

			void ClearLimbs() {
				body->clear();
			}

		public :

			Natural() {

			}

			~Natural() {

			}			
			
			Natural(const string_type& value) {
				ClearLimbs();
				*body = detail::Parse(value);
			}

			void operator=(const string_type& value){
				ClearLimbs();
				auto digits = detail::Parse(value);

				for (auto d : digits) {
					AddMostLimb(d);
				}
			}

			Natural(limb_type value) {
				ClearLimbs();

				while (value > LIMB_BASE) {
					AddMostLimb(value % LIMB_BASE);
					value = value / LIMB_BASE;
				}
				AddMostLimb(value);
			}

			void operator=(limb_type value) {
				ClearLimbs();

				while (value > LIMB_BASE) {
					AddMostLimb(value % LIMB_BASE);
					value = value / LIMB_BASE;
				}
				AddMostLimb(value);
			}

			Natural(const vector_type vec) {
				ClearLimbs();
				for (auto d : vec) {
					AddMostLimb(d);
				}
			}

			void operator= (const vector_type vec) {
				ClearLimbs();
				for (auto d : vec) {
					AddMostLimb(d);
				}
			}

			Natural(const Natural& expr) {
				ClearLimbs();

				for (auto d : *expr.body) {
					AddMostLimb(d);
				}
			}

			void operator=(const Natural& expr) {
				ClearLimbs();
				for (auto d : *expr.body) {
					AddMostLimb(d);
				}
			}

			template<typename E>
			Natural(const NaturalBase<E>& expr) {
				ClearLimbs();
				auto digits = expr.Digits();
				for (auto d : digits) {
					AddMostLimb(d);
				}
			}

			template<typename E>
			void operator=(const NaturalBase<E>& expr) {
				ClearLimbs();
				auto digits = expr.Digits();
				for (auto d : digits) {
					AddMostLimb(d);
				}
			}

			const vector_type Digits() const {
				return *this->body;
			}

			const Natural& AddMostLimb(limb_type digit) {
				this->body->push_back(digit);
				return *this;
			}

			const Natural& AddLeastLimb(limb_type digit) {
				this->body->insert(this->body->begin(), digit);
				return *this;
			}

			const Natural& RemoveLeadingZeroes() {
				size_type N = Size();
				index_type i = N - 1;
				for (i; i < N; --i) {
					if (this->body->at(i) != 0) {
						break;
					}
				}

				if (i + 1 > i)
					this->body->resize(i + 1);

				return *this;
			}

			const Natural& AddTrailingZeros(const size_type zeros) {
				for (index_type i = 0; i < zeros; ++i) {
					this->AddLeastLimb(0);
				}

				return *this;
			}

			limb_type operator[](index_type idx) const{
				return (*this->body)[idx];
			}

			limb_type& operator[](index_type idx) {
				return (*this->body)[idx];
			}

			template<typename E>
			const Natural& operator+=(const NaturalBase<E>& expr) {
				(*this) = (*this) + expr;

				return *this;
			}

			template<typename E>
			const Natural& operator-=(const NaturalBase<E>& expr) {
				(*this) = (*this) - expr;

				return *this;
			}

			const Natural& Evaluate() const{
				return *this;
			}

			void Log() const {
				for (auto d : *body) {
					std::cout << d << " ";
				}
				std::cout << "\n";
			}
		};

	}
}