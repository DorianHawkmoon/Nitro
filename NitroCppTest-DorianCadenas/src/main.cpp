#include "precompiled.h"

#include "json/json.h"
#include <fstream>
#include "ShapeIntersection.h"

using namespace ShapeOverlay;

/// <summary>
/// Main entry of the shape overlay program
/// Receive a json filename to parse the shapes
/// </summary>
/// <param name="argc">nubmer of arguments</param>
/// <param name="argv">arguments: needed the name/path of the json file</param>
/// <returns></returns>
int main(int argc, char *argv[]) {
	//TODO check i have at least one input (the filename)
	//TODO improve, create a config class with details like maximum number of shape for shape intersection
	std::unique_ptr<ShapeIntersection> shapeIntersection(new ShapeIntersection()); //Todo pass the filename
	shapeIntersection->ReportIntersections("Hola");
	//TODO improve string errors report

	return 0;
}