//---------------------------------------------------------------------//
//The starting point of the algorithm 
#include "CommandProcess.cpp"
//---------------------------------------------------------------------//
//---------------------------------------------------------------------//
// custom file explorer - fsm 
//---------------------------------------------------------------------//
//---------------------------------------------------------------------//
#ifdef FSM_ENTRY 
	[[noreturn]] inline void FileExplorerInit() {
		static Directory EntryDir("C:\\");
		G_ExecutableDir = &EntryDir;
		//---------------------------------------------------------------------//	
		std::string command{ }; 
		// current problem is the fact that cd command cant take a full string input 
		while (std::getline(std::cin , command)) {
			std::array<std::string, 3U> comm_base = CommandSpecialSymbolProcess(command);
			//CommandeExecute(comm_base, EntryDir);
			CommandProcessFuncMap(comm_base);
		}
	}
//---------------------------------------------------------------------//
#endif // !FSM_ENTRY
//---------------------------------------------------------------------//
#ifndef FILESYSYTEM_HEAD   
	#include <filesystem>  
#endif 
//---------------------------------------------------------------------//
#ifndef IOSTREAM_HEAD
	#include <iostream>
#endif
//---------------------------------------------------------------------//
#ifndef EXCEPTIONS_HEAD
	#include <stdexcept>
#endif 
//---------------------------------------------------------------------//
#ifndef ErrorLogger 
	#include "ErrorLogger.h"
#endif // 
//---------------------------------------------------------------------//
int main(int argc, char** argv) {
	try { 
		FileExplorerInit();
		return 0;
	}
	//---------------------------------------------------------------------//
	catch (const ErrorManager& err) {
		std::cerr << "Caught a custom error - " << err.what() << std::endl;
	}
	//---------------------------------------------------------------------//
	catch (const std::filesystem::filesystem_error& e) {
		std::cerr << e.what() << ' ' << e.code() << ' ' << e.path1() << std::endl; 
	}
	//---------------------------------------------------------------------//
	catch (const  std::exception& exc) {
		std::cerr << "Exception caught in main() - " << exc.what() << std::endl;
	}
	//---------------------------------------------------------------------//
}
//---------------------------------------------------------------------//