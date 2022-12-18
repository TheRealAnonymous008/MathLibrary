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
	//ASSERT_TRUE(b > a && a > y && y > x);
	//ASSERT_TRUE(x < a && b > y);
	//ASSERT_TRUE(x != y && x != b);
	//ASSERT_TRUE(z == x);
	//ASSERT_TRUE(c == b);
	//ASSERT_TRUE(z <= x && x >= z);
	//ASSERT_TRUE(c <= b && b >= c);
	//ASSERT_TRUE(z != b && z != y);
}