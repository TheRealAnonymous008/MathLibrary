#include "pch.h"

using namespace MathLib::NumberSystems;

TEST(NaturalNumbers, Basic) {
	Natural x = Natural("12345678910111213141516999");
	
	ASSERT_EQ(x.Val(), "12345678910111213141516999");

	auto digits = x.Digits();

	ASSERT_EQ(std::to_string(digits[0]), "141516999");

	ASSERT_THROW(Natural("abcd"), InvalidNumericString);
	
}

TEST(NaturalNumbers, Addition) {
	Natural x = std::string("1234567890987654321");
	Natural y = std::string("9876543210123456789");

	Natural z = x + y;

	std::cout<<z.Val()<<"\n";
}