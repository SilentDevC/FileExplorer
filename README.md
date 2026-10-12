# FileExplorer 📁

![C++](https://img.shields.io/badge/Language-C%2B%2B-blue.svg?style=flat&logo=c%2B%2B)
![Boost](https://img.shields.io/badge/Library-Boost-orange.svg?style=flat&logo=boost)

## 🌟 Description

FileExplorer is a custom-built, robust file management system and error logging framework developed in modern C++. It provides a command-line interface (CLI) for performing core filesystem operations, including file and directory manipulation, navigation, and permission handling. Beyond basic file management, it integrates a sophisticated error logging system that converts error messages into an efficient binary format for storage and later decoding. Additionally, the project supports JSON file handling using the Boost.PropertyTree library, enabling structured data management within the filesystem.

Designed with modularity and resilience in mind, FileExplorer employs modern C++ standards, extensive exception handling, and custom classes to ensure scalability and reliable operation. It offers a powerful set of tools for navigating and managing your system, akin to a simplified bash terminal.

## 📚 Table of Contents

*   [🌟 Description](#-description)
*   [✨ Features](#-features)
*   [🛠️ Tech Stack](#%EF%B8%8F-tech-stack)
*   [🚀 Installation](#-installation)
*   [💡 Usage](#-usage)
*   [📂 Project Structure](#-project-structure)
*   [📖 API Reference](#-api-reference)
*   [🤝 Contributing](#-contributing)
*   [📜 License](#-license)
*   [🔗 Important Links](#-important-links)
*   [Acknowlegements](#Acknowlegements)
*   [<footer> Footer](#footer)

## ✨ Features

FileExplorer provides a comprehensive set of features for file system and error management:

### File Management System
*   **Directory Traversal**: Navigate through the filesystem using `cd` command.
*   **File & Directory Creation/Deletion**: Easily `addfile`, `adddir`, `remfile`, and `remdir` from the current directory.
*   **Directory Listing**: View contents of the current directory with `ls`, which also filters out hidden files.
*   **Permissions Handling**: Automatically sets `FS::perms::all` permissions upon file creation.
*   **Robust Error Handling**: Utilizes `std::filesystem::filesystem_error` and custom exceptions for reliable operation.
*   **Custom Operators & Iterators**: Enhances efficient filesystem manipulation with custom C++ constructs.
*   **Restricted Access Paths**: Prevents operations on predefined sensitive paths, improving security and stability.

### Error Logging Framework
*   **Binary Logging**: Converts error messages into a compact binary format for efficient storage in `LogFile.dat`.
*   **Binary-to-String Conversion**: Decodes binary log data back into human-readable error messages.
*   **`std::bitset` Utilization**: Leverages `std::bitset` for robust data representation during binary conversion.
*   **Detailed Error Reporting**: Implements custom `ErrorManager` exceptions and detailed reporting for debugging and convenience.

### JSON File Handling
*   **JSON Information Parsing**: Create and update JSON files (e.g., `prop.json`) with structured project or class metadata using `jsonip`.
*   **JSON File Reading**: Read and display structured data from JSON files using `jsonr`.
*   **Boost.PropertyTree Integration**: Seamlessly handles JSON serialization and deserialization using the powerful Boost library.

### Command-Line Interface (CLI)
*   **Bash-like Commands**: Offers intuitive commands for common filesystem tasks.
*   **Unified Entry Point**: All commands are invoked via the `fsm` prefix.
*   **Extensible Design**: Command processing uses `std::map` of function objects, allowing for easy expansion of new commands.

## 🛠️ Tech Stack

*   **Primary Language**: C++ (Modern C++ standards)
*   **Standard Library**: `std::filesystem` for filesystem operations, `std::bitset` for binary data handling, `std::shared_ptr` for memory management, `std::array`, `std::vector`, `std::map`, `std::stringstream`.
*   **External Libraries**: Boost (specifically `Boost.PropertyTree` for JSON parsing and serialization).
*   **Build System**: Microsoft Visual Studio (recommended), potentially CMake (a `CMakeLists.txt` is present but empty, indicating a possible future or alternative build configuration).
*   **Exception Handling**: Custom and standard C++ exception mechanisms (`std::exception`, `std::filesystem::filesystem_error`, `std::invalid_argument`).

## 🚀 Installation

This project is primarily designed to be built with MS Visual Studio. Ensure you have the necessary prerequisites before proceeding.

### Prerequisites
*   **C++ Compiler**: A C++17 compatible compiler. Microsoft Visual Studio is the recommended environment.
*   **Boost Library**: Specifically, the `Boost.PropertyTree` module must be preinstalled and configured with your compiler. If using Visual Studio, you might need to configure include and library paths manually.

### Building the Project

1.  **Clone the repository**: 
    ```bash
    git clone https://github.com/SilentDevC/FileExplorer.git
    cd FileExplorer
    ```

2.  **Open in Visual Studio**: 
    Open the project (`.sln` or `.vcxproj` if they existed, otherwise create a new C++ project and add the files) in Microsoft Visual Studio.

3.  **Configure Boost (if necessary)**:
    *   Go to **Project Properties** -> **VC++ Directories**.
    *   Add your Boost include path to **Include Directories**.
    *   Add your Boost library path to **Library Directories**.
    *   Go to **Linker** -> **Input** -> **Additional Dependencies** and add the required Boost library files (e.g., `boost_property_tree-vc143-mt-gd-x64-1_84.lib`).

4.  **Build the Solution**: 
    Build the project (e.g., `Ctrl+Shift+B` or from the `Build` menu). This will compile `main.cpp`, `CommandProcess.cpp`, `FileExplorer.cpp`, `ErrorLogger.cpp`, and `JsonHandlers.cpp` into an executable.

## 💡 Usage

FileExplorer operates through a command-line interface. The application starts in the `C:\` directory by default and accepts commands prefixed with `fsm`.

To interact with the FileExplorer, run the compiled executable. You will then be prompted to enter commands.

### General Command Structure

All commands follow the pattern: `fsm <command> [argument]`

### Available Commands

Here are the eight commands supported by the FileExplorer:

| Command   | Description                                           | Example                                       |
| :-------- | :---------------------------------------------------- | :-------------------------------------------- |
| `addfile` | Creates a new file in the current directory.          | `fsm addfile myfile.txt`                      |
| `adddir`  | Creates a new directory in the current directory.     | `fsm adddir NewFolder`                        |
| `remfile` | Removes a specified file.                             | `fsm remfile oldfile.txt`                     |
| `remdir`  | Removes a specified directory and its contents.       | `fsm remdir EmptyFolder`                      |
| `ls`      | Lists the contents of the current directory.          | `fsm ls`                                      |
| `cd`      | Changes the current working directory.                | `fsm cd C:\Users\Public`                    |
| `jsonip`  | Creates or updates a JSON info file.                  | `fsm jsonip myconfig.json`                    |
| `jsonr`   | Reads and displays content from a JSON file.          | `fsm jsonr mydata.json`                       |

### Real-World Use Cases & Workflow

1.  **Exploring and Managing Files**: Start the application and use `fsm ls` to see the current directory content. Navigate with `fsm cd Path\To\Directory`. Create a new log file for a project with `fsm addfile project_log.txt`.

2.  **Creating Project Directories**: You can quickly scaffold new project folders: `fsm adddir MyNewProject`. Then `fsm cd MyNewProject` to move into it.

3.  **Managing Configuration with JSON**: For applications that require structured configuration, use `fsm jsonip config.json` to create a `config.json`. The system will prompt you for `Name`, `Type`, and `Extention` fields. Later, you can inspect this configuration with `fsm jsonr config.json`.

4.  **Security and Restricted Paths**: The `RestrictedAccessPaths.txt` file allows you to define paths that cannot be modified or deleted by the FileExplorer. This prevents accidental changes to critical system directories. Ensure this file is maintained to protect sensitive areas.

5.  **Error Logging**: Any filesystem errors encountered during operations will be logged in `LogFile.dat` in a binary format by the `ErrorManager`. This allows for efficient, tamper-resistant logging that can be decoded later for debugging purposes.

### Example Session

```bash
# Assuming the executable is named FileExplorer.exe
./FileExplorer.exe

# The shell starts at C:\

# List contents
fsm ls
# Output: (shows files/dirs in C:\)

# Create a new directory
fsm adddir MyDocuments
# Output: Succesfull creation of the directory!

# Change into the new directory
fsm cd MyDocuments
# Output: Moved successfully! New Directory - C:\MyDocuments

# Create a file inside MyDocuments
fsm addfile report.txt
# Output: Successful creation of the file !

# List contents of MyDocuments
fsm ls
# Output: C:\MyDocuments\report.txt-0 bytes

# Create a JSON configuration file
fsm jsonip project_config.json
# Input prompts: Enter the Name ! -> MyProject; Enter the Type ! -> ConsoleApp; Enter the Extention ! -> cpp
# Output: Properties have been updated!

# Read the JSON configuration
fsm jsonr project_config.json
# Output: Name: 1.0
# Type: FileExplorer
# Extension: C_Project
# Name: MyProject
# Type: ConsoleApp
# Extention: cpp

# Remove the report file
fsm remfile report.txt
# Output: Successful removal!

# Go back to the root directory
fsm cd C:\
# Output: Moved successfully! New Directory - C:\

# Remove the created directory
fsm remdir MyDocuments
# Output: Contents of the directroy were - 2pieces! (removes folder and config file inside)

# Exit the application (e.g., Ctrl+C or close terminal)
```

## 📂 Project Structure

The repository is organized into several key C++ source and header files, alongside auxiliary data files:

```
FileExplorer/
├── CMakeLists.txt              # CMake build configuration (currently empty)
├── CommandProcess.cpp          # Implements command parsing and execution logic
├── CommandProcess.h            # Header for CommandProcess
├── ErrorLogger.cpp             # Implementation of the binary error logging system
├── ErrorLogger.h               # Header for ErrorLogger
├── FileExplorer.cpp            # Core implementation of filesystem operations (Directory class)
├── FileExplorer.h              # Header for FileExplorer (Directory class definition)
├── JsonHandlers.cpp            # Handles JSON reading and writing using Boost.PropertyTree
├── LogFile.dat                 # Binary file for storing error logs
├── main.cpp                    # Application entry point and main loop
├── prop.json                   # Default JSON file for metadata (used by jsonip/jsonr)
├── README.md                   # Project documentation (this file)
└── RestrictedAccessPaths.txt   # Configuration file for paths with restricted access
```

## 📖 API Reference

The API for this project is primarily its command-line interface. The `Directory` class and `ErrorManager` class expose internal functionalities, which are utilized by the `CommandProcess` module.

### Global Functions (exposed via `fsm` commands)
*   `void Directory::DirectoryAddFile(const std::filesystem::path&)`: Adds a file to the current directory.
*   `void Directory::AddDirectory(const std::filesystem::path&)`: Adds a directory to the current directory.
*   `void Directory::DirectoryRemoveFile(const std::filesystem::path&)`: Removes a file from the current directory.
*   `void Directory::RemoveDirectory(const std::filesystem::path&)`: Removes a directory and its contents from the current directory.
*   `void Directory::ShowDirectoryContents()`: Displays the contents of the current directory.
*   `Directory Directory::MoveToTheDirectory(const std::filesystem::path&)`: Changes the current working directory.
*   `void JsonInfoParser(const std::filesystem::path&)`: Populates a JSON file with descriptive information.
*   `void JsonFileReader(const std::filesystem::path&)`: Reads and prints the content of a JSON file.

These functions are encapsulated and called by the `CommandProcessFuncMap` based on user input.

## 📜 License

This project has MIT License.

## 🔗 Important Links

*   **GitHub Repository**: [https://github.com/SilentDevC/FileExplorer](https://github.com/SilentDevC/FileExplorer)

## Acknowlegements

*   Special thanks to the Boost community for providing the `PropertyTree` library.

### <footer>

--- 

### FileExplorer 📁

Developed by [SilentDevC](https://github.com/SilentDevC) 

*   Star the repository if you found it useful! ⭐
*   Fork the project to contribute or use it as a starting point! 🍴
*   Report issues or suggest enhancements [here](https://github.com/SilentDevC/FileExplorer/issues)! 🐛
*   Reach out via GitHub for any questions or collaborations! 💬
