#include <gtest/gtest.h>
#include "analyser/Intersection.h"
#include "shapes/Rectangle.h"

#define NAME_CLASS IntersectionTest

using namespace IntersectionChecker;

//constructor
TEST(NAME_CLASS, Constructor) {
	Intersection inter(2, 3, nullptr);
	Intersection inter2(2, 3, std::unique_ptr<Shape>(new Rectangle(10,15,20,30)));

	EXPECT_STREQ(inter.ToString().c_str(), "No intersection");
	EXPECT_STREQ(inter2.ToString().c_str(), "Between rectangle 2 and 3 at (10,15), w=20, h=30");
}

TEST(CLASS_NAME, GetIntersectionShape) {
	Intersection inter(2, 3, std::unique_ptr<Shape>(new Rectangle(10, 15, 20, 30)));
	std::unique_ptr<Shape> shape = inter.GetIntersectionShape();
	EXPECT_STREQ(shape->ToString().c_str(), "Rectangle at (10,15), w=20, h=30");

	Intersection interNull(2, 3, nullptr);
	std::unique_ptr<Shape> shapeNull = interNull.GetIntersectionShape();
	EXPECT_EQ(shapeNull, nullptr);
}

TEST(NAME_CLASS, AddIntersection) {
	Intersection inter(2, 3, std::unique_ptr<Shape>(new Rectangle(10, 15, 20, 30)));
	std::unique_ptr<Intersection> added = inter.AddShapeIntersection(5, std::unique_ptr<Shape>(new Rectangle(5, 3, 5, 5)));
	std::unique_ptr<Intersection> added2 = added->AddShapeIntersection(4, std::unique_ptr<Shape>(new Rectangle(5, 3, 3, 5)));

	EXPECT_STREQ(added->ToString().c_str(), "Between rectangle 2, 3 and 5 at (5,3), w=5, h=5");
	EXPECT_STREQ(added2->ToString().c_str(), "Between rectangle 2, 3, 5 and 4 at (5,3), w=3, h=5");

	EXPECT_NE(&inter, added.get());
	EXPECT_NE(added2.get(), added.get());
}

TEST(NAME_CLASS, Strings) {
	Intersection inter(2, 3, nullptr);
	Intersection inter2(2, 3, std::unique_ptr<Shape>(new Rectangle(10, 15, 20, 30)));

	EXPECT_STREQ(inter.ToString().c_str(), "No intersection");
	EXPECT_STREQ(inter2.ToString().c_str(), "Between rectangle 2 and 3 at (10,15), w=20, h=30");

	std::unique_ptr<Intersection> added = inter.AddShapeIntersection(5, std::unique_ptr<Shape>(new Rectangle(5, 3, 5, 5)));
	EXPECT_STREQ(added->ToString().c_str(), "Between rectangle 2, 3 and 5 at (5,3), w=5, h=5");

	std::unique_ptr<Intersection> added2 = added->AddShapeIntersection(11, std::unique_ptr<Shape>(new Rectangle(5, 3, 5, 5)));
	EXPECT_STREQ(added2->ToString().c_str(), "Between rectangle 2, 3, 5 and 11 at (5,3), w=5, h=5");
}