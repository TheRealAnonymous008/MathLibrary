#include "pch.h"

using namespace MathLib::NumberSystems;

TEST(NaturalNumbers, Basic) {
	Natural x = Natural("12345678910111213141516");
	
	ASSERT_EQ(x.Val(), "12345678910111213141516");

	auto digits = x.Digits();

	ASSERT_EQ(std::to_string(digits[0]), "12345");

	ASSERT_THROW(Natural("abcd"), InvalidNumericString);
	
}

TEST(NaturalNumbers, Addition) {
	Natural x = Natural("1245678901234567890");
	Natural y = Natural("987654321987654321");

	x + y;
}