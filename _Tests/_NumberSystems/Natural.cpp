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
	Natural x = std::string("9999999999999999999999999999999999999");
	Natural y = std::string("9999999999999999999999999999999999999");

	Natural z = x + y;

	ASSERT_EQ(z.Val(), "19999999999999999999999999999999999998");
}

TEST(NaturalNumbers, AdditionUnequalSizes) {
	Natural x = std::string("9999999999999999999999999999999999999");
	Natural y = std::string("1");

	Natural z = x + y;

	ASSERT_EQ(z.Val(), "10000000000000000000000000000000000000");
}

TEST(NaturalNumbers, Eager) {
	Natural x = std::string("1292748172418241858125812871274128");
	Natural y = std::string("112128912837121279414917241724174291");

	Natural z = x + y;

	ASSERT_EQ(z.Val(), z.Evaluate().Val());
}

TEST(NaturalNumbers, PlusEqual) {
	Natural x = std::string("1292748172418241858125812871274128");
	Natural y = std::string("112128912837121279414917241724174291");

	Natural z = x + y; 
	x += y;

	ASSERT_EQ(z.Val(), x.Val());
}