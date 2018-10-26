#include "precompiled.h"

#include "ShapeIntersection.h"
#include "utils/Config.h"

using namespace ShapeOverlay;

/// <summary>
/// Main entry of the shape overlay program
/// Receive a json filename to parse the shapes
/// </summary>
/// <param name="argc">nubmer of arguments</param>
/// <param name="argv">arguments: (optional) name/path of the json file</param>
/// <returns></returns>
int main(int argc, char *argv[]) {
	std::string filename;

	//check if givenf ile
	if (argc <= 0) {
		LOG("It is possible to give an input JSON file as an argument.\n");
		LOG("I will use data/example.json for demostration purposes.\n");
		filename = "data/example.json";

	} else {
		filename = argv[1];
	}

	//create the configuration for the program
	Config config;

	//create the program itself with the given configuration
	std::unique_ptr<ShapeIntersection> shapeIntersection(new ShapeIntersection(config));

	//execute the program given the json filename to process
	shapeIntersection->ReportIntersections(filename);

	return 0;
}