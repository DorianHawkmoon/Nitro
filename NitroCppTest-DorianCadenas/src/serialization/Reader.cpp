#include "precompiled.h"
#include "Reader.h"

#include <fstream>    

namespace ShapeOverlay {

	std::vector<std::shared_ptr<Shape>> Reader::ParseFileShapes(const std::string & filename, const ShapeFactory& factory, int maxNumberShapes) {
		std::vector<std::shared_ptr<Shape>> result;

		Json::Value shapes;
		std::ifstream configFile(filename, std::ifstream::binary);
		if (!configFile.good()) {
			throw std::exception("Reader::ParseFileShape Error with the file. Is it exists?");
		}
		
		//read and parse the file
		Json::CharReaderBuilder builder;
		std::string errors;
		bool parsed = Json::parseFromStream(builder, configFile, &shapes, &errors);
		if (!parsed) {
			std::string message("Reader::ParseFileShape Error parsing json file: " + errors);
			throw std::exception(message.c_str());
		}

		//iterate the differents shapes
		for (auto it = shapes.begin(); (it != shapes.end() && maxNumberShapes > 0); ++it) {
			Json::Value typeShape = it.key(); //get the name of the shape
			Json::Value listSpecificShape = (*it); //get the list of instances for the especified shape
			for (auto itShapes = listSpecificShape.begin(); (itShapes != listSpecificShape.end() && maxNumberShapes > 0); ++itShapes) {
				//create the object and deserialize it
				std::shared_ptr<Shape> shape = factory.Create(typeShape.asString());
				//control if we don't have this figure registered
				if (shape == nullptr) {
					throw std::exception("Reader::ParseFileShape Error, there is no registered shape");
				} else {
					shape->Deserialize(*itShapes);
					//store and continue
					result.push_back(shape);
					--maxNumberShapes;
				}
			}
		}

		//close the file
		configFile.close();

		//with c++11 returning a vector by value is efficiency enough to not worry about it (it moves, not copy)
		return result;
	}

}