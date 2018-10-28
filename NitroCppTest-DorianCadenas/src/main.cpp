#include "precompiled.h"

#include "ShapeIntersection.h"
#include "utils/Config.h"

using namespace ShapeOverlay;

/// <summary>
/// Main entry of the shape overlay program
/// Receive a json filename to parse the shapes (optional)
/// </summary>
/// <param name="argc">nubmer of arguments</param>
/// <param name="argv">arguments: (optional) name/path of the json file</param>
/// <returns></returns>
int main(int argc, char *argv[]) {
	std::string filename;

	//check if givenf ile
	if (argc <= 1) { //first argument is the executable itself
		LOG("It is possible to give an input JSON file as an argument.\n");
		LOG("I will use data/example.json for demostration purposes.\n");
		filename = "data/example.json";

	} else {
		filename = std::string(argv[2]);
	}

	//create the configuration for the program
	std::shared_ptr<Config> config = std::make_shared<Config>();

	//create the program itself with the given configuration
	ShapeIntersection shapeIntersection = ShapeIntersection(config);

	//execute the program given the json filename to process
	shapeIntersection.ReportIntersections(filename);

	return 0;
}