#pragma once
#include "../../headers/Fwd.h"
#include "../../Exceptions.h"

#include "../Natural/Natural.h"
#include "../Integer/Integer.h"
#include "RealBase.h"

namespace MathLib {
	namespace NumberSystems {
		
		const unsigned DEFAULT_PRECISION = 32;

		class Real : public RealBase<Real>, public Stringable {
		private:
			Integer* mantissa = new Integer();
			Integer* exponent = new Integer();
			Natural* precision = new Natural(DEFAULT_PRECISION);

			void SetBody(const Integer& mantissa, const Integer& exponent = constants::integers::ZERO, const Natural& precision = Natural(DEFAULT_PRECISION)) {
				*(this->mantissa) = mantissa;
				*(this->exponent) = exponent;
				*(this->precision) = precision;
			}

		public:
			Real() {

			}

			~Real() {
				delete mantissa;
				delete exponent;
				delete precision;
			}

			Real(const Integer& mantissa, const Integer& exponent = constants::integers::ZERO, const Natural& precision = Natural(DEFAULT_PRECISION)) {
				SetBody(mantissa, exponent, precision);
			}

			Real(const Real& other) {
				SetBody(*other.mantissa, *other.exponent, *other.precision);
			}

			void operator=(const Real& other) {
				SetBody(*other.mantissa, *other.exponent, *other.precision);
			}

			template<typename E>
			Real(const RealBase<E>& expr) {
				Real eval = expr.Evaluate();
				SetBody(*eval.mantissa, *eval.exponent, *eval.precision);
			}

			template<typename E>
			void operator=(const RealBase<E>& expr) {
				Real eval = expr.Evaluate();
				SetBody(*eval.mantissa, *eval.exponent, *eval.precision);
			}

			Integer Mantissa() const {
				return *(this->mantissa);
			}

			Integer Exponent() const {
				return *(this->exponent);
			}

			Natural Precision() const {
				return *(this->precision);
			}

			string_type Str() const {
				auto s = mantissa->Str() + "e" + exponent->Str();

				return s;
			}

			const Real& Evaluate() const {
				return *this;
			}
		};
	}
}