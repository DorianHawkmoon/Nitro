#include "precompiled.h"
#include "Reader.h"

#include <fstream>    

namespace ShapeOverlay {

	bool Reader::ParseFileShapes(const std::string & filename) {
		//check the path is correct
			//check syntax
			//return the shape in the given argument

		bool result = true;
		std::string errors;

		Json::Value config;
		std::ifstream configFile(filename, std::ifstream::binary);
		result &= configFile.good();

		if (!result) {
			LOG("Error with the file. Is it exists?");
		}
		
		Json::CharReaderBuilder builder;
		if (!Json::parseFromStream(builder, configFile, &config, &errors)) {
			LOG("Error parsing json file: ", errors, "\n");
		}

		//TODO iterate json and create the objects with the factory
		//return the objects (in a given parameter)


		configFile.close();

		return result;
	}

}