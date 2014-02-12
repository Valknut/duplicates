#pragma once
#include "sha1.h"
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <Windows.h>

using namespace std;

class TreeScanner
{
public:
	
	// Checks whether the given absolute or relative path is a valid file.
	bool IsFile(const string& path);

	// Checks whether the given absolute or relative path is a valid directory. 
	bool IsDirectory(const string& path);

	// Returns the number of bytes the given file contains.
	size_t FileSizeInBytes(const string& filename);

	// Returns the names of all files and directories directly contained in a
	// given directory specified by its absolute or relative path.
	vector<string> GetFilesAndDirectoriesFlat(const string& directory);

	// Returns the names of all files and directories directly or indirectly
	// (recursively) contained in a given directory specified by it's absolute
	// or relative path. The names are stored in the output parameter:
	// files_and_directories and are included using an in-order traversal of
	// the filesystem.
	void GetFilesAndDirectoriesRecursive(const string& base_path,vector<string>& files_and_directories);

	// Recursively traverses the files in a base directory and creates a map
	// from file contents to a vector of filenames. The contents of the files
	// are represented as C++ strings where each character represents a byte
	// from the file. This results in a grouping in which the names of all
	// files with the same content are put into the same vector. 
	void GroupIntoClasses(const string& base_directory,map<string, vector<string> >& classes);
};

