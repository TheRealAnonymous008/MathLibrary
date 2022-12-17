#include "pch.h"

using namespace MathLib::NumberSystems;

TEST(IntegerNumber, Basic) {

	Integer x = Integer("-12345746121231312313469363209452094192341");
	Integer y = Integer("4624361212324639534851824182389123912");

	ASSERT_EQ(x.Str(), "-12345746121231312313469363209452094192341");
	ASSERT_EQ(y.Str(), "4624361212324639534851824182389123912");
}


TEST(IntegerNumber, NaturalCompatibility) {

	Natural a = Natural("999999");
	Natural b = Natural("1239534875129487");

	Integer x = a + b;
}