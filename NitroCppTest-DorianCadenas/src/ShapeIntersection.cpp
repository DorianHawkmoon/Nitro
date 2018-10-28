#include "precompiled.h"
#include "ShapeIntersection.h"
#include "shapes/AllShapes.h"
#include "analyser/Analyser.h"

namespace ShapeOverlay {

	ShapeIntersection::ShapeIntersection(std::shared_ptr<Config> config)
		: shapeFactory(),
		config(config)
	{
		//register the different shapes we could have to process
		//as a possible improve of the program, the config file could specify which shapes to admit
		shapeFactory.Register<Rectangle>("rects");
	}


	void ShapeIntersection::ReportIntersections(const std::string & filenameShapes) {
		int maxNumberShapes = config->GetMaxNumberElements();

		try {
			//given the factory, the file and
			//read and parse the json files, given the factory, and receive a vector of the shapes
			Reader reader;
			reader.ParseFileShapes(filenameShapes, shapeFactory, maxNumberShapes);
			std::vector<std::shared_ptr<Shape>> shapes = reader.GetReadShapes();

			if (shapes.size() == 0) {
				LOG("No shapes to analyze");
			} else {
				//pass the list of shapes to the analyzer TODO
				//create the analyzer and pass it the vector
				Analyser analyser;
				bool results = analyser.Analyze(shapes);


				//get the results from the analyzer and display TODO
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
					//TODO read the results and write the response
					buildResult << analyser.GetResults();

				} else {
					buildResult << "No intersections.\n";
				}
				//print results TODO see LOG or just iostream(results!!)
				LOG(buildResult.str().c_str());
			}
		} catch (const std::exception& e) {

			//TODO treat the exceptions
		}
	}

}