#include "pch.h"

using namespace MathLib::NumberSystems;

TEST(NaturalNumbers, Basic) {
	Natural x = Natural("12345678910111213141516999");
	
	ASSERT_EQ(x.Val(), "12345678910111213141516999");

	auto digits = x.Digits();

	ASSERT_EQ(std::to_string(digits[0]), "141516999");

	ASSERT_THROW(Natural("abcd"), InvalidNumericString);
	
}

TEST(NaturalNumbers, Zero) {
	Natural x = Natural();

	ASSERT_EQ(x.Val(), "0");
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
	Natural x = std::string(  "1292748172418241858125812871274128");
	Natural y = std::string("112128912837121279414917241724174291");

	Natural z = x + y; 
	x += y;

	ASSERT_EQ(z.Val(), x.Val());
}

TEST(NaturalNumbers, Ord) {
	Natural p = std::string("1529489283429841241453295214");
	Natural y = std::string("1529489283429941241453295214");
	Natural x = std::string("1529489283429841241453295214");
	Natural z = std::string( "321324352352352352532521231");

	ASSERT_TRUE(x != y && y != z && x != z);
	ASSERT_TRUE(y > x && x < y);
	ASSERT_TRUE(p == x);
	ASSERT_TRUE(p >= x && x <= p);
	ASSERT_TRUE(x > z);
	ASSERT_TRUE(z < y);
	ASSERT_TRUE(x >= z);
	ASSERT_TRUE(z <= y);
	ASSERT_TRUE(x + y > y + z);
}

TEST(NaturalNumbers, Subtraction) {
	Natural x = std::string("99999999999999999999");
	Natural y = std::string(         "12345678910");

	ASSERT_THROW(y - x, InvalidSubtractionOperation);

	ASSERT_EQ(x - y, Natural("99999999987654321089"));
}

TEST(NaturalNumbers, SubtractionWithBorrow) {
	Natural x = std::string("100000000000000");
	Natural y = std::string(    "12345678910");

	auto z = x - y;

	ASSERT_EQ(z + y, x);
}