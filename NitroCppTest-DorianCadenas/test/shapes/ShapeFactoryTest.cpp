#include <gtest/gtest.h>
#include "shapes/ShapeFactory.h"
#include "shapes/Rectangle.h"

#define NAME_CLASS ShapeFactoryTest

using namespace ShapeOverlay;


TEST(NAME_CLASS, RegisterAndCreate) {
	ShapeFactory factory;

	std::shared_ptr<Shape> result = factory.Create("test");
	ASSERT_TRUE(result == nullptr);

	factory.Register<Rectangle>("test");
	result = factory.Create("test");
	ASSERT_FALSE(result == nullptr);

	result = factory.Create("testAnother");
	ASSERT_TRUE(result == nullptr);
}

TEST(NAME_CLASS, FailRegister) {
	EXPECT_THROW({
			try {
				ShapeFactory factory;
				factory.Register<Rectangle>("test");
				factory.Register<Rectangle>("test"); //test register again with same id
			} catch (const std::exception& error) {
				// tests that it has the correct message
				EXPECT_STREQ("ShapeFactory::Register => Id/name already exists.", error.what());
				throw;
			}
		}, std::exception);
}