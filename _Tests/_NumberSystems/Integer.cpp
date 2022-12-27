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

TEST(IntegerNumber, ZeroRepresentation) {
	Integer x = Integer(0);
	Integer y = Integer("-0");
	Integer z = Integer(1234354355);
	ASSERT_EQ(x, y);
	ASSERT_EQ(x + y, x);
	ASSERT_EQ(y + z, z);
	ASSERT_EQ(z - y, z);
	ASSERT_EQ(z * y, x);
}

TEST(IntegerArtihmetic, Increment) {
	Integer x = Integer(-1);
	ASSERT_EQ(x++, Integer(0));

	ASSERT_EQ(x + Integer(1), Integer(1));
}

TEST(IntegerArtihmetic, Decrement) {
	Integer x = Integer(1);
	ASSERT_EQ(x--, Integer(0));

	ASSERT_EQ(x + Integer(-1), Integer(-1));
}

TEST(IntegerArithmetic, Negation) {
	Integer x = Integer("359487298390812309871083");
	Integer y = -x;

	ASSERT_EQ(x + y, Integer(0));
	ASSERT_EQ(-y, x);
}

TEST(IntegerArithmetic, Addition) {
	Integer x = Integer("-234598203408920482930458123903582908231593421945039682139815923794937479239574929912492346991292906204234023402412916393479043938418494785823682480223981");
	Integer y = Integer("-79021391923109241024932639548360934204354069481020130123024953520002394979469242938238289382130128512039123");
	Integer a = Integer("239893812739108231203811322192343942958568585807324912031231001000123131923924932593954395293548623");
	Integer b = Integer("991245824082340327032747324082081279381238123013918203210325924999910102130102313212647351201094235020124035923953943953942001002943959356093059353490530");

	ASSERT_EQ(a + b, Integer(POSITIVE, a.Magnitude() + b.Magnitude()));
	ASSERT_EQ(x + y, Integer(NEGATIVE, x.Magnitude() + y.Magnitude()));
	ASSERT_EQ(x + a, Integer(NEGATIVE, x.Magnitude() - a.Magnitude()));
	ASSERT_EQ(y + b, Integer(POSITIVE, b.Magnitude() - y.Magnitude()));
}

TEST(IntegerArithmetic, Subtraction) {
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

TEST(IntegerArithmetic, Multiplication) {
	Integer x = Integer("-234598203408920482930458123903582908231593421945039682139815923794937479239574929912492346991292906204234023402412916393479043938418494785823682480223981");
	Integer y = Integer("-79021391923109241024932639548360934204354069481020130123024953520002394979469242938238289382130128512039123");
	Integer a = Integer("239893812739108231203811322192343942958568585807324912031231001000123131923924932593954395293548623");
	Integer b = Integer("991245824082340327032747324082081279381238123013918203210325924999910102130102313212647351201094235020124035923953943953942001002943959356093059353490530");
	
	ASSERT_EQ(a * b, Integer(POSITIVE, a.Magnitude() * b.Magnitude()));
	ASSERT_EQ(x * y, Integer(POSITIVE, x.Magnitude() * y.Magnitude()));
	ASSERT_EQ(x * a, Integer(NEGATIVE, x.Magnitude() * a.Magnitude()));
	ASSERT_EQ(y * b, Integer(NEGATIVE, b.Magnitude() * y.Magnitude()));
}

TEST(IntegerArithmetic, Division) {
	Integer x = Integer("-234598203408920482930458123903582908231593421945039682139815923794937479239574929912492346991292906204234023402412916393479043938418494785823682480223981");
	Integer y = Integer("-79021391923109241024932639548360934204354069481020130123024953520002394979469242938238289382130128512039123");
	Integer a = Integer("239893812739108231203811322192343942958568585807324912031231001000123131923924932593954395293548623");
	Integer b = Integer("991245824082340327032747324082081279381238123013918203210325924999910102130102313212647351201094235020124035923953943953942001002943959356093059353490530");

	ASSERT_EQ(a / b, Integer(POSITIVE, a.Magnitude() / b.Magnitude()));
	ASSERT_EQ(x / y, Integer(POSITIVE, x.Magnitude() / y.Magnitude()));
	ASSERT_EQ(x / a, Integer(NEGATIVE, x.Magnitude() / a.Magnitude()));
	ASSERT_EQ(b / y, Integer(NEGATIVE, b.Magnitude() / y.Magnitude()));
}

TEST(IntegerArithmetic, ZeroArithmetic) {
	Integer x = Integer("984728394738973894205305732968738294087324902741472498172428760294");
	Integer y = Integer("-984728394738973894205305732968738294087324902741472498172428760294");

	ASSERT_EQ(x + y, Integer());
	ASSERT_EQ(y + x, Integer());

	ASSERT_EQ(x - x, Integer());
	ASSERT_EQ(y - y, Integer());

	ASSERT_EQ(x * Integer(), Integer());
	ASSERT_EQ(y * Integer(), Integer());
	ASSERT_EQ(Integer() * x, Integer());
	ASSERT_EQ(Integer() * y, Integer());
	ASSERT_EQ(Integer() / x, Integer());
	ASSERT_EQ(Integer() / y, Integer());

	ASSERT_NE(x, y);
}

TEST(IntegerArithmetic, Modulo) {
	Integer x = Integer("-234598203408920482930458123903582908231593421945039682139815923794937479239574929912492346991292906204234023402412916393479043938418494785823682480223981");
	Integer y = Integer("-79021391923109241024932639548360934204354069481020130123024953520002394979469242938238289382130128512039123");
	Integer a = Integer("239893812739108231203811322192343942958568585807324912031231001000123131923924932593954395293548623");
	Integer b = Integer("991245824082340327032747324082081279381238123013918203210325924999910102130102313212647351201094235020124035923953943953942001002943959356093059353490530");

	Integer z = (x / y) * y;
	Integer r = x % y;

	ASSERT_EQ((a / b) * b + a % b , a);
	ASSERT_EQ((x / a) * a + x % a , x);
	ASSERT_EQ((b / x) * x + b % x , b);
	ASSERT_EQ((x / y) * y + x % y , x);
}

TEST(IntegerArithmetic, PerfectRemainder) {
	Integer a = Integer("24682468246824682468246824682468");
	Integer na = Integer("-24682468246824682468246824682468");
	Integer b = Integer("12341234");
	Integer nb = Integer("-12341234");

	ASSERT_EQ((a % b), Integer());
	ASSERT_EQ((a % nb), Integer());
	ASSERT_EQ((na % b), Integer());
	ASSERT_EQ((na % nb), Integer());
	
	ASSERT_EQ((a / b) * b + a % b, a);
	ASSERT_EQ((a / nb) * nb + a % nb, a);
	ASSERT_EQ((na / b) * b + na % b, na);
	ASSERT_EQ((na / nb) * nb + na % nb, na);
}

TEST(IntegerBitwise, AND) {
	Integer x = -16;
	Integer y = 99;
	
	ASSERT_EQ(x & y, Integer(96));
	ASSERT_EQ(x & x, x);
	ASSERT_EQ(x & Integer(), Integer());
	ASSERT_EQ(Integer() & Integer(), Integer());
}

TEST(IntegerBitwise, OR) {
	Integer x = -16;
	Integer y = 99;

	ASSERT_EQ(x | y, Integer(-16 | 99));
	ASSERT_EQ(x | x, x);
	ASSERT_EQ(x | Integer(), x);
	ASSERT_EQ(Integer() | Integer(), Integer());
}

TEST(IntegerBitwise, XOR) {
	Integer x = -16;
	Integer y = 99;

	ASSERT_EQ(x ^ y, Integer(-16 ^ 99));
	ASSERT_EQ(x ^ x, Integer());
	ASSERT_EQ(x ^ Integer(), x);
	ASSERT_EQ(Integer() ^ Integer(), Integer(-1));
}

TEST(IntegerBitwise, NOT) {
	Integer x = -16;
	Integer y = 99;
	
	Integer zero = Integer();

	ASSERT_EQ(~x, Integer(~(-16)));
	ASSERT_EQ(~~x, x);
	ASSERT_EQ(~y, Integer(~99));
	ASSERT_EQ(~~y, y);
	ASSERT_EQ(~zero, Integer(-1));
}

TEST(IntegerBitwise, LeftShift) {
	Integer x = -16;
	Integer y = 3;

	ASSERT_EQ(x << y, Integer(-16 << 3));
	ASSERT_THROW(y << x, UndefinedBitshift);
}

TEST(IntegerBitwise, RightShift) {
	Integer x = -16;
	Integer y = 3;

	ASSERT_EQ(x >> y, Integer(-16 >> 3));
	ASSERT_THROW(y >> x, UndefinedBitshift);
}