#include "precompiled.h"
#include "serialization/Reader.h"
#include "IntersectionCheckerOrchestration.h"
#include "shapes/AllShapes.h"
#include "analyser/Analyser.h"

namespace IntersectionChecker {

	IntersectionCheckerOrchestration::IntersectionCheckerOrchestration(std::shared_ptr<Config> config)
		: shapeFactory(),
		config(config)
	{
		//register the different shapes we could have to process
		//as a possible improve of the program, the config file could specify which shapes to admit
		shapeFactory.Register<Rectangle>("rects");
	}


	void IntersectionCheckerOrchestration::ReportIntersections(const std::string & filenameShapes) {
		int maxNumberShapes = config->GetMaxNumberElements();

		try {
			//given the factory, the file and
			//read and parse the json files, given the factory, and receive a vector of the shapes
			Reader reader;
			reader.ParseFileShapes(filenameShapes, shapeFactory, maxNumberShapes);
			std::vector<std::shared_ptr<Shape>> shapes = reader.GetReadShapes();

			if (shapes.size() == 0) {
				std::cout << "No shapes to analyze" << std::endl;

			} else {
				Analyser analyser;
				bool results = analyser.Analyze(shapes);

				std::stringstream buildResult;

				//write the shapes input read
				buildResult << "Input:\n";
				for (unsigned int i = 0; i < shapes.size(); ++i) {
					buildResult << (i + 1) << ": " << shapes[i]->ToString() << ".\n";
				}
				buildResult << "\n";

				if (results) {
					//write the rectangle intersections
					buildResult << "Intersections:\n";
					buildResult << analyser.GetResults();

				} else {
					buildResult << "No intersections.\n";
				}

				//show results
				std::cout << buildResult.str();
			}
		} catch (const std::exception& e) {
			std::cout << "ShapeIntersection::ReportIntersection = > Error: " << e.what() << std::endl;
		}
	}

}