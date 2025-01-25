//---------------------------------------------------------------------//
#include "FileExplorer.h"
//custom header file signatures 
#define FSM_ENTRY
#define FILESYSYTEM_HEAD
#define IOSTREAM_HEAD
#define EXCEPTIONS_HEAD // FOR stdexcept
#define ERROR_MANAGER // FOR error manager 
//---------------------------------------------------------------------//
//@Description - A pointer to the current executable directory 
static Directory* G_ExecutableDir; 
//---------------------------------------------------------------------//
const std::map<std::string, std::function<void(std::filesystem::path&)>, std::less<>> FN_map{
	{ "addfile" , [&](FS::path& npath) { G_ExecutableDir->DirectoryAddFile(npath); }} ,
	{ "adddir" ,  [&](FS::path& npath) { G_ExecutableDir->AddDirectory(npath); }} ,
	{ "remfile" , [&](FS::path& npath) { G_ExecutableDir->DirectoryRemoveFile(npath); }},
	{ "remdir" ,  [&](FS::path& npath) { G_ExecutableDir->RemoveDirectory(npath); }} ,
	{ "ls" ,      [&](FS::path& npath) { G_ExecutableDir->ShowDirectoryContents(); }} ,
	{ "cd" ,      [&](FS::path& npath) { G_ExecutableDir->MoveToTheDirectory(npath); }} ,
	{ "jsonip" ,  [&](FS::path& npath) { JsonInfoParser(npath); }} ,
	{ "jsonr" ,   [&](FS::path& npath) { JsonFileReader(npath); }}
};

//---------------------------------------------------------------------//
inline std::vector<std::filesystem::path> ReadTheRestFile() {
	//---------------------------------------------------------------------//
	std::vector<std::filesystem::path> RestrictedPaths{};
	//---------------------------------------------------------------------//
	std::ifstream file{ "C:\\Users\\Arman\\source\\repos\\C_Project\\RestrictedAccessPaths.txt" ,std::ios_base::in };
	std::istream_iterator<std::string> beg{ file };
	std::istream_iterator<std::string> end; 
 	//---------------------------------------------------------------------//
	std::filesystem::path RestPath{ };
	//---------------------------------------------------------------------//
	while (beg != end) {
		RestPath = *beg; 
		RestrictedPaths.push_back(RestPath);
		++beg; 
	}
	//---------------------------------------------------------------------//
	return RestrictedPaths;
}
//---------------------------------------------------------------------//
inline std::array<std::string, 3U> CommandSpecialSymbolProcess(const std::string& target) {
	try {
		//---------------------------------------------------------------------//
		std::array<std::string ,3U> ProceccedCommand{ };
		//---------------------------------------------------------------------//
		std::stringstream ss{ target };
		for (int i = 0; i < 3; i++) {
			ss >> ProceccedCommand[i]; 
		}
		//---------------------------------------------------------------------//
		//---------------------------------------------------------------------//
		if (ProceccedCommand.empty()) {
			std::cout << "Empty array!" << std::endl;
		}
		//---------------------------------------------------------------------//
		return ProceccedCommand;
		//---------------------------------------------------------------------//
	}
	//---------------------------------------------------------------------//
	catch (const std::exception& ex) {
		std::cerr << ex.what() << std::endl; 
		throw;
	}
	//---------------------------------------------------------------------//
}
//---------------------------------------------------------------------//
//Deprecated
inline void CommandExecute(const std::array<std::string, 3U>& other, Directory& Pdir) {
	try {  
		//---------------------------------------------------------------------//
		std::vector<std::filesystem::path> Paths{ ReadTheRestFile() };
		//---------------------------------------------------------------------//
		if (other[0] != "fsm") {
			std::cerr << "Wrong shell command <" << other[0] << "> is not a entry command , fsm expected!" << std::endl;
			return;
		}
		//---------------------------------------------------------------------//
		for (const auto& it : Paths) {
			if (other[2] == it) {
				return;
			}
		}
		//---------------------------------------------------------------------//
		if (other[1] == "addfile") {
			Pdir.DirectoryAddFile(other[2]);
		}
		//---------------------------------------------------------------------//
		if (other[1] == "adddir") {
			Pdir.AddDirectory(other[2]);
		}
		//---------------------------------------------------------------------//
		if (other[1] == "remfile") {
			Pdir.DirectoryRemoveFile(other[2]);
		}
		//---------------------------------------------------------------------//
		if (other[1] == "remdir") {
		    Pdir.RemoveDirectory(other[2]);
		}
		//---------------------------------------------------------------------//
		if (other[1] == "ls") {
			Pdir.ShowDirectoryContents(); 
		} 
		//---------------------------------------------------------------------//
		if (other[1] == "cd") {
			Pdir.MoveToTheDirectory(other[2]);
		}
		//---------------------------------------------------------------------//
		//for JSON info parser 
		if (other[1] == "jsonip") {
			JsonInfoParser(); 
		}
		//for the JSON reader 
		if (other[1] == "jsonr") {
			JsonFileReader(_STR_CAST_U_("C:\\Users\\Arman\\source\\repos\\C_Project\\prop.json"));
		}
		else if (!(other[1] == "addfile" || other[1] == "adddir"
				|| other[1] == "remfile" || other[1] == "remdir"
				|| other[1] == "ls"		 || other[1] == "cd"
				|| other[1] == "jsonip"  || other[1] == "jsonr")) {
			std::cout << "Wrong Shell command!" << std::endl;
			return;
		}
	 
	}
	catch (const std::invalid_argument& inv) {
		std::cerr << inv.what() << std::endl; 
		throw; 
	}
	catch (const std::filesystem::filesystem_error& ferr) {
		std::cerr << ferr.code() << ' ' << ferr.what() << ' ' << ferr.path1() << std::endl;
		throw; 
	}
}
//---------------------------------------------------------------------//

//---------------------------------------------------------------------//
inline void CommandProcessFuncMap( const std::array<std::string , 3U>& MsgArr ) {
	try {
		if (MsgArr[0] != "fsm") {
			std::cout << "The action command is not fsm!" << std::endl; 
			return;
		}
		//---------------------------------------------------------------------//
		
		//---------------------------------------------------------------------//
		auto it = FN_map.find(MsgArr[1]); // Find the command in the map
		//---------------------------------------------------------------------//
		if (it != FN_map.end()) {
			std::filesystem::path commandPath = MsgArr[2]; // Argument as a path
			it->second(commandPath); // Call the associated function
		}
		else {
			std::cerr << "Command not found!" << std::endl; 
		}
		//---------------------------------------------------------------------//
	}
	catch (const std::invalid_argument& inv) {
		std::cerr << inv.what() << std::endl;
		throw;
	}
	catch (const std::filesystem::filesystem_error& ferr) {
		std::cerr << ferr.code() << ' ' << ferr.what() << ' ' << ferr.path1() << std::endl;
		throw;
	}
}
//---------------------------------------------------------------------//