#include "pch.h"

using namespace MathLib::NumberSystems;

TEST(NaturalNumbers, Basic) {

	Natural x = Natural("12345678910111213141516999");
	
	ASSERT_EQ(x.Val(), "12345678910111213141516999");

	auto digits = x.Digits();

	ASSERT_THROW(Natural("abcd"), InvalidNumericString);
}

TEST(NaturalNumbers, Zero) {
	Natural x = Natural();

	ASSERT_EQ(x.Val(), "0");
	
	Natural y = Natural("201221765421199947510");

	ASSERT_EQ((x + y), y);
}

TEST(NaturalNumbers, ULL) {
	Natural x = 123456;
	ASSERT_EQ(x, Natural("123456"));

	Natural y = ULLONG_MAX;
	ASSERT_EQ(y, Natural(std::to_string(ULLONG_MAX)));

}

TEST(NaturalArithmetic, Addition) {
	Natural x = std::string("9999999999999999999999999999999999999");
	Natural y = std::string("9999999999999999999999999999999999999");

	Natural z = x + y;

	ASSERT_EQ(z, Natural("19999999999999999999999999999999999998"));
}

TEST(NaturalArithmetic, AdditionUnequalSizes) {
	Natural x = std::string("9999999999999999999999999999999999999");
	Natural y = std::string("1");

	Natural z = x + y;

	ASSERT_EQ(z, Natural("10000000000000000000000000000000000000"));
}

TEST(NaturalArithmetic, Eager) {
	Natural x = std::string("1292748172418241858125812871274128");
	Natural y = std::string("112128912837121279414917241724174291");

	Natural z = x + y;

	ASSERT_EQ(z.Val(), z.Evaluate().Val());
}

TEST(NaturalArithmetic, PlusEqual) {
	Natural x = std::string(  "1292748172418241858125812871274128");
	Natural y = std::string("112128912837121279414917241724174291");

	Natural z = x + y; 
	x += y;

	ASSERT_EQ(z, x);
}

TEST(NaturalArithmetic, Ord) {
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

TEST(NaturalArithmetic, Subtraction) {
	Natural x = std::string("99999999999999999999");
	Natural y = std::string(         "12345678910");

	ASSERT_EQ(x - y, Natural("99999999987654321089"));
}

TEST(NaturalArithmetic, SubtractionWithBorrow) {
	Natural x = std::string("100000000000000");
	Natural y = std::string("12345678910");

	auto z = x - y;

	ASSERT_EQ(z + y, x);
	ASSERT_EQ(x + y - y, x);

}

TEST(NaturalArithmetic, MultiplicationSmall) {
	Natural x = std::string("1234123412341234");
	Natural y = 2;

	ASSERT_EQ((x * y), Natural("2468246824682468"));
	ASSERT_EQ((x * Natural(3)), (x * y + x));
}

TEST(NaturalArithmetic, MultiplicationLarge) {
	Natural x = std::string("1291481248124155");
	Natural y = std::string("8241255743525941");

	ASSERT_EQ((x * y), Natural("10643427253759243309891831204855"));

	auto x2 = x * x;
	auto x3 = x * x * x;
	auto y3 = y * y * y;
	
	ASSERT_EQ((x3), Natural("2154092329411760158758784688638048092381023875"));
	ASSERT_EQ((x3), x2 * x);

	ASSERT_EQ(y3, Natural("559732048897626335341862485738274677761989812621"));
}

TEST(NaturalArithmetic, MultiplicationStressTest) {
	Natural x = std::string("912847598293293742934928749827489172831423840248235601270583274623478124973519407342947283427342393");
	Natural y = std::string("293472749235728428357126940735827434810239242572935092398472871028038485776249124983758612483248394");

	auto z = x * y;

	auto result = Natural("267,895,894,304,364,752,678,868,955,431,824,907,367,753,146,322,020,621,335,624,329,595,212,336,512,781,781,585,428,916,823,953,974,814,585,680,226,678,326,375,639,556,132,623,499,217,174,608,843,391,469,389,219,335,124,993,828,874,277,769,329,364,543,105,366,842");
	ASSERT_EQ(z, result);
	ASSERT_EQ((x * y), (y * x));

}

TEST(NaturalArithmetic, KaratsubaTest) {
	Natural x = std::string("912847598293293742934928749827489172831423840248235601270583274623478124973519407342947283427342393");
	Natural y = std::string("293472749235728428357126940735827434810239242572935092398472871028038485776249124983758612483248394");

	auto z = implementation::KaratsubaMultiplication<1>(x, y);

	auto result = Natural("267,895,894,304,364,752,678,868,955,431,824,907,367,753,146,322,020,621,335,624,329,595,212,336,512,781,781,585,428,916,823,953,974,814,585,680,226,678,326,375,639,556,132,623,499,217,174,608,843,391,469,389,219,335,124,993,828,874,277,769,329,364,543,105,366,842");
	ASSERT_EQ(z, result);
}

TEST(NaturalArithmetic, DivisionTiny) {
	Natural x = Natural("1234");
	Natural k = x / Natural("2");
	
	std::cout << k.Val() << "\n";
	ASSERT_EQ(k, Natural("617"));
}

TEST(NaturalArithmetic, DivisionSmall) {
	Natural x = Natural("766970544842443844");
	Natural y = Natural(	     "862664913");

	Natural z = x / y;

	ASSERT_TRUE(x <= z * y + y);

	std::cout << (z * y).Val() << "\n";
	std::cout << (x).Val() << "\n";
	ASSERT_TRUE(z * y <= x + y);
}


TEST(NaturalArithmetic, DivisionLarge) {
	Natural x = Natural("10643427253759243309891831204855");
	Natural y = Natural("8241255743525941");

	Natural z = x / y;
	Natural expected = Natural("1291481248124155");

	expected.Log();
	z.Log();

	ASSERT_EQ(z, expected);
}

//TEST(NaturalArithmetic, DivisionStresss) {
//	Natural x = Natural("267,895,894,304,364,752,678,868,955,431,824,907,367,753,146,322,020,621,335,624,329,595,212,336,512,781,781,585,428,916,823,953,974,814,585,680,226,678,326,375,639,556,132,623,499,217,174,608,843,391,469,389,219,335,124,993,828,874,277,769,329,364,543,105,366,842");
//	Natural y = Natural("293472749235728428357126940735827434810239242572935092398472871028038485776249124983758612483248394");
//
//	Natural z = x / y;
//}
