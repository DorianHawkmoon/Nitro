#include <gtest/gtest.h>
#include "utils/Utils.h"
#include <type_traits>

#define NAME_CLASS UtilsTest

using namespace ShapeOverlay::Maths;
using namespace ShapeOverlay::Utils;

TEST(NAME_CLASS, ValidDataVector2) {
	Vector2<int> valid(5, 6);
	Vector2<float> stillValid(2, 3.0);
	
	EXPECT_THROW({Vector2<std::string> noValid;}, std::exception);
	EXPECT_THROW({Vector2<bool> noValid; }, std::exception);
	EXPECT_THROW({Vector2<char> noValid; }, std::exception);
	EXPECT_THROW({Vector2<std::string> noValid("asdf","asdf"); }, std::exception);
	EXPECT_THROW({Vector2<std::string> noValid("h","s"); }, std::exception);
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