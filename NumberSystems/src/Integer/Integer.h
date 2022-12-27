#pragma once
#include "../../headers/Fwd.h"
#include "../../Exceptions.h"

#include "../Natural/Natural.h"

#include "IntegerBase.h"
#include "Parse.h"
#include "Signs.h"

namespace MathLib {
	namespace NumberSystems {
		class Integer : public IntegerBase<Integer>, public Stringable {
		private:
			IntegerSign sign = POSITIVE;
			Natural* body = new Natural();

			void ClearLimbs() {
				sign = POSITIVE;
				*body = 0;
			}

			void SetBody(const IntegerSign& sign, const Natural& body) {
				*(this->body) = body;
				this->sign = sign;
			}

			void SetBody(const Integer& expr) {
				*(this->body) = *(expr.body);
				this->sign = expr.sign;
			}

		public:
			Integer() {

			}

			~Integer() {
				delete body;
			}

						
			Integer(const string_type& value) {
				auto parsed = detail::ParseInteger(value);
				SetBody(parsed.sign, Natural(parsed.body));
			}

			void operator=(const string_type& value){
				auto parsed = detail::ParseInteger(value);
				SetBody(parsed.sign, Natural(parsed.body));
			}

			template<std::integral T>
			Integer(T value) {
				ClearLimbs();

				if (value == 0) {
					return;
				}

				auto s = (value < 0) ? NEGATIVE : POSITIVE;

				limb_type abs_val = abs(value);
				vector_type limbs;

				while (abs_val > LIMB_BASE) {
					limbs.push_back(abs_val % LIMB_BASE);
					abs_val = abs_val / LIMB_BASE;
				}
				limbs.push_back(abs_val);
				SetBody(s, Natural(limbs));
			}
			
			template<std::integral T>
			void operator=(T value) {
				ClearLimbs();

				if (value == 0) {
					return;
				}

				auto s = (value < 0) ? NEGATIVE : POSITIVE;

				limb_type abs_val = abs(value);
				vector_type limbs;

				while (abs_val > LIMB_BASE) {
					limbs.push_back(abs_val % LIMB_BASE);
					abs_val = abs_val / LIMB_BASE;
				}

				limbs.push_back(abs_val);
				SetBody(s, Natural(limbs));
			}

			Integer(const IntegerSign& sign, const vector_type& vec) {
				SetBody(sign, Natural(vec));
			}

			void operator= (const vector_type& vec) {
				SetBody(POSITIVE, Natural(vec));
			}

			template<typename Expr>
			Integer(const IntegerSign& sign, const NaturalBase<Expr>& expr) {
				SetBody(sign, expr.Evaluate());
			}

			template<typename Expr>
			Integer(const NaturalBase<Expr>& expr) {
				SetBody(POSITIVE, expr.Evaluate());
			}

			template<typename Expr>
			void operator=(const NaturalBase<Expr>& expr) {
				SetBody(POSITIVE, expr.Evaluate());
			}

			Integer(const Integer& expr) {
				SetBody(expr);
			}

			void operator=(const Integer& expr) {
				SetBody(expr);
			}

			template<typename E>
			Integer(const IntegerBase<E>& expr) {
				auto eval = expr.Evaluate();
				SetBody(eval);
			}

			template<typename E>
			void operator=(const IntegerBase<E>& expr) {
				auto eval = expr.Evaluate();
				SetBody(eval);
			}

			const vector_type Digits() const {
				return this->body->Digits();
			}

			const IntegerSign Sign() const {
				return this->sign;
			}

			Natural Magnitude() const {
				return *(this->body);
			}

			const size_type Size() const {
				return this->body->Size();
			}

			const signed_size_type SignedSize() const {
				return (this->sign == POSITIVE) ? this->body->Size() : -1 * this->body->Size();
			}

			Integer& AddMostLimb(limb_type digit) {
				this->body->AddMostLimb(digit);
				return *this;
			}

			Integer& AddLeastLimb(limb_type digit) {
				this->body->AddLeastLimb(digit);
				return *this;
			}

			Integer& RemoveLeadingZeroes() {
				this->body->RemoveLeadingZeroes();

				if (this->Size() == 0) {
					ClearLimbs();
				}

				return *this;
			}

			Integer& AddTrailingZeroes(const size_type zeroes) {
				this->AddTrailingZeroes(zeroes);
				return *this;
			}

			Integer& RemoveLeastLimbs(const size_type limbs) {
				this->body->RemoveLeastLimbs(limbs);

				if (this->Size() == 0) {
					ClearLimbs();
				}

				return *this;
			}

			Natural Slice(const index_type left, const index_type right) const {
				return this->body->Slice(left, right);
			}

			limb_type operator[](index_type idx) const {
				return (*this->body)[idx];
			}

			limb_type operator[](index_type idx) {
				return (*this->body)[idx];
			}

			template<typename E>
			const Integer& operator+=(const IntegerBase<E>& expr) {
				(*this) = (*this) + expr;

				return *this;
			}

			template<typename E>
			const Integer& operator-=(const IntegerBase<E>& expr) {
				(*this) = (*this) - expr;

				return *this;
			}

			template<typename E>
			const Integer& operator*=(const IntegerBase<E>& expr) {
				(*this) = (*this) * expr;

				return *this;
			}

			template<typename E>
			const Integer& operator/=(const IntegerBase<E>& expr) {
				(*this) = (*this) / expr;

				return *this;
			}

			template<typename E>
			const Integer& operator%=(const IntegerBase<E>& expr) {
				(*this) = (*this) % expr;

				return *this;
			}

			template<typename E>
			const Integer& operator&=(const IntegerBase<E>& expr) {
				(*this) = (*this) & expr;

				return *this;
			}

			template<typename E>
			const Integer& operator|=(const IntegerBase<E>& expr) {
				(*this) = (*this) | expr;

				return *this;
			}

			template<typename E>
			const Integer& operator^=(const IntegerBase<E>& expr) {
				(*this) = (*this) ^ expr;

				return *this;
			}

			template<typename E>
			const Integer& operator<<=(const IntegerBase<E>& expr) {
				(*this) = (*this) << expr;

				return *this;
			}

			template<typename E>
			const Integer& operator>>=(const IntegerBase<E>& expr) {
				(*this) = (*this) >> expr;

				return *this;
			}

			Integer operator--(int) {
				if (this->sign == NEGATIVE) {
					*this->body = (*this->body)++;
				}
				else {
					*this->body = (*this->body)--;
				}

				return *this;
			}

			Integer operator++(int) {
				if (this->sign == NEGATIVE) {
					*this->body = (*this->body)--;
				}
				else {
					*this->body = (*this->body)++;
				}
				return *this;
			}

			string_type Str() const {
				auto s = (this->sign == POSITIVE) ? "" : "-";
				string_type str = body->Str();
				
				return s + str;
			}

			const Integer& Evaluate() const {
				return *this;
			}
		};

		namespace constants {
			namespace integers {
				static const Integer ZERO = Integer();
				static const Integer ONE = Integer(1);
				static const Integer NEG_ONE = Integer(-1);
			}
		}
	}
}