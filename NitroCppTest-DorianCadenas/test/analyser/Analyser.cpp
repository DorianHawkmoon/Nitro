#include "Analyser.h"
#include "shapes/AllShapes.h"

using namespace IntersectionChecker;

void AnalyserTest::SetUp() {
	analyser = std::make_unique<Analyser>();
}

void AnalyserTest::TearDown() {
	analyser.reset();
}

TEST_F(NAME_CLASS, NoShapes) {
	std::vector<std::shared_ptr<Shape>> shapes;
	EXPECT_FALSE(analyser->Analyze(shapes));

	shapes.push_back(std::shared_ptr<Shape>(new Rectangle(10,10,50,50)));
	EXPECT_FALSE(analyser->Analyze(shapes));

	//at least two
	shapes.push_back(std::shared_ptr<Shape>(new Rectangle(10, 10, 50, 50)));
	EXPECT_TRUE(analyser->Analyze(shapes));
}

TEST_F(NAME_CLASS, NoIntersection) {
	std::vector<std::shared_ptr<Shape>> shapes;
	shapes.push_back(std::shared_ptr<Shape>(new Rectangle(10, 10, 50, 50)));
	shapes.push_back(std::shared_ptr<Shape>(new Rectangle(100, 10, 50, 50)));
	EXPECT_FALSE(analyser->Analyze(shapes));

	EXPECT_STREQ(analyser->GetResults().c_str(),"No intersections.\n");
}

TEST_F(NAME_CLASS, BasicIntersection) {
	std::vector<std::shared_ptr<Shape>> shapes;
	shapes.push_back(std::shared_ptr<Shape>(new Rectangle(100, 100, 250, 80)));
	shapes.push_back(std::shared_ptr<Shape>(new Rectangle(140, 160, 250, 100)));
	EXPECT_TRUE(analyser->Analyze(shapes));

	EXPECT_STREQ(analyser->GetResults().c_str(), "Between rectangle 1 and 2 at (140,160), w=210, h=20.\n");
}

TEST_F(NAME_CLASS, LotOfIntersections) {
	std::vector<std::shared_ptr<Shape>> shapes;
	shapes.push_back(std::shared_ptr<Shape>(new Rectangle(100, 100, 250, 80)));
	shapes.push_back(std::shared_ptr<Shape>(new Rectangle(120, 200, 250, 150)));
	shapes.push_back(std::shared_ptr<Shape>(new Rectangle(140, 160, 250, 100)));
	shapes.push_back(std::shared_ptr<Shape>(new Rectangle(160, 140, 350, 190)));
	EXPECT_TRUE(analyser->Analyze(shapes));

	EXPECT_STREQ(analyser->GetResults().c_str(), "Between rectangle 1 and 3 at (140,160), w=210, h=20.\n\
Between rectangle 1 and 4 at (160,140), w=190, h=40.\n\
Between rectangle 2 and 3 at (140,200), w=230, h=60.\n\
Between rectangle 2 and 4 at (160,200), w=210, h=130.\n\
Between rectangle 3 and 4 at (160,160), w=230, h=100.\n\
Between rectangle 1, 3 and 4 at (160,160), w=190, h=20.\n\
Between rectangle 2, 3 and 4 at (160,200), w=210, h=60.\n");



	shapes.push_back(std::shared_ptr<Shape>(new Rectangle(500, 100, 250, 100)));
	shapes.push_back(std::shared_ptr<Shape>(new Rectangle(500, 100, 230, 100)));
	shapes.push_back(std::shared_ptr<Shape>(new Rectangle(500, 100, 200, 100)));
	shapes.push_back(std::shared_ptr<Shape>(new Rectangle(500, 100, 150, 100)));
	EXPECT_TRUE(analyser->Analyze(shapes));

EXPECT_STREQ(analyser->GetResults().c_str(), "Between rectangle 1 and 3 at (140,160), w=210, h=20.\n\
Between rectangle 1 and 4 at (160,140), w=190, h=40.\n\
Between rectangle 2 and 3 at (140,200), w=230, h=60.\n\
Between rectangle 2 and 4 at (160,200), w=210, h=130.\n\
Between rectangle 3 and 4 at (160,160), w=230, h=100.\n\
Between rectangle 4 and 5 at (500,140), w=10, h=60.\n\
Between rectangle 4 and 6 at (500,140), w=10, h=60.\n\
Between rectangle 4 and 7 at (500,140), w=10, h=60.\n\
Between rectangle 4 and 8 at (500,140), w=10, h=60.\n\
Between rectangle 5 and 6 at (500,100), w=230, h=100.\n\
Between rectangle 5 and 7 at (500,100), w=200, h=100.\n\
Between rectangle 5 and 8 at (500,100), w=150, h=100.\n\
Between rectangle 6 and 7 at (500,100), w=200, h=100.\n\
Between rectangle 6 and 8 at (500,100), w=150, h=100.\n\
Between rectangle 7 and 8 at (500,100), w=150, h=100.\n\
Between rectangle 1, 3 and 4 at (160,160), w=190, h=20.\n\
Between rectangle 2, 3 and 4 at (160,200), w=210, h=60.\n\
Between rectangle 4, 5 and 6 at (500,140), w=10, h=60.\n\
Between rectangle 4, 5 and 7 at (500,140), w=10, h=60.\n\
Between rectangle 4, 5 and 8 at (500,140), w=10, h=60.\n\
Between rectangle 4, 6 and 7 at (500,140), w=10, h=60.\n\
Between rectangle 4, 6 and 8 at (500,140), w=10, h=60.\n\
Between rectangle 4, 7 and 8 at (500,140), w=10, h=60.\n\
Between rectangle 5, 6 and 7 at (500,100), w=200, h=100.\n\
Between rectangle 5, 6 and 8 at (500,100), w=150, h=100.\n\
Between rectangle 5, 7 and 8 at (500,100), w=150, h=100.\n\
Between rectangle 6, 7 and 8 at (500,100), w=150, h=100.\n\
Between rectangle 4, 5, 6 and 7 at (500,140), w=10, h=60.\n\
Between rectangle 4, 5, 6 and 8 at (500,140), w=10, h=60.\n\
Between rectangle 4, 5, 7 and 8 at (500,140), w=10, h=60.\n\
Between rectangle 4, 6, 7 and 8 at (500,140), w=10, h=60.\n\
Between rectangle 5, 6, 7 and 8 at (500,100), w=150, h=100.\n\
Between rectangle 4, 5, 6, 7 and 8 at (500,140), w=10, h=60.\n");
}