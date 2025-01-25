//---------------------------------------------------------------------//
#ifndef ErrorLogger 
#define ErrorLogger 
//---------------------------------------------------------------------//
#include <iostream>
#include <stdexcept>
#include <bitset>
#include <fstream>
#include <filesystem>
#include <array>
#include <vector>
//---------------------------------------------------------------------//
enum class ErrorCodes {
	Light , 
	Crucial , 
	Priority , 
	Fatal 
};
//---------------------------------------------------------------------//
using Binary_8t = std::bitset<8>;
using MatrixString = std::vector<std::vector<std::string>>;
using MatrixBinary = std::vector<std::vector<Binary_8t>>;
//---------------------------------------------------------------------//
class ErrorManager : public std::exception {
private:
	std::string Error_Message{};
	Binary_8t Binary_data{};
	std::filesystem::path This_Path{ std::filesystem::current_path() };
	//---------------------------------------------------------------------//
private:
	std::ofstream& OpenLogFile();
	std::vector<std::bitset<8>> StringToBinary(const std::string& Input) const;
	void ErrorWriteToFileBinary();
	void ErrorReadTheFileBinary() const ;
	std::vector<std::string> BinaryToString(const MatrixBinary& data) const;
	std::string BinaryToString(const std::vector<Binary_8t>& data) const; 
	friend std::ostream& operator<< (std::ostream& ost ,std::bitset<8>& bset);
	//---------------------------------------------------------------------//
public:
	ErrorManager() {
		Error_Message = "";
		Binary_data = 0;
	};
	//---------------------------------------------------------------------//
	ErrorManager(const std::string& nError_Message, const ErrorCodes& Error_Type)
		:Error_Message(nError_Message) {
		//---------------------------------------------------------------------//
		switch (Error_Type) {
			//---------------------------------------------------------------------//
		case ErrorCodes::Light:
			Binary_data = Binary_8t{ "00000000" };
			break;
		case ErrorCodes::Crucial:
			Binary_data = Binary_8t{ "00000001" };
			break;
		case ErrorCodes::Priority:
			Binary_data = Binary_8t{ "00000010" };
			break;
		case ErrorCodes::Fatal:
			Binary_data = Binary_8t{ "00000011" };
			break;
		}
		ErrorWriteToFileBinary();
		ErrorReadTheFileBinary();
	};
	//---------------------------------------------------------------------//
	// 
	//---------------------------------------------------------------------//
	char const* what() const override {
		return Error_Message.c_str(); 
	}
	//---------------------------------------------------------------------//
};
//---------------------------------------------------------------------//
#endif
//---------------------------------------------------------------------//

