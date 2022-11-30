#include "pch.h"

using namespace MathLib::NumberSystems;

TEST(Natural, Basic) {
	Natural x = Natural("1234567");
	
	ASSERT_EQ(x.Val(), "1234567");
}