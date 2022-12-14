#include "pch.h"

using namespace MathLib::NumberSystems;

TEST(NaturalNumbers, Basic) {

	Natural x = Natural("12345678910111213141516999");
	
	ASSERT_EQ(x.Str(), "12345678910111213141516999");

	auto digits = x.Digits();

	ASSERT_THROW(Natural("abcd"), InvalidNumericString);
}

TEST(NaturalNumbers, Zero) {
	Natural x = Natural();

	ASSERT_EQ(x.Str(), "0");
	
	Natural y = Natural("201221765421199947510");

	ASSERT_EQ((x + y), y);
}

TEST(NaturalNumbers, ULL) {
	Natural x = 123456;
	ASSERT_EQ(x, Natural("123456"));

	Natural y = ULLONG_MAX;
	ASSERT_EQ(y, Natural(std::to_string(ULLONG_MAX)));

}

TEST(NaturalNumbers, LeadingZeroes) {
	vector_type limbs = { 1, 0 };
	Natural x = Natural(limbs);
	x.RemoveLeadingZeroes();

	ASSERT_EQ(x.Size(), 1);

}

TEST(NaturalOrd, Ord) {
	Natural p = std::string("1529489283429841241453295214");
	Natural y = std::string("1529489283429941241453295214");
	Natural x = std::string("1529489283429841241453295214");
	Natural z = std::string("321324352352352352532521231");

	ASSERT_TRUE(x + Natural("1") > x);
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

TEST(NaturalOrd, ZeroRepresentation) {
	Natural z1 = Natural();
	Natural z2 = Natural(0);
	Natural z3 = Natural("0");
	Natural z4 = Natural("00000000000000000000000000000000000000000000");

	ASSERT_EQ(z1, z2);
	ASSERT_EQ(z1, z3);
	ASSERT_EQ(z1, z4);
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

	ASSERT_EQ(z.Str(), z.Evaluate().Str());
}

TEST(NaturalArithmetic, PlusEqual) {
	Natural x = std::string(  "1292748172418241858125812871274128");
	Natural y = std::string("112128912837121279414917241724174291");

	Natural z = x + y; 
	x += y;

	ASSERT_EQ(z, x);
}

TEST(NaturalArithmetic, Subtraction) {
	Natural x = std::string("99999999999999999999");
	Natural y = std::string(         "12345678910");

	ASSERT_EQ(x - y, Natural("99999999987654321089"));
	ASSERT_THROW(y - x, InvalidSubtractionOperation);
}

TEST(NaturalArithmetic, SubtractionWithBorrow) {
	Natural x = std::string("100000000000000");
	Natural y = std::string(    "12345678910");

	auto z = x - y;

	ASSERT_EQ(z + y, x);
	ASSERT_EQ(x + y - y, x);

}

TEST(NaturalArithmetic, SubtractionEqualLength) {
	Natural x = std::string("82410293512432931023812");
	Natural y = std::string("66940392833103219032431");

	auto z = x - y;

	ASSERT_EQ(z + y, x);
	ASSERT_EQ(x + y - y, x);

}

TEST(NaturalArithmetic, Increment) {
	Natural x = Natural();
	x++;

	ASSERT_EQ(x, Natural("1"));

	x = Natural("203498729402759012847021587102481");
	Natural y = x;

	x++;
	ASSERT_EQ(x, y + Natural("1"));
}

TEST(NaturalArithmetic, Decrement) {
	Natural x = Natural("1");
	x--;

	x = Natural("203498729402759012847021587102481");
	Natural y = x;
	x--;
	ASSERT_EQ(x, y - Natural("1"));
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

TEST(NaturalArithmetic, DivisionEqualSizes) {
	Natural x = Natural("1234");
	Natural k = x / Natural("2");
	
	ASSERT_EQ(k, Natural("617"));

	x = Natural("246824682468246824682468");
	Natural y = Natural("12341234");
	k = x / y;
	
	ASSERT_EQ(k * y, x);
}

TEST(NaturalArithmetic, DivisionSmall) {
	Natural x = Natural("766970544842443844");
	Natural y = Natural(	     "862664913");

	Natural z = x / y;

	ASSERT_TRUE(x <= z * y + y);
	ASSERT_TRUE(z * y <= x + y);
}


TEST(NaturalArithmetic, DivisionLarge) {
	Natural x = Natural("10643427253759243309891831204855");
	Natural y = Natural("8241255743525941");

	Natural z = x / y;
	Natural expected = Natural("1291481248124155");

	ASSERT_EQ(z, expected);
}

TEST(NaturalArithmetic, DivisionStress) {
	Natural x = Natural("267,895,894,304,364,752,678,868,955,431,824,907,367,753,146,322,020,621,335,624,329,595,212,336,512,781,781,585,428,916,823,953,974,814,585,680,226,678,326,375,639,556,132,623,499,217,174,608,843,391,469,389,219,335,124,993,828,874,277,769,329,364,543,105,366,842");
	Natural y = Natural("293472749235728428357126940735827434810239242572935092398472871028038485776249124983758612483248394");

	Natural z = x / y;
	Natural expected = std::string("912847598293293742934928749827489172831423840248235601270583274623478124973519407342947283427342393");

	ASSERT_EQ(z, expected);

	x = Natural("128182418418242358791284923482734123305985724872935782347827482734");
	y = Natural("99999999999999999");
	expected = Natural("1,281,824,184,182,423,600,731,091,076,651,577,240,370,768,015,245");
	z = x / y;

	ASSERT_EQ(z, expected);
}

TEST(NaturalArithmetic, DivisionSmallToBig) {
	Natural x = Natural("267,895,894,304,364,752,678,868,955,431,824,907,367,753,146,322,020,621,335,624,329,595,212,336,512,781,781,585,428,916,823,953,974,814,585,680,226,678,326,375,639,556,132,623,499,217,174,608,843,391,469,389,219,335,124,993,828,874,277,769,329,364,543,105,366,842");
	Natural y = Natural("293472749235728428357126940735827434810239242572935092398472871028038485776249124983758612483248394");

	Natural z = y / x;
	Natural expected = std::string("0");

	ASSERT_EQ(z, expected);
}

TEST(NaturalArithmetic, RecursiveTest) {
	Natural x = Natural("267,895,894,304,364,752,678,868,955,431,824,907,367,753,146,322,020,621,335,624,329,595,212,336,512,781,781,585,428,916,823,953,974,814,585,680,226,678,326,375,639,556,132,623,499,217,174,608,843,391,469,389,219,335,124,993,828,874,277,769,329,364,543,105,366,842");
	Natural y = Natural("744235346246734730463047112");

	auto normalized = implementation::NormalizeDivisionArgs(x, y);
	x = normalized.denominator;
	y = normalized.numerator;

	auto knuth = implementation::KnuthDivision(x, y);
	auto recursive = implementation::RecursiveDivision<3>(x, y);
	ASSERT_EQ(knuth.div, recursive.div);
	ASSERT_EQ(knuth.mod, recursive.mod);
}

TEST(NaturalArithmetic, DivideByZero) {
	Natural x = Natural("289735928359208938057903589082439028318273");
	Natural y = 0;

	ASSERT_THROW(x / y, DivisionByZero);

	y = Natural();
	ASSERT_THROW(x / y, DivisionByZero);

	y = Natural("0");
	ASSERT_THROW(x / y, DivisionByZero);
}

TEST(NaturalArithmetic, ZeroArithmetic) {
	Natural x = Natural();
	Natural y = Natural("1243452824950349529048239412");

	ASSERT_EQ(x / y, Natural());
	ASSERT_EQ(x * y, Natural());
}

TEST(NaturalArithmetic, ModuloSimple) {
	Natural x = std::string("12334223543421892342");
	Natural y = std::string(		   "100000000");

	ASSERT_EQ(x % y, Natural("21892342"));
}

TEST(NaturalArithmetic, ModuloExactLarge) {
	Natural x = Natural("267,895,894,304,364,752,678,868,955,431,824,907,367,753,146,322,020,621,335,624,329,595,212,336,512,781,781,585,428,916,823,953,974,814,585,680,226,678,326,375,639,556,132,623,499,217,174,608,843,391,469,389,219,335,124,993,828,874,277,769,329,364,543,105,366,842");
	Natural y = Natural("293472749235728428357126940735827434810239242572935092398472871028038485776249124983758612483248394");

	ASSERT_EQ(x % y, Natural("0"));
}

TEST(NaturalArithmetic, ModuloLarge) {
	Natural x = Natural("6729438910328437423723127312938713289723894837582194124829374397482138742");
	Natural y = Natural("21381243724723422348374283189231");

	Natural expected = Natural("17812059265469952713876488966778");
	ASSERT_EQ(x % y, expected);
}

TEST(NaturalArithmetic, ModuloSmallToLarge) {
	Natural x = Natural("267,895,894,304,364,752,678,868,955,431,824,907,367,753,146,322,020,621,335,624,329,595,212,336,512,781,781,585,428,916,823,953,974,814,585,680,226,678,326,375,639,556,132,623,499,217,174,608,843,391,469,389,219,335,124,993,828,874,277,769,329,364,543,105,366,842");
	Natural y = Natural("293472749235728428357126940735827434810239242572935092398472871028038485776249124983758612483248394");

	Natural z = y % x;

	ASSERT_EQ(z, y);
}

TEST(NaturalArithmetic, SelfAssignment) {
	Natural base = Natural("123019482348275406274839582349234242424264694857263894038738493749304812912313");
	Natural y = Natural("987678092987552323124923512386486645231316946947762519563500121");

	Natural x;

	x = base;
	x += y;
	ASSERT_EQ(x, base + y);

	x = base;
	x -= y;
	ASSERT_EQ(x, base - y);

	x = base;
	x *= y;
	ASSERT_EQ(x, base * y);

	x = base;
	x /= y;
	ASSERT_EQ(x, base / y);

	x = base;
	x %= y;
	ASSERT_EQ(x, base % y);

}

TEST(NaturalBitwise, AND) {
	Natural x = Natural("192387249827397413287294872148972647618294761971876182371982319412313");
	Natural y = Natural("823742849201298312849123810231031");

	Natural z = x & y;
	for (index_type i = 0; i < z.Size(); ++i) {
		ASSERT_EQ(z[i], x[i] & y[i]);
	}
}

TEST(NaturalBitwise, ANDIdentities) {
	Natural x = Natural("23132812847238172942385272374234092834923849");
	Natural y = Natural("28313912748123712432513282572359912353523521");
	Natural z = Natural("12310231029310321231");

	ASSERT_EQ(x & x, x);
	ASSERT_EQ(x & y, y & x);
	ASSERT_EQ(x & (y & z), (x & y) & z);
	ASSERT_EQ(x & Natural(), Natural());
}

TEST(NaturalBitwise, OR) {
	Natural x = Natural("192387249827397413287294872148972647618294761971876182371982319412313");
	Natural y = Natural("823742849201298312849123810231031");

	Natural z = x | y;

	index_type i = 0;
	for (i = 0; i < y.Size(); ++i) {
		ASSERT_EQ(z[i], x[i] | y[i]);
	}

	for (i; i < x.Size(); ++i) {
		ASSERT_EQ(z[i], x[i] | 0);
	}
}

TEST(NaturalBitwise, ORIdentities) {
	Natural x = Natural("23132812847238172942385272374234092834923849");
	Natural y = Natural("28313912748123712432513282572359912353523521");
	Natural z = Natural("12310231029310321231");

	ASSERT_EQ(x | x, x);
	ASSERT_EQ(x | y, y | x);
	ASSERT_EQ(x | (y | z), (x | y) | z);
	ASSERT_EQ(x | Natural(), x);
}

TEST(NaturalBitwise, XOR) {
	Natural x = Natural("192387249827397413287294872148972647618294761971876182371982319412313");
	Natural y = Natural("823742849201298312849123810231031");

	Natural z = x ^ y;

	index_type i = 0;
	for (i = 0; i < y.Size(); ++i) {
		ASSERT_EQ(z[i], x[i] ^ y[i]);
	}

	for (i; i < x.Size(); ++i) {
		ASSERT_EQ(z[i], x[i] ^ 0);
	}
}

TEST(NaturalBitwise, XORIdentities) {
	Natural x = Natural("23132812847238172942385272374234092834923849");
	Natural y = Natural("28313912748123712432513282572359912353523521");
	Natural z = Natural("12310231029310321231");

	ASSERT_EQ(x ^ y, y ^ x);
	ASSERT_EQ(x ^ (y ^ z), (x ^ y) ^ z);
	ASSERT_EQ(x ^ Natural(), x);
	ASSERT_EQ(x ^ x, Natural());
	ASSERT_EQ(x ^ (y ^ y), x);
}

TEST(NaturalBitwise, NOT) {
	Natural x = Natural("1239817423471293724781293035239572423589124174235651626124723041902382756732859648673653743940121354134131539629289348576866341253391");
	Natural z = ~x;
	
	ASSERT_EQ(~~x, x);

	for (index_type i = 0; i < z.Size(); ++i) {
		ASSERT_EQ(z[i] + x[i], LIMB_BASE - 1);
	}
}

TEST(NaturalBitwise, BooleanIdentities) {
	Natural x = Natural("123019482348275406274839582349234242424264694857263894038738493749304812912313");
	Natural y = Natural("987678092987552323124923512386486645231316946947762519563500121");
	Natural z = Natural("987237549998127310012");

	Natural a = ~(x | y);
	Natural b = ~x & ~y;

	ASSERT_EQ(x | (x & y), x);
	ASSERT_EQ(x & (x | y), x);
	ASSERT_EQ(x | (y & z), (x | y) & (x | z));
	ASSERT_EQ(x & (y | z), (x & y) | (x & z));
	ASSERT_EQ(x & (y ^ z), (x & y) ^ (x & z));
	ASSERT_EQ(x - y, ~(~x + y));
}

TEST(NaturalBitwise, DeMorgansLaw) {
	Natural x = Natural("893019482348275406274839582349234242424264694857263894038738493749304812912313");
	Natural y = Natural("987678092987552323124923512386486645231316946947762519563123153512112324500121");

	ASSERT_EQ(x.Size(), y.Size());
	ASSERT_EQ(~(x | y), ~x & ~y);
	ASSERT_EQ(~(x & y), ~x | ~y);
}

TEST(NaturalBitwise, SelfAssignment) {
	Natural base = Natural("123019482348275406274839582349234242424264694857263894038738493749304812912313");
	Natural y = Natural("987678092987552323124923512386486645231316946947762519563500121");

	Natural x;

	x = base;
	x &= y;
	ASSERT_EQ(x, base & y);

	x = base;
	x |= y;
	ASSERT_EQ(x, base | y);

	x = base;
	x ^= y;
	ASSERT_EQ(x, base ^ y);

}

TEST(NaturalBitShifts, Left) {
	Natural x = Natural("52091");
	Natural y = Natural("123");
	Natural expected = Natural("553,926,524,227,456,421,883,457,708,616,507,434,467,328");

	ASSERT_EQ(x << y, expected);
}

TEST(NaturalBitShifts, Right) {
	Natural x = Natural("553,926,524,227,456,421,883,457,708,616,507,434,467,328");
	Natural y = Natural("123");

	Natural expected = Natural("52091");
	ASSERT_EQ(x >> y, expected);
}

TEST(NaturalBitShifts, LeftOnlyResidue) {
	Natural x = Natural("395683471238923583940968724851724938627182120434");
	Natural y = Natural("13");

	Natural z = x << y;
	Natural expected = x * Natural(8192);

	ASSERT_EQ(z, expected);
}

TEST(NaturalBitShifts, RightOnlyResidue) {
	Natural x = Natural("395683471238923583940968724851724938627182120434");
	Natural y = Natural("13");

	Natural z = x >> y;
	Natural expected = x / Natural("8192");

	ASSERT_EQ(x >> y, expected);
}

TEST(NaturalBitShifts, SelfAssignment) {
	Natural base = Natural("943872394837812930487123982049821702348924121");
	Natural y = Natural("612");
	Natural x;

	x = base;
	x <<= y;
	ASSERT_EQ(x, base << y);

	x = base;
	x >>= y;
	ASSERT_EQ(x, base >> y);

	x = base;
	x <<= y;
	x >>= y;
	ASSERT_EQ(x, base);
	
}