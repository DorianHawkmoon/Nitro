#include "precompiled.h"

#include "IntersectionCheckerOrchestration.h"
#include "utils/Config.h"

using namespace IntersectionChecker;

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
		std::cout << "It is possible to give an input JSON file as an argument." << std::endl;
		std::cout << "I will use data/example.json for demostration purposes." << std::endl <<std::endl;
		filename = "data/example.json";

	} else {
		filename = std::string(argv[1]);
	}

	//create the configuration for the program
	std::shared_ptr<Config> config = std::make_shared<Config>();

	//create the program itself with the given configuration
	IntersectionCheckerOrchestration orchestration(config);

	//execute the program given the json filename to process
	orchestration.ReportIntersections(filename);

	return 0;
}