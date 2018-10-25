#include <gtest/gtest.h>
#include "shapes/Rectangle.h"
#include "json/json.h"

#define NAME_CLASS RectangleTest

using namespace ShapeOverlay;

TEST(NAME_CLASS, CorrectRectangle) {
	Json::Value json;

	json["x"] = 100;
	json["y"] = 150;
	json["w"] = 200;
	json["h"] = 300;

	Rectangle rectangle;
	rectangle.Deserialize(json);

	EXPECT_TRUE(rectangle.GetTopLeft().x == 100);
	EXPECT_TRUE(rectangle.GetTopLeft().y == 150);
	EXPECT_TRUE(rectangle.GetSize().x == 200);
	EXPECT_TRUE(rectangle.GetSize().y == 300);
}

TEST(NAME_CLASS, SizeZero) {
	Json::Value json;

	json["x"] = 100;
	json["y"] = 150;
	json["w"] = 0;
	json["h"] = 300;

	Rectangle rectangle;
	EXPECT_THROW({
			try {
				rectangle.Deserialize(json);
			} catch (const std::invalid_argument& error) {
				EXPECT_STREQ("Rectangle::Deserialize Size should be positive", error.what());
				throw;
			}
		}, std::invalid_argument);

	json["x"] = 100;
	json["y"] = 150;
	json["w"] = 200;
	json["h"] = 0;

	
	EXPECT_THROW({
			try {
				rectangle.Deserialize(json);
			} catch (const std::invalid_argument& error) {
				EXPECT_STREQ("Rectangle::Deserialize Size should be positive", error.what());
				throw;
			}
		}, std::invalid_argument);

	json["x"] = 100;
	json["y"] = 150;
	json["w"] = 0;
	json["h"] = 0;

	EXPECT_THROW({
			try {
				rectangle.Deserialize(json);
			} catch (const std::invalid_argument& error) {
				EXPECT_STREQ("Rectangle::Deserialize Size should be positive", error.what());
				throw;
			}
		}, std::invalid_argument);
}

TEST(NAME_CLASS, TopLeftPoint) {
	//check the point is positive
	Json::Value json;

	json["x"] = -100;
	json["y"] = 150;
	json["w"] = 200;
	json["h"] = 300;

	Rectangle rectangle;
	EXPECT_THROW({
			try {
				rectangle.Deserialize(json);
			} catch (const std::invalid_argument& error) {
				EXPECT_STREQ("Rectangle::Deserialize top left point should be positive", error.what());
				throw;
			}
		}, std::invalid_argument);

	json["y"] = -150;
	EXPECT_THROW({
			try {
				rectangle.Deserialize(json);
			} catch (const std::invalid_argument& error) {
				EXPECT_STREQ("Rectangle::Deserialize top left point should be positive", error.what());
				throw;
			}
		}, std::invalid_argument);

	//zero top left is valid
	json["x"] = 0;
	json["y"] = 0;
	EXPECT_NO_THROW({rectangle.Deserialize(json); });
	EXPECT_TRUE(rectangle.GetTopLeft().x == 0);
	EXPECT_TRUE(rectangle.GetTopLeft().y == 0);
}

TEST(NAME_CLASS, Sizes) {
	Json::Value json;
	Rectangle rectangle;

	json["x"] = 100;
	json["y"] = 150;
	json["w"] = 200;
	json["h"] = 300;

	
	EXPECT_NO_THROW({rectangle.Deserialize(json);});
	EXPECT_TRUE(rectangle.GetSize().x == 200);
	EXPECT_TRUE(rectangle.GetSize().y == 300);

	json["w"] = -20;
	json["h"] = 300;
	EXPECT_THROW({
			try {
				rectangle.Deserialize(json);
			} catch (const std::invalid_argument& error) {
				EXPECT_STREQ("Rectangle::Deserialize Size should be positive", error.what());
				throw;
			}
		}, std::invalid_argument);

	json["h"] = -30;
	EXPECT_THROW({
			try {
				rectangle.Deserialize(json);
			} catch (const std::invalid_argument& error) {
				EXPECT_STREQ("Rectangle::Deserialize Size should be positive", error.what());
				throw;
			}
		}, std::invalid_argument);
}

TEST(NAME_CLASS, CopyRectangle) {
	Json::Value json;

	json["x"] = 100;
	json["y"] = 150;
	json["w"] = 200;
	json["h"] = 300;

	Rectangle rectangle;
	rectangle.Deserialize(json);

	Rectangle copyConstructor(rectangle);
	Rectangle asignment;
	asignment = rectangle;

	EXPECT_TRUE(rectangle.GetTopLeft().x == copyConstructor.GetTopLeft().x);
	EXPECT_TRUE(rectangle.GetTopLeft().y == copyConstructor.GetTopLeft().y);
	EXPECT_TRUE(rectangle.GetSize().x == copyConstructor.GetSize().x);
	EXPECT_TRUE(rectangle.GetSize().y == copyConstructor.GetSize().y);

	EXPECT_TRUE(rectangle.GetTopLeft().x == asignment.GetTopLeft().x);
	EXPECT_TRUE(rectangle.GetTopLeft().y == asignment.GetTopLeft().y);
	EXPECT_TRUE(rectangle.GetSize().x == asignment.GetSize().x);
	EXPECT_TRUE(rectangle.GetSize().y == asignment.GetSize().y);
}

TEST(NAME_CLASS, IncorrectParameters) {
	Json::Value json;
	Rectangle rectangle;

	json["x"] = 100;
	
	EXPECT_THROW({
			try {
				rectangle.Deserialize(json);
			} catch (const std::invalid_argument& error) {
				EXPECT_STREQ("Rectangle::Deserialize Lack of arguments", error.what());
				throw;
			}
		}, std::invalid_argument);

	json["y"] = 150;
	json["w"] = 200;

	EXPECT_THROW({
			try {
				rectangle.Deserialize(json);
			} catch (const std::invalid_argument& error) {
				EXPECT_STREQ("Rectangle::Deserialize Lack of arguments", error.what());
				throw;
			}
		}, std::invalid_argument);


	json["h"] = 200;
	//an extra non-needed argument
	json["another"] = 200;
	EXPECT_NO_THROW({ rectangle.Deserialize(json); }); //should just ignore it
}
