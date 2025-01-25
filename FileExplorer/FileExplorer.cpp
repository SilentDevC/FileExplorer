//---------------------------------------------------------------------//
#include "FileExplorer.h"
//#define DEBUG
//---------------------------------------------------------------------//

//---------------------------------------------------------------------//
inline Directory::Directory(const Directory& other) noexcept {
	this->_dir_entry = other._dir_entry;
	this->_dir_path = other._dir_path;
	this->_dir_iter = other._dir_iter;
}
//---------------------------------------------------------------------//
inline Directory::Directory(Directory&& other) noexcept {
	this->_dir_entry = std::move(other._dir_entry);
	this->_dir_path = std::move(other._dir_path);
	this->_dir_iter = std::move(other._dir_iter);
}
//---------------------------------------------------------------------//
inline bool Directory::operator==(const Directory& other) const {
	return _dir_entry == other._dir_entry && _dir_path == other._dir_path && _dir_iter == other._dir_iter;
}
//---------------------------------------------------------------------//
inline bool Directory::operator!=(const Directory& other) const {
	return !(_dir_entry == other._dir_entry && _dir_path == other._dir_path && _dir_iter == other._dir_iter);
}
//---------------------------------------------------------------------//
inline FS::path& Directory::operator/=(const Directory& other) const { 
	FS::path ResPath = *this->_dir_path / *other._dir_path; 
	return std::ref(ResPath);
}
//---------------------------------------------------------------------//
//prefix operator ++
inline Directory& Directory::operator++() noexcept {
	++this->_dir_iter;
	return *this;
}
//---------------------------------------------------------------------//
// postfix operator++ 
inline Directory Directory::operator++(int) noexcept {
	Directory temp = *this;
	++this->_dir_iter;
	return temp;
}
//---------------------------------------------------------------------//
inline Directory& Directory::at(int& pos) {
	//---------------------------------------------------------------------//
	while (pos--) {
		//---------------------------------------------------------------------//
		if (this->_dir_iter._At_end()) {
			break;
		}
		//---------------------------------------------------------------------//
		++this->_dir_iter;
	}
	//---------------------------------------------------------------------//
	return *this;
}
//---------------------------------------------------------------------//
//---------------------------------------------------------------------//
void Directory::DirectoryAddFile() const {
	try {
		//---------------------------------------------------------------------//
		FS::path filename = *this->_dir_path; 
		FS::path filenamestart; 
		do {
			std::cout << "Enter the name of the file to add - " ;
			std::cin >> filenamestart; 
		} while (filenamestart.empty());
		//---------------------------------------------------------------------//
		filename /= filenamestart; 
		//---------------------------------------------------------------------//
#ifdef DEBUG
		std::cout << "Full path is - " << filename << std::endl;
		std::cout << "Starting path is - " << *this->_dir_path << std::endl;
#endif // DEBUG
		//---------------------------------------------------------------------//
		if (!FS::exists(*this->_dir_path)) {
			throw FS::filesystem_error("Failed operation - Missing File", *this->_dir_path, std::make_error_code(std::errc::no_such_file_or_directory));
		}
		//---------------------------------------------------------------------//
		std::ofstream file(filename, std::ios_base::out);
		//---------------------------------------------------------------------//
		if (!file) {
			throw FS::filesystem_error("Failed Operation - File_Creationy", filename, std::make_error_code(std::errc::no_such_file_or_directory));
		}
		else {
			std::cout << "Successful creation of the file !" << std::endl;
		}
		//---------------------------------------------------------------------//
		std::error_code err;
		FS::permissions(filename , FS::perms::all, err); 
		
		//---------------------------------------------------------------------//
		if (err) {
			std::cerr << "Failure dureing permission setting - " << err.message() << "!" << std::endl;
		}
		else {
			std::cerr << "Permissions accepted!" << std::endl;
		}
		//---------------------------------------------------------------------//
		file.close();
	}
	catch (const FS::filesystem_error& err) {
		std::cerr << "Directory failure - " << err.what() << " "
			<< err.code() << " "
			<< err.path1() << std::endl;
		// path1 - primary manipulation path 
		throw;
	}
}
//---------------------------------------------------------------------//
void Directory::DirectoryAddFile(const FS::path& filenamestart) const {
	try {
		//---------------------------------------------------------------------//
		FS::path filename = *this->_dir_path; 
		/*do {
			std::cout << "Enter the name of the file to add - " ;
			std::cin >> filenamestart; 
		} while (filenamestart.empty());*/
		//---------------------------------------------------------------------//
		filename /= filenamestart; 
		//---------------------------------------------------------------------//
#ifdef DEBUG
		std::cout << "Full path is - " << filename << std::endl;
		std::cout << "Starting path is - " << *this->_dir_path << std::endl;
#endif // DEBUG
		//---------------------------------------------------------------------//
		if (!FS::exists(*this->_dir_path)) {
			throw FS::filesystem_error("Failed operation - Missing File", *this->_dir_path, std::make_error_code(std::errc::no_such_file_or_directory));
		}
		//---------------------------------------------------------------------//
		std::ofstream file(filename, std::ios_base::out);
		//---------------------------------------------------------------------//
		if (!file) {
			throw FS::filesystem_error("Failed Operation - File_Creationy", filename, std::make_error_code(std::errc::no_such_file_or_directory));
		}
		else {
			std::cout << "Successful creation of the file !" << std::endl;
		}
		//---------------------------------------------------------------------//
		std::error_code err;
		FS::permissions(filename , FS::perms::all, err); 
		
		//---------------------------------------------------------------------//
		if (err) {
			std::cerr << "Failure dureing permission setting - " << err.message() << "!" << std::endl;
		}
		else {
			std::cerr << "Permissions accepted!" << std::endl;
		}
		//---------------------------------------------------------------------//
		file.close();
	}
	catch (const FS::filesystem_error& err) {
		std::cerr << "Directory failure - " << err.what() << " "
			<< err.code() << " "
			<< err.path1() << std::endl;
		// path1 - primary manipulation path 
		throw;
	}
}
//---------------------------------------------------------------------//
inline void Directory::DirectoryRemoveFile() const {
	try {
		//---------------------------------------------------------------------//
		FS::path removal_path; 
		std::cout << "Enter a path to delete - "; 
		std::cin >> removal_path;
		//---------------------------------------------------------------------//
		if (!FS::exists(*this->_dir_path/removal_path)) {
			throw FS::filesystem_error("Remove operation failed!", *this->_dir_path / removal_path, std::make_error_code(std::errc::bad_file_descriptor));
		}
		//---------------------------------------------------------------------//
		if (FS::remove(*this->_dir_path / removal_path)) {
			std::cout << "Successful removal!" << std::endl; 
		}
		//---------------------------------------------------------------------//
	}
	//---------------------------------------------------------------------//
	catch (FS::filesystem_error& err) {
		std::cerr << "Filesystem failure ! - " << err.what()
			<< err.code()
			<< err.path1() << std::endl;
		throw;
	}
}
//---------------------------------------------------------------------//
void Directory::DirectoryRemoveFile(const FS::path& removal_path) const {
	try {
		//---------------------------------------------------------------------//
		/*std::cout << "Enter a path to delete - "; 
		std::cin >> removal_path;*/
		//---------------------------------------------------------------------//
		if (!FS::exists(*this->_dir_path/removal_path)) {
			throw FS::filesystem_error("Remove operation failed!", *this->_dir_path / removal_path, std::make_error_code(std::errc::bad_file_descriptor));
		}
		//---------------------------------------------------------------------//
		if (FS::remove(*this->_dir_path / removal_path)) {
			std::cout << "Successful removal!" << std::endl; 
		}
		//---------------------------------------------------------------------//
	}
	//---------------------------------------------------------------------//
	catch (FS::filesystem_error& err) {
		std::cerr << "Filesystem failure ! - " << err.what()
			<< err.code()
			<< err.path1() << std::endl;
		throw;
	}
}
//---------------------------------------------------------------------//
void Directory::AddDirectory(const FS::path& NewDirName ) const {
	try {
		//---------------------------------------------------------------------//
		if (!FS::exists(*this->_dir_path) && FS::is_directory(*this->_dir_path)) {
			throw FS::filesystem_error("Addition Operation failed!", *this->_dir_path, std::make_error_code(std::errc::bad_file_descriptor));
		}
		//---------------------------------------------------------------------//
		if (FS::create_directory(*this->_dir_path / NewDirName)) {
			std::cout << "Succesfull creation of the directory!" << std::endl;
		}
		//---------------------------------------------------------------------//
		else {
			std::cout << "Error while creating the directory!" << std::endl;
		}
		//---------------------------------------------------------------------//
	}
	catch (const FS::filesystem_error& err) {
		std::cerr << "Filesystem failure ! - " << err.what()
			<< err.code()
			<< err.path1() << std::endl;
		throw;
	}
	catch (const std::exception& exc) {
		std::cerr << "Exception caught - " << exc.what() << std::endl;
	}
}
//---------------------------------------------------------------------//
void Directory::RemoveDirectory(const FS::path& RemName) const{
	//---------------------------------------------------------------------//
	if (!FS::exists(*this->_dir_path/RemName)) {
		throw FS::filesystem_error("Addition Operation failed!", *this->_dir_path, std::make_error_code(std::errc::bad_file_descriptor));
	}
	//---------------------------------------------------------------------//
	uintmax_t dirc = FS::remove_all(*this->_dir_path/RemName);
	std::cout << "Contents of the directroy were - " << dirc << "pieces!" << std::endl;
}
//---------------------------------------------------------------------//
void Directory::ShowDirectoryContents() const {
	//---------------------------------------------------------------------//
	if (!(FS::exists(*this->_dir_path) && FS::is_directory(*this->_dir_path))) {
		throw FS::filesystem_error("Addition Operation failed!", *this->_dir_path, std::make_error_code(std::errc::bad_file_descriptor));
	}
	//auto fullpath = *this->_dir_path / DirPath; 
	this->_dir_iter = FS::directory_iterator(*this->_dir_path);
	//---------------------------------------------------------------------//
	std::cout << "Directories are - " << std::endl;

	for (const auto& entr : this->_dir_iter) {

		for (int index = 0; index < FSM_HIDDEN_FILES_EXT.size() ; index++ ) {
			std::cout << entr.path() << "-" << entr.file_size() << " bytes" << std::endl; 

			if (entr.path().generic_string()[3] == FSM_HIDDEN_FILES_EXT[index]) {
				std::cout << "Hidden file!" << std::endl; 
			}
		}
	}
}
//---------------------------------------------------------------------//
Directory Directory::MoveToTheDirectory(const FS::path& go_to_path) {
	//---------------------------------------------------------------------//
	if (!FS::exists(go_to_path) || !FS::is_directory(go_to_path)) {
		FS::create_directory(go_to_path);
	}
	this->_dir_iter = FS::directory_iterator(go_to_path);
	*this->_dir_path = go_to_path;
	if (*this->_dir_path == go_to_path) {
		std::cout << "Moved successfully!" << std::endl;
		std::cout << "New Directory - " << *this->_dir_path << std::endl;
	}
	return *this;
}
////---------------------------------------------------------------------//
inline uintmax_t Directory::DirectoryCounter() const {
	if (!(FS::exists(*this->_dir_path) && FS::is_directory(*this->_dir_path))) {
		return -1;
	}
	//---------------------------------------------------------------------//
	uintmax_t counter{ };
	//---------------------------------------------------------------------//
	for (const auto& it : *_dir_path.get()) {
		if (FS::is_directory(it)) ++counter;
	}
	return counter;
	//---------------------------------------------------------------------//
}
//---------------------------------------------------------------------//
void ShowFilepathSymbols(FS::path& other) { 
	for (const auto& iter : other) {
		std::cout << other.root_name()
			<< other.root_directory()
			<< other.root_path() << std::endl; 
		std::cout << iter << std::endl; 
	}
}
//---------------------------------------------------------------------//
