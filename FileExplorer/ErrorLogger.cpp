#include "ErrorLogger.h" 
//---------------------------------------------------------------------//

//---------------------------------------------------------------------//
std::ostream& operator<<(std::ostream& ost,std::bitset<8>& bset) {
	ost << bset.to_string();
	return ost;
}
//---------------------------------------------------------------------//
std::ostream& operator<< (std::ostream& ost,const std::vector<std::string>& other) {
	for (const auto& it : other) ost << it;
	return ost;
}
//---------------------------------------------------------------------//
std::ofstream& ErrorManager::OpenLogFile() {
	//---------------------------------------------------------------------//
	static std::ofstream LogFile(this->This_Path/"LogFile.dat", std::ios_base::binary | std::ios_base::app );
	if (!LogFile) {
		throw std::filesystem::filesystem_error("Failed to Create a logfile!", std::make_error_code(std::errc::address_not_available));
	}
	//---------------------------------------------------------------------//
	
	//---------------------------------------------------------------------//
	return LogFile;
	//---------------------------------------------------------------------//
}
//---------------------------------------------------------------------//
std::vector<std::bitset<8>> ErrorManager::StringToBinary(const std::string& Input) const {
	try {
		//---------------------------------------------------------------------//
		std::vector<std::bitset<8>> BinaryErrorMessage{};
		//---------------------------------------------------------------------//
		for (char binarychar : Input) {
			std::bitset<8> chbitset{ static_cast<unsigned char>(binarychar) }; 
			BinaryErrorMessage.push_back(chbitset);
		}
		//---------------------------------------------------------------------//
		if (BinaryErrorMessage.empty()) {
			throw std::invalid_argument("Empty binary data!");
		}
		return BinaryErrorMessage; 
	}
	catch (const std::invalid_argument& err) {
		std::cerr << "Caught an invalid argument - " << err.what() << std::endl; 
		throw;
	}	
}
void ErrorManager::ErrorWriteToFileBinary() {
	//---------------------------------------------------------------------//
	// opening the log file - lfile 
	std::ofstream& lfile = OpenLogFile();
	//---------------------------------------------------------------------//
	// writing to the logfile 
	lfile << Binary_data; 
	for (const auto& it : StringToBinary(Error_Message)) {
		lfile << it ;
	}
	//---------------------------------------------------------------------//
	lfile << "11111111"; // 11111111
	//---------------------------------------------------------------------//
}
//---------------------------------------------------------------------//
void ErrorManager::ErrorReadTheFileBinary() const {
	//---------------------------------------------------------------------//
	std::ifstream LogFile(this->This_Path / "LogFile.dat", std::ios_base::binary | std::ios_base::in);
	if (!LogFile) {
		throw std::filesystem::filesystem_error("Missing file,failed to open!", std::make_error_code(std::errc::address_not_available));
	}
	//---------------------------------------------------------------------//
	MatrixBinary fullbindat{}; 
	std::vector<Binary_8t> singlebinarydata; 
	Binary_8t bdat; 
	//---------------------------------------------------------------------//
	while (LogFile.good()) { 
		//---------------------------------------------------------------------//
		LogFile >> bdat;
		//---------------------------------------------------------------------//
		if (!(bdat.to_string() == "00000000" || bdat.to_string() == "00000001" || bdat.to_string() == "00000010" || bdat.to_string() == "00000011")) {
			//std::cout << bdat << std::endl;
			singlebinarydata.push_back(bdat);
			//---------------------------------------------------------------------//
			if (bdat.to_string() == "11111111") {
				//std::cerr << "Pass!" << std::endl; 
				fullbindat.push_back(singlebinarydata); 
				singlebinarydata.clear(); 
			}
			//---------------------------------------------------------------------//
		} 
	}
	std::cout << "The Log is - " << BinaryToString(fullbindat) << std::endl; 
	//---------------------------------------------------------------------//
}
//---------------------------------------------------------------------//
std::vector<std::string> ErrorManager::BinaryToString(const MatrixBinary& data) const {
	//---------------------------------------------------------------------//
	try {
		std::vector<std::string> ErrMesVect{}; 
		std::string ErrorMessage{ };
		//---------------------------------------------------------------------//
		for (auto row = 0; row < data.size(); row++) { 
			for (auto col = 0; col < data[row].size(); col++) {
				//std::cout << "ch - " << data[row][col] << std::endl; 
				char ch = static_cast<unsigned char>(data[row][col].to_ulong());
				ErrorMessage += ch;
			}
			ErrMesVect.push_back(ErrorMessage);
			ErrorMessage.clear(); 
		}
		//---------------------------------------------------------------------//
		if (ErrMesVect.empty()) {
			throw std::invalid_argument("Empty messages!");
		}
		//---------------------------------------------------------------------//
		return ErrMesVect; 
		//---------------------------------------------------------------------//
	}
	//---------------------------------------------------------------------//
	catch (const ErrorManager& errm) {
		std::cerr << errm.what() << std::endl; 
		throw; 
	}
	//---------------------------------------------------------------------//
	catch (const std::filesystem::filesystem_error& err) {
		std::cerr << err.what() << ' ' << err.code() << ' ' << "On the primary path - " << err.path1() << std::endl;
		throw; 
	}
}
//---------------------------------------------------------------------//
//---------------------------------------------------------------------//
std::string ErrorManager::BinaryToString(const std::vector<Binary_8t>& data) const {
	//---------------------------------------------------------------------//
	try {
		std::string ErrorMessage{ };
		//---------------------------------------------------------------------//
		for (auto i = 0; i < data.size(); i++) {
			//std::cout << "ch - " << data[i] << std::endl; 
			char ch = static_cast<unsigned char>(data[i].to_ulong());
			ErrorMessage += ch; 
		}
		if (ErrorMessage.empty()) {
			throw std::invalid_argument("Empty string!");
		}
		return ErrorMessage; 
	}
	catch (const ErrorManager& errm) {
		std::cerr << errm.what() << std::endl; 
		throw; 
	}
	catch (const std::filesystem::filesystem_error& err) {
		std::cerr << err.what() << ' ' << err.code() << ' ' << "On the primary path - " << err.path1() << std::endl;
		throw; 
	}
}
//---------------------------------------------------------------------//
