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
			bool sign = POSITIVE;
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
				*body = Natural(parsed.body);
				sign = parsed.sign;
			}

			void operator=(const string_type& value){
				auto parsed = detail::ParseInteger(value);
				*body = Natural(parsed.body);
				sign = parsed.sign;
			}

			template<std::integral T>
			Integer(T value) {
				ClearLimbs();

				if (value == 0) {
					return;
				}

				sign = (value < 0);

				while (value > LIMB_BASE) {
					body->AddMostLimb(value % LIMB_BASE);
					value = value = value / LIMB_BASE;
				}
				body->AddMostLimb(value);
			}
			
			template<std::integral T>
			void operator=(T value) {
				ClearLimbs();

				if (value == 0) {
					return;
				}

				sign = (value < 0);

				while (value > LIMB_BASE) {
					body->AddMostLimb(value % LIMB_BASE);
					value = value = value / LIMB_BASE;
				}
				body->AddMostLimb(value);
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

			const size_type Size() const {
				return this->body->Size();
			}

			const bool Sign() const {
				return this->sign;
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

			string_type Str() const {
				auto s = (this->sign == POSITIVE) ? "" : "-";
				return s + body->Str();
			}

			const Integer& Evaluate() const {
				return *this;
			}
		};
	}
}