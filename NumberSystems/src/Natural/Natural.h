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

			void ClearDigits() {
				body->clear();
			}

		public :

			Natural() {

			}

			~Natural() {

			}			
			
			Natural(const string_type& value) {
				ClearDigits();
				*body = detail::Parse(value);
			}

			void operator=(const string_type& value){
				ClearDigits();
				auto digits = detail::Parse(value);

				for (auto d : digits) {
					AddDigitLeft(d);
				}
			}

			Natural(const vector_type vec) {
				ClearDigits();
				for (auto d : vec) {
					AddDigitLeft(d);
				}
			}

			void operator= (const vector_type vec) {
				ClearDigits();
				for (auto d : vec) {
					AddDigitLeft(d);
				}
			}

			void operator=(const Natural& expr) {
				ClearDigits();
				for (auto d : *expr.body) {
					AddDigitLeft(d);
				}
			}

			template<typename E>
			Natural(const NaturalBase<E>& expr) {
				ClearDigits();
				auto digits = expr.Digits();
				for (auto d : digits) {
					AddDigitLeft(d);
				}
			}

			template<typename E>
			void operator=(const NaturalBase<E>& expr) {
				ClearDigits();
				auto digits = expr.Digits();
				for (auto d : digits) {
					AddDigitLeft(d);
				}
			}

			const vector_type Digits() const {
				return *this->body;
			}

			const Natural& AddDigitLeft(data_type digit) {
				this->body->push_back(digit);
				return *this;
			}

			const Natural& AddDigitRight(data_type digit) {
				if (digit >= 0) {
					this->body->insert(this->body->begin(), digit);
				}
				return *this;
			}

			const Natural& RemoveLeadingZeroes() {
				index_type i = Size() - 1;;
				for (i; i >= 0; --i) {
					if (this->body->at(i) != 0) {
						break;
					}
				}

				if (i > 1)
					this->body->resize(i + 1);

				return *this;
			}

			data_type operator[](index_type idx) const{
				return (*this->body)[idx];
			}

			data_type& operator[](index_type idx) {
				return (*this->body)[idx];
			}

			template<typename E>
			const Natural& operator+=(const NaturalBase<E>& expr) {
				(*this) = (*this) + expr;

				return *this;
			}

			const Natural& Evaluate() const{
				return *this;
			}
		};

	}
}