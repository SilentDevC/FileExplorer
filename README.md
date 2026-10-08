# FileExplorer

This is a custom file management system and error logging framework in C++.
Implemented core filesystem operations, including file addition, removal, directory navigation, and permission handling.
Designed an error logging system that converts error messages into binary data, stores them in a log file.
It uses MS Visual Studio as a build system .

File Explorer:

  Supports directory traversal, file addition/removal, and directory creation/deletion.
  Handles file permissions and ensures robust error handling for missing or inaccessible files.
  Custom operators and iterators for efficient filesystem manipulation.
  Supports Json File handling via Boost Open-Source Library (specifically using property_tree module).

Error Logger:

  Logs error messages in binary format for efficiency and later decoding.
  Uses std::bitset and binary-to-string conversion for robust data representation.
  Implements exceptions and detailed error reporting for debugging and convenience.

What I've used:

  C++ (Modern C++ standards)
  Exception handling for error resilience
  Modular design with custom classes for scalability
  Parts of the STL like shared pointer , bitset etc. 
  Also for this project to compile properly you should have preinstalled Boost - Property Tree Module

How to use:

  This framework supports eight basic commands ( similar to bash terminal ) , two of those are for operating Json Files . 
  To use this teminal write fsm and after that one of following commands 
  
  addfile
  adddir 
  remfile
  remdir
  ls  
  cd  
  jsonip 
  jsonr 

