//---------------------------------------------------------------------//
#include <vector>
#include <array>
#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <filesystem>
//---------------------------------------------------------------------//
const std::array<std::string, 2U> FileExtensions = { ".txt" , ".dat" };
const std::array <std::string, 3> JSONCLassData = { "Name" , "Type" , "Extention" };
//---------------------------------------------------------------------//
//---------------------------------------------------------------------//
// add's an information about the contents of the classes in a Json format
inline void JsonInfoParser(const std::filesystem::path& npath ) {
	using boost::property_tree::ptree;

	boost::property_tree::ptree root;
	//---------------------------------------------------------------------//
	root.put("Version", "1.0");
	root.put("Type", "FileExplorer");
	root.put("Project Name", "C_Project");

	ptree ClassInstanceTree;
	//---------------------------------------------------------------------//
	for (const auto& it : JSONCLassData) {
		//---------------------------------------------------------------------//
		ptree ClassInstanceNode;
		std::string JsonValueUser{};
		std::cout << "Enter the " << it << " ! " << std::endl;
		std::cin >> JsonValueUser;
		ClassInstanceNode.put("", JsonValueUser);

		//---------------------------------------------------------------------//
		ClassInstanceTree.push_back(std::make_pair(it, ClassInstanceNode));
		JsonValueUser.clear();
	}
	//---------------------------------------------------------------------//
	
	root.add_child("Class Description", ClassInstanceTree);
	boost::property_tree::write_json( npath.generic_string(), root);
	std::cout << "Properties have been updated!" << std::endl;
	//---------------------------------------------------------------------//a
}
//---------------------------------------------------------------------//

//---------------------------------------------------------------------//
// add's an information about the contents of the classes in a Json format
inline void JsonInfoParser() {
	using boost::property_tree::ptree;

	boost::property_tree::ptree root;
	//---------------------------------------------------------------------//
	root.put("Version", "1.0");
	root.put("Type", "FileExplorer");
	root.put("Project Name", "C_Project");

	ptree ClassInstanceTree;
	//---------------------------------------------------------------------//
	for (const auto& it : JSONCLassData) {
		//---------------------------------------------------------------------//
		ptree ClassInstanceNode;
		std::string JsonValueUser{};
		std::cout << "Enter the " << it << " ! " << std::endl;
		std::cin >> JsonValueUser;
		ClassInstanceNode.put("", JsonValueUser);

		//---------------------------------------------------------------------//
		ClassInstanceTree.push_back(std::make_pair(it, ClassInstanceNode));
		JsonValueUser.clear();
	}
	//---------------------------------------------------------------------//
	
	root.add_child("Class Description", ClassInstanceTree);
	boost::property_tree::write_json("prop.json", root);
	std::cout << "Properties have been updated!" << std::endl;
	//---------------------------------------------------------------------//a
}
//---------------------------------------------------------------------//
inline void JsonFileReader(const std::filesystem::path& filename) {
	//std::string filename = FS::current_path().generic_string() + "prop.json"; 
	// Create a property tree
	boost::property_tree::ptree pt;
	//---------------------------------------------------------------------//
	// Read JSON file into the property tree
	try {
		boost::property_tree::read_json(filename.generic_string(), pt);
		//---------------------------------------------------------------------//
		// Access values in the JSON
		std::string Version = pt.get<std::string>("Version", "Version not found in a JSON!");
		std::string Type = pt.get<std::string>("Type", "Type not found in a JSON!");
		std::string ProjectName = pt.get("Project Name", "Project Name not found in a JSON!"); // Default to empty if not found
		//---------------------------------------------------------------------//
		std::cout << "Name: " << Version << std::endl;
		std::cout << "Type: " << Type << std::endl;
		std::cout << "Extension: " << ProjectName << std::endl;
		//---------------------------------------------------------------------//
		// Access nested arrays
		for (const auto& item : pt.get_child("Class Description")) {
			std::cout << item.first << ": " << item.second.get_value<std::string>() << std::endl;
		}
	}
	//---------------------------------------------------------------------//
	catch (const boost::property_tree::json_parser_error& e) {
		std::cerr << "Error parsing JSON: " << e.what() << std::endl;
	}
	//---------------------------------------------------------------------//
	catch (const boost::property_tree::ptree_bad_path& e) {
		std::cerr << "Error accessing JSON path: " << e.what() << std::endl;
	}
	//---------------------------------------------------------------------//
}
//---------------------------------------------------------------------//

//---------------------------------------------------------------------//
inline void JsonFileReader(const std::string& filename) {
	//std::string filename = FS::current_path().generic_string() + "prop.json"; 
	// Create a property tree
	boost::property_tree::ptree pt;
	//---------------------------------------------------------------------//
	// Read JSON file into the property tree
	try {
		boost::property_tree::read_json(filename, pt);
		//---------------------------------------------------------------------//
		// Access values in the JSON
		std::string Version = pt.get<std::string>("Version", "Version not found in a JSON!");
		std::string Type = pt.get<std::string>("Type", "Type not found in a JSON!");
		std::string ProjectName = pt.get("Project Name", "Project Name not found in a JSON!"); // Default to empty if not found
		//---------------------------------------------------------------------//
		std::cout << "Name: " << Version << std::endl;
		std::cout << "Type: " << Type << std::endl;
		std::cout << "Extension: " << ProjectName << std::endl;
		//---------------------------------------------------------------------//
		// Access nested arrays
		for (const auto& item : pt.get_child("Class Description")) {
			std::cout << item.first << ": " << item.second.get_value<std::string>() << std::endl;
		}
	}
	//---------------------------------------------------------------------//
	catch (const boost::property_tree::json_parser_error& e) {
		std::cerr << "Error parsing JSON: " << e.what() << std::endl;
	}
	//---------------------------------------------------------------------//
	catch (const boost::property_tree::ptree_bad_path& e) {
		std::cerr << "Error accessing JSON path: " << e.what() << std::endl;
	}
	//---------------------------------------------------------------------//
}
//---------------------------------------------------------------------//
