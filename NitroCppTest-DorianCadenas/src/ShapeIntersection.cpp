#include "precompiled.h"
#include "ShapeIntersection.h"
#include "shapes/Rectangle.h"

namespace ShapeOverlay {

	ShapeIntersection::ShapeIntersection()
		: shapeFactory()
	{
		//register the different shapes we could have
		shapeFactory.Register<Rectangle>("rects");
	}

	void ShapeIntersection::ReportIntersections(const std::string & filenameShapes) {
		Reader reader;
		int maxNumberShapes = 10; //TODO change to config class
		//pass the shapes and the factory and get a list of shapes created
		//reader.ParseFileShapes(filenameShapes, shapeFactory, maxNumberShapes);
		reader.ParseFileShapes("data/test/nonexists.json",	shapeFactory, 2);

		//pass the list of shapes to the analyzer TODO
		//get the results from the analyzer and display TODO
	}

}