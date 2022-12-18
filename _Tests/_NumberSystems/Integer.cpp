#include "pch.h"

using namespace MathLib::NumberSystems;

TEST(IntegerNumber, Basic) {

	Integer x = Integer("-12345746121231312313469363209452094192341");
	Integer y = Integer("4624361212324639534851824182389123912");

	ASSERT_EQ(x.Str(), "-12345746121231312313469363209452094192341");
	ASSERT_EQ(y.Str(), "4624361212324639534851824182389123912");

	x = -123;
	y = 123;
	ASSERT_EQ(x.Str(), "-123");
	ASSERT_EQ(y.Str(), "123");

	x = 0;
	ASSERT_EQ(x.Str(), "0");
}


TEST(IntegerNumber, NaturalCompatibility) {

	Natural a = Natural("999999");
	Natural b = Natural("1239534875129487");

	Integer x = a + b;

	ASSERT_EQ(x.Str(), (a + b).Evaluate().Str());
}

TEST(IntegerNumber, Ordering) {
	Integer x = Integer("-23459820340892048293045812390358290823123981");
	Integer y = Integer("-1938238289382130128512039123");
	Integer a = Integer("2398938127391082312038123");
	Integer b = Integer("09124582408234032703274732408208127938123812301391820321");


	Integer z = x;
	Integer c = b;

	ASSERT_TRUE(x < y && y < a && a < b);
	ASSERT_TRUE(b > a && a > y && y > x);
	ASSERT_TRUE(x < a && b > y);
	ASSERT_TRUE(x != y && x != b);
	ASSERT_TRUE(z == x);
	ASSERT_TRUE(c == b);
	ASSERT_TRUE(z <= x && x >= z);
	ASSERT_TRUE(c <= b && b >= c);
	ASSERT_TRUE(z != b && z != y);
}

TEST(IntegerNumber, Addition) {
	Integer x = Integer("-234598203408920482930458123903582908231593421945039682139815923794937479239574929912492346991292906204234023402412916393479043938418494785823682480223981");
	Integer y = Integer("-79021391923109241024932639548360934204354069481020130123024953520002394979469242938238289382130128512039123");
	Integer a = Integer("239893812739108231203811322192343942958568585807324912031231001000123131923924932593954395293548623");
	Integer b = Integer("991245824082340327032747324082081279381238123013918203210325924999910102130102313212647351201094235020124035923953943953942001002943959356093059353490530");

	ASSERT_EQ(a + b, Integer(POSITIVE, a.Magnitude() + b.Magnitude()));
	ASSERT_EQ(x + y, Integer(NEGATIVE, x.Magnitude() + y.Magnitude()));
	ASSERT_EQ(x + a, Integer(NEGATIVE, x.Magnitude() - a.Magnitude()));
	ASSERT_EQ(y + b, Integer(POSITIVE, b.Magnitude() - y.Magnitude()));
}

TEST(IntegerNumber, Subtraction) {
	Integer x = Integer("-234598203408920482930458123903582908231593421945039682139815923794937479239574929912492346991292906204234023402412916393479043938418494785823682480223981");
	Integer y = Integer("-79021391923109241024932639548360934204354069481020130123024953520002394979469242938238289382130128512039123");
	Integer a = Integer("239893812739108231203811322192343942958568585807324912031231001000123131923924932593954395293548623");
	Integer b = Integer("991245824082340327032747324082081279381238123013918203210325924999910102130102313212647351201094235020124035923953943953942001002943959356093059353490530");

	ASSERT_EQ(a - b, Integer(NEGATIVE, b.Magnitude() - a.Magnitude()));
	ASSERT_EQ(b - a, Integer(POSITIVE, b.Magnitude() - a.Magnitude()));

	ASSERT_EQ(x - y, Integer(NEGATIVE, x.Magnitude() - y.Magnitude()));
	ASSERT_EQ(y - x, Integer(POSITIVE, x.Magnitude() - y.Magnitude()));

	ASSERT_EQ(x - a, Integer(NEGATIVE, x.Magnitude() + a.Magnitude()));
	ASSERT_EQ(a - x, Integer(POSITIVE, x.Magnitude() + a.Magnitude()));

	ASSERT_EQ(y - b, Integer(NEGATIVE, b.Magnitude() + y.Magnitude()));
	ASSERT_EQ(b - y, Integer(POSITIVE, b.Magnitude() + y.Magnitude()));
}