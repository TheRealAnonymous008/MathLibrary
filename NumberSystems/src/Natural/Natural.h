#pragma once
#include "../../headers/Fwd.h"
#include "../../Exceptions.h"
#include "../Utils/Parse.h"

#include "NaturalBase.h"

#include <vector>

namespace MathLib {
	namespace NumberSystems {

		class Natural : public NaturalBase<Natural>, public Stringable{
		private:
			vector_type* body = new vector_type();

			void ClearLimbs() {
				body->clear();
			}

			void SetBody(const vector_type& digits) {
				this->body->resize(digits.size());
				std::copy(digits.begin(), digits.end(), this->body->begin());
			}


		public :

			Natural() {

			}

			~Natural() {
				delete body;
			}			
			
			Natural(const string_type& value) {
				vector_type digits = detail::ParseNatural(value);
				SetBody(digits);
			}

			void operator=(const string_type& value){
				vector_type digits = detail::ParseNatural(value);
				SetBody(digits);
			}

			Natural(limb_type value) {
				ClearLimbs();

				if (value == 0) {
					return;
				}

				while (value > LIMB_BASE) {
					AddMostLimb(value % LIMB_BASE);
					value = value / LIMB_BASE;
				}
				AddMostLimb(value);
			}

			void operator=(limb_type value) {
				ClearLimbs();

				if (value == 0) {
					return;
				}

				while (value > LIMB_BASE) {
					AddMostLimb(value % LIMB_BASE);
					value = value / LIMB_BASE;
				}
				AddMostLimb(value);
			}

			Natural(const vector_type& vec) {
				SetBody(vec);
			}

			void operator= (const vector_type& vec) {
				SetBody(vec);
			}

			Natural(const Natural& expr) {
				SetBody(*expr.body);
			}

			void operator=(const Natural& expr) {
				SetBody(*expr.body);
			}

			template<typename E>
			Natural(const NaturalBase<E>& expr) {
				vector_type digits = expr.Evaluate().Digits();
				SetBody(digits);
			}

			template<typename E>
			void operator=(const NaturalBase<E>& expr) {
				vector_type digits = expr.Evaluate().Digits();
				SetBody(digits);
			}

			const vector_type Digits() const {
				return *this->body;
			}

			const size_type Size() const {
				return this->body->size();
			}

			Natural& AddMostLimb(limb_type digit) {
				this->body->push_back(digit);
				return *this;
			}

			Natural& AddLeastLimb(limb_type digit) {
				this->body->insert(this->body->begin(), digit);
				return *this;
			}

			Natural& RemoveLeadingZeroes() {
				size_type N = Size();
				index_type i = N - 1;
				for (i; i < N; --i) {
					if (this->body->at(i) != 0) {
						break;
					}
				}

				if (i + 1 > i)
					this->body->resize(i + 1);
				else {
					ClearLimbs();
				}

				return *this;
			}

			Natural& AddTrailingZeros(const size_type zeros) {
				this->body->insert(this->body->begin(), zeros, 0);

				return *this;
			}

			Natural& RemoveLeastLimbs(const size_type limbs) {
				if (limbs > this->Size()) {
					ClearLimbs();
				}
				else {
					this->body->erase(this->body->begin(), this->body->begin() + limbs);
				}

				return *this;
			}

			Natural Slice(const index_type left, const index_type right) const {
				Natural slice = vector_type(body->begin() + left, body->begin() + right);
				return slice;
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

			template<typename E>
			const Natural& operator*=(const NaturalBase<E>& expr) {
				(*this) = (*this) * expr;

				return *this;
			}

			template<typename E>
			const Natural& operator/=(const NaturalBase<E>& expr) {
				(*this) = (*this) / expr;

				return *this;
			}

			template<typename E>
			const Natural& operator%=(const NaturalBase<E>& expr) {
				(*this) = (*this) % expr;

				return *this;
			}

			template<typename E>
			const Natural& operator&=(const NaturalBase<E>& expr) {
				(*this) = (*this) & expr;

				return *this;
			}

			template<typename E>
			const Natural& operator|=(const NaturalBase<E>& expr) {
				(*this) = (*this) | expr;

				return *this;
			}

			template<typename E>
			const Natural& operator^=(const NaturalBase<E>& expr) {
				(*this) = (*this) ^ expr;

				return *this;
			}

			template<typename E>
			const Natural& operator<<=(const NaturalBase<E>& expr) {
				(*this) = (*this) << expr;

				return *this;
			}


			template<typename E>
			const Natural& operator>>=(const NaturalBase<E>& expr) {
				(*this) = (*this) >> expr;

				return *this;
			}

			Natural operator--(int) {
				size_type size = this->Size();

				if (size == 0) {
					throw InvalidSubtractionOperation();
				}

				for (index_type i = 0; i < size; ++i) {
					if ((*body)[i] == 0) {
						(*body)[i] = MAX_LIMB_VALUE;
					}
					else {
						--(*body)[i];
						break;
					}
				}

				this->RemoveLeadingZeroes();
				return *this;
			}

			Natural operator++(int) {;
				size_type size = this->Size();

				if (size == 0) {
					AddMostLimb(1);
					return *this;
				}

				for (index_type i = 0; i < size; ++i) {
					if ((*body)[i] == MAX_LIMB_VALUE) {
						(*body)[i] = 0;
					}
					else {
						++(*body)[i];
						break;
					}
				}
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

			string_type Str() const {
				return detail::ReverseParse(Digits());
			}
		};
		
		namespace constants {
			static const Natural ZERO = Natural();
			static const Natural ONE = Natural("1");
		}
	}
}