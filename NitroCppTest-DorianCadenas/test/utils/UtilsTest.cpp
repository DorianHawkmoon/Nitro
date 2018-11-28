#include <gtest/gtest.h>
#include "utils/Utils.h"
#include <type_traits>

#define NAME_CLASS UtilsTest

using namespace IntersectionChecker::Maths;
using namespace IntersectionChecker::Utils;

/*
TODO improve test for the SFINAE approach of the template
//https://cpptalk.wordpress.com/2009/09/12/substitution-failure-is-not-an-error-2/
template<typename T>
struct HasValue {
	struct Fallback { int x; }; // introduce member name "x"
	struct Derived : T, Fallback {}; //problem diamond, inherit both from T and Fallback

	template<typename C, C> struct ChT;

	//function for the instantiated template
	template<typename C> static char(&f(ChT<int Fallback::*, &C::x>*))[1];
	//function if template above is not posible (SFINAE)
	template<typename C> static char(&f(...))[2]; //variadic has lower priority

	static bool const value = sizeof(f<Derived>(0)) == 2;
};
*/


TEST(NAME_CLASS, ValidDataVector2) {
	Vector2<int> valid(5, 6);
	Vector2<float> stillValid(2, 3.0);
	
	
	//HasValue<Vector2<bool>>::value);
	//HasValue<Vector2<std::string>>::value);
	//HasValue<Vector2<char>>::value);

}

TEST(NAME_CLASS, ConstructorVector2) {
	Vector2<int> normal;
	EXPECT_EQ(normal.x, 0);
	EXPECT_EQ(normal.y, 0);

	Vector2<int> arguments(5, 6);
	EXPECT_EQ(arguments.x, 5);
	EXPECT_EQ(arguments.y, 6);

	Vector2<float> argumentsFloat(5, 6);
	EXPECT_FLOAT_EQ(arguments.x, 5);
	EXPECT_FLOAT_EQ(arguments.y, 6);
}

TEST(NAME_CLASS, CopyConstructorVector2) {
	Vector2<int> arguments(5, 6);
	Vector2<int> copy=arguments;
	Vector2<int> asign;
	asign = copy;

	EXPECT_EQ(copy.x, 5);
	EXPECT_EQ(copy.y, 6);

	EXPECT_EQ(asign.x, 5);
	EXPECT_EQ(asign.y, 6);
}

TEST(NAME_CLASS, NumberToString) {
	EXPECT_EQ(NumberToString<int>(2), "2");
	EXPECT_EQ(NumberToString<int>(-5), "-5");
	EXPECT_EQ(NumberToString<float>(3), "3");
	EXPECT_EQ(NumberToString<float>(3.0f), "3");
	EXPECT_EQ(NumberToString<float>(3.5), "3.5");
}