#include "ReaderTest.h"
#include "serialization/Reader.h"
#include "shapes/Rectangle.h"

using namespace ShapeOverlay;

void ReaderTest::SetUp() {
	factory = std::make_unique<ShapeFactory>();
	factory->Register<Rectangle>("rects");
}

void ReaderTest::TearDown() {
	factory.reset();
}



TEST_F(NAME_CLASS, NumberShapes) {
	//test if obey the limit of shapes
	Reader reader;
	std::vector<std::shared_ptr<Shape>> result = reader.ParseFileShapes("data/test/limits.json", 
																	*factory.get(), 2);
	EXPECT_EQ(result.size(), 2);
	

	result.clear();
	result = reader.ParseFileShapes("data/test/limits.json",
		*factory.get(), 5);
	EXPECT_EQ(result.size(), 5);


	result.clear();
	result = reader.ParseFileShapes("data/test/limits.json",
		*factory.get(), 10);
	EXPECT_EQ(result.size(), 7); 
}

TEST_F(NAME_CLASS, ShapesCreated) {
	//check if creates correctly the shapes
	Reader reader;
	std::vector<std::shared_ptr<Shape>> result = reader.ParseFileShapes("data/test/limits.json",
		*factory.get(), 2);
	ASSERT_EQ(result.size(), 2);

	//TODO improve test
	EXPECT_TRUE(result[0] != nullptr);
	EXPECT_TRUE(result[1] != nullptr);
}

TEST_F(NAME_CLASS, Exceptions) {
	//test if throw the exceptions as it should be
	Reader reader;

	//error file does not exists
	EXPECT_THROW({
			try {
				reader.ParseFileShapes("data/test/nonexists.json", *factory.get(), 2);
			} catch (const std::exception& error) {
				// tests that it has the correct message
				EXPECT_STREQ("Reader::ParseFileShape Error with the file. Is it exists?", error.what());
				throw;
			}
		}, std::exception);
		
	
	//error shape not registered
	EXPECT_THROW({
			try {
				std::vector<std::shared_ptr<Shape>> result = reader.ParseFileShapes("data/test/strangeshape.json",
																					*factory.get(), 2);
			} catch (const std::exception& error) {
				// tests that it has the correct message
				EXPECT_STREQ("Reader::ParseFileShape Error, there is no registered shape", error.what());
				throw;
			}
		}, std::exception);

	//error not validated
	EXPECT_THROW({
			try {
				std::vector<std::shared_ptr<Shape>> result = reader.ParseFileShapes("data/test/malformed.json",
																				*factory.get(), 2);
			} catch (const std::exception& error) {
				EXPECT_TRUE(std::string(error.what()).find("Error parsing json file") != std::string::npos);
				throw;
			}
		}, std::exception);


	//error shape with not enough parameters
	EXPECT_THROW({
			try {
				std::vector<std::shared_ptr<Shape>> result = reader.ParseFileShapes("data/test/notenoughparameters.json",
																					*factory.get(), 2);
			} catch (const std::exception& error) {
				EXPECT_TRUE(std::string(error.what()).find("Deserialize Lack of arguments") != std::string::npos);
				throw;
			}
		}, std::exception);
		

	//error shape with wrong parameters
	EXPECT_THROW({
				std::vector<std::shared_ptr<Shape>> result = reader.ParseFileShapes("data/test/wrongparameters.json",
																					*factory.get(), 2);
		}, std::exception);

}

