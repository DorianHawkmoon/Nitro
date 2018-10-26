#include "precompiled.h"
#include "ShapeIntersection.h"
#include "shapes/AllShapes.h"
#include "analyser/Analyser.h"

namespace ShapeOverlay {

	ShapeIntersection::ShapeIntersection(Config config)
		: shapeFactory(),
		config(config)
	{
		//register the different shapes we could have to process
		//as a possible improve of the program, the config file could specify which shapes to admit
		shapeFactory.Register<Rectangle>("rects");
	}

	void ShapeIntersection::ReportIntersections(const std::string & filenameShapes) {
		Reader reader;
		int maxNumberShapes = config.GetMaxNumberElements();

		//read and parse the json files, given the factory, and receive a vector of the shapes
		//TODO get exceptions and treat it
		std::vector<std::shared_ptr<Shape>> shapes = reader.ParseFileShapes(filenameShapes,	shapeFactory, maxNumberShapes);

		if (shapes.size() == 0) {
			LOG("No shapes to analyze");
		} else {

			//pass the list of shapes to the analyzer TODO
			//create the analyzer and pass it the vector
			//Analyser analyser;
			//analyser.Analyse(shapes);


			//get the results from the analyzer and display TODO
			std::stringstream buildResult;

			buildResult << "Input:\n";
			//write the shapes readed
			for (int i = 0; i < shapes.size(); ++i) {
				buildResult << (i + 1) << ": " << shapes[i]->ToString() << ".\n";
			}
			buildResult << "\n";
			buildResult << "Intersections:\n";

			//TODO read the results and write the response

			LOG(buildResult.str().c_str());
		}
	}

}