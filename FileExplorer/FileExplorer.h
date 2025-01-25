//---------------------------------------------------------------------//
#ifndef  FILEEXPLORER
#define  FILEEXPLORER
//---------------------------------------------------------------------//
#include <iostream>
#include <fstream>
#include <filesystem>
#include <list>
#include <map>
#include <array>
#include <unordered_map>
#include <sstream>
#include <set>
#include <functional>
//---------------------------------------------------------------------//
//---------------------------------------------------------------------//
#include "ErrorLogger.h"
#include "JsonHandlers.cpp"
//---------------------------------------------------------------------//
// My main class for working with a filesystem 
// will be updated as the project grows 
// for now my main goal is to implement all basic tools for the workload e.g removal , addition of files etc. 
//---------------------------------------------------------------------//

//---------------------------------------------------------------------//
namespace FS = std::filesystem;
#define _STR_CAST_U_ static_cast<std::string>
//---------------------------------------------------------------------//
#define _PATH_CAST_U_	  static_cast<std::filesystem::path>
#define _PATH_CAST_REF_U_ static_cast<std::filesystem::path&>
#define _PATH_U_		  std::filesystem::path
//---------------------------------------------------------------------//
const std::array<char, 2U> FSM_HIDDEN_FILES_EXT = { '.' , '$' };
//---------------------------------------------------------------------//
class Directory {
private:
	mutable std::shared_ptr<FS::path> _dir_path{};
	mutable std::shared_ptr<FS::directory_entry> _dir_entry{};
	mutable FS::directory_iterator _dir_iter{};
public:
	//---------------------------------------------------------------------//
	Directory() {
		*_dir_path = "C:\\"; 
		_dir_entry = nullptr; 
		_dir_iter = FS::directory_iterator("C:\\");
	}
	//---------------------------------------------------------------------//
	Directory(const FS::path& _n_dir_name)
		: _dir_path(std::make_shared<FS::path>(_n_dir_name)),
		_dir_entry(std::make_shared<FS::directory_entry>(*_dir_path)),
		_dir_iter(*_dir_path) {
		std::cout << "Current directory is - " << *this->_dir_path << std::endl;
	};
	//---------------------------------------------------------------------//
	Directory(const Directory& other) noexcept;
	Directory(Directory&& other) noexcept;
	//---------------------------------------------------------------------//
	~Directory() = default;
public:
	//---------------------------------------------------------------------//
	FS::path& operator* () { return *_dir_path; }
	FS::path& operator->() { return *_dir_path; }
	//---------------------------------------------------------------------//
	bool operator==(const Directory& other) const;
	bool operator!=(const Directory& other) const;
	FS::path& operator /= (const Directory& other) const;
	//---------------------------------------------------------------------//
	Directory& operator++() noexcept;
	Directory operator++(int) noexcept;
	Directory& at(int& pos);
	//---------------------------------------------------------------------//
	FS::path& GetDirPath() noexcept { return *_dir_path; }
	FS::directory_iterator& GetDirIter() noexcept { return _dir_iter; }
	FS::directory_entry& GetDirEntry() noexcept { return *_dir_entry; }
	//---------------------------------------------------------------------//
private:
	void SetDirIter(const FS::path& npath) noexcept { _dir_iter = FS::directory_iterator(npath); }
	void SetDirEntry(const FS::directory_entry& nentry) { *this->_dir_entry = nentry; }
	void SetDirPath(const FS::path& npath) noexcept { *this->_dir_path = npath; }
	inline std::string underlying_filename_string(const FS::directory_entry& other) const {
		return (other.path().filename().string());
	}
	//---------------------------------------------------------------------//
public:
	//---------------------------------------------------------------------//
	void DirectoryAddFile() const;
	void DirectoryAddFile(const FS::path& filenamestart) const;
	void DirectoryRemoveFile() const;
	void DirectoryRemoveFile(const FS::path& removal_path) const;
	void AddDirectory(const FS::path& NewDirName) const;
	void RemoveDirectory(const FS::path& RemName) const;
	void ShowDirectoryContents() const;
	void MoveToTheDirectory() const;
	Directory MoveToTheDirectory(const FS::path& go_to_path);
	uintmax_t DirectoryCounter() const;

	//---------------------------------------------------------------------//
};
//---------------------------------------------------------------------//
//
//---------------------------------------------------------------------//
#endif // ! FILEEXPLORER
//---------------------------------------------------------------------//