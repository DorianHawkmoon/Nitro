#include "precompiled.h"

#include "json/json.h"
#include <fstream>

using namespace ShapeOverlay;

/// <summary>
/// Main entry of the shape overlay program
/// Receive a json filename to parse the shapes
/// </summary>
/// <param name="argc">nubmer of arguments</param>
/// <param name="argv">arguments: needed the name/path of the json file</param>
/// <returns></returns>
int main(int argc, char *argv[]) {

	LOG("Hello world");

	//quick test of json inclusion
	Json::Value root;   // starts as "null"; will contain the root value after parsing

	//load file
	std::ifstream config_doc("data/test.json", std::ifstream::binary);
	config_doc >> root;


	// Get the value of the member of root named 'my-encoding', return 'UTF-32' if there is no
	// such member.
	std::string my_encoding = root.get("my-encoding", "UTF-32").asString();

	// Get the value of the member of root named 'my-plug-ins'; return a 'null' value if
	// there is no such member.
	const Json::Value my_plugins = root["my-plug-ins"];
	for (unsigned int index = 0; index < my_plugins.size(); ++index)  // Iterates over the sequence elements.
		LOG(my_plugins[index].asString().c_str());

	LOG( Utils::NumberToString(root["my-indent"].get("length", 3).asInt()).c_str() );
	std::stringstream boolalpha;
	boolalpha << std::boolalpha << root["my-indent"].get("use_space", true).asBool() << std::endl;
	LOG( boolalpha.str().c_str() );

	// ...
	// At application shutdown to make the new configuration document:
	// Since Json::Value has implicit constructor for all value types, it is not
	// necessary to explicitly construct the Json::Value object:
	root["encoding"] = "UTF-8";
	root["indent"]["length"] = 5;
	root["indent"]["use_space"] = false;

	// Make a new JSON document with the new configuration. Preserve original comments.
	std::cout << root << "\n";

	return 0;
}