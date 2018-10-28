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
		EXPECT_NO_THROW({rectangle.Deserialize(json);}); //should just ignore it
	
}

TEST(NAME_CLASS, Constructors) {
	Rectangle rectangle(100, 150, 200, 300);

	EXPECT_TRUE(rectangle.GetTopLeft().x == 100);
	EXPECT_TRUE(rectangle.GetTopLeft().y == 150);
	EXPECT_TRUE(rectangle.GetSize().x == 200);
	EXPECT_TRUE(rectangle.GetSize().y == 300);

	Maths::Vector2<int> topLeft{10,15};
	Maths::Vector2<int> size{20,30};
	Rectangle rectangle2(topLeft,size);

	EXPECT_TRUE(rectangle2.GetTopLeft().x == 10);
	EXPECT_TRUE(rectangle2.GetTopLeft().y == 15);
	EXPECT_TRUE(rectangle2.GetSize().x == 20);
	EXPECT_TRUE(rectangle2.GetSize().y == 30);

	Rectangle rectangle3;
	EXPECT_TRUE(rectangle3.GetTopLeft().x == 0);
	EXPECT_TRUE(rectangle3.GetTopLeft().y == 0);
	EXPECT_TRUE(rectangle3.GetSize().x == 0);
	EXPECT_TRUE(rectangle3.GetSize().y == 0);
}

TEST(NAME_CLASS, Strings) {
	Rectangle rectangle(100, 150, 200, 300);
	EXPECT_STRCASEEQ(rectangle.ToString().c_str(), "Rectangle at (100,150), w=200, h=300");
	EXPECT_STRCASEEQ(rectangle.NameShape().c_str(), "Rectangle");
}

TEST(NAME_CLASS, Collisions) {
	Rectangle rect1(100,100,250,80);
	Rectangle rect2(120,200,250,150);
	Rectangle rect3(140,160,250,100);

	std::unique_ptr<Shape> intersection1_2 = rect1.Intersection(rect2);
	std::unique_ptr<Shape> intersection1_3 = rect1.Intersection(rect3);
	std::unique_ptr<Shape> intersection2_3 = rect2.Intersection(rect3);

	//check intersection exists
	ASSERT_EQ(intersection1_2, nullptr);
	ASSERT_NE(intersection1_3, nullptr);
	ASSERT_NE(intersection2_3, nullptr);

	//check data intersection
	EXPECT_STREQ(intersection1_3->ToString().c_str(), "Rectangle at (140,160), w=210, h=20");
	EXPECT_STREQ(intersection2_3->ToString().c_str(), "Rectangle at (140,200), w=230, h=60");

	//edge case
	Rectangle rect4(350, 100, 10, 20);
	Rectangle rect5(100, 180, 10, 20);
	std::unique_ptr<Shape> intersection1_4 = rect1.Intersection(rect4);
	std::unique_ptr<Shape> intersection1_5 = rect1.Intersection(rect5);

	ASSERT_EQ(intersection1_4, nullptr);
	ASSERT_EQ(intersection1_5, nullptr);

	//fully included
	Rectangle rect6(110, 110, 20, 20);
	std::unique_ptr<Shape> intersection1_6 = rect1.Intersection(rect6);
	ASSERT_NE(intersection1_6, nullptr);
}

TEST(NAME_CLASS, Clone) {
	Rectangle rectangle(50, 10, 20, 30);
	std::unique_ptr<Shape> clone = rectangle.GetClone();

	EXPECT_NE(&rectangle, clone.get()); //compare pointers
	EXPECT_TRUE(clone != nullptr);
	EXPECT_STRCASEEQ(clone->ToString().c_str(), "Rectangle at (50,10), w=20, h=30");
	

}