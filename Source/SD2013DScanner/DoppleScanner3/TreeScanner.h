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
	
	/// Checks whether the given absolute or relative path is a valid file.
	///@param path A constant reference to a string of a path
	///@return A whether the string is a path to a file 
	bool IsFile(const string& path); 

	/// Checks whether the given absolute or relative path is a valid directory. 
	bool IsDirectory(const string& path); 

	/// A method that estimates the size of a file
	/// @param filename A constant reference to a string of a filename 
	/// @return  The number of bytes the given file contains.
	size_t FileSizeInBytes(const string& filename); 
	   
	
	//!  Returns the names of all files and directories directly contained in a
		//! given directory specified by its absolute or relative path.
	/*!
	  \param directory a string to the main directory.
	  \return  Returns the names of all files and directories directly or indirectly
	 (recursively) contained in a given directory specified by it's absolute
	 or relative path. The names are stored in the output parameter:
	 files_and_directories and are included using an in-order traversal of
	 the filesystem..
	*/
	vector<string> GetFilesAndDirectoriesFlat(const string& directory);

	///Recursive version of GetFilesAndDirectoriesFlat(...)
	///@see GetFilesAndDirectoriesFlat()
	///@param base_path A constant reference to a string a base path
	///@param files_and_directories A reference to a vector of strings of filenames and the paths to them
	void GetFilesAndDirectoriesRecursive(const string& base_path,vector<string>& files_and_directories);

	/// Recursively traverses the files in a base directory and creates a map
	/// from hashes of file contents to a vector of filenames. This results in a grouping in which the names of all
	/// files with the same content are put into the same vector. 
	void GroupIntoClasses(const string& base_directory,map<string, vector<string> >& classes);
};

