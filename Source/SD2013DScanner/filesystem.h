// A very basic Win32 based library for filesystem manipulation.

#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <Windows.h>
using namespace std;

#define BUFFER_SIZE 1024


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
void GetFilesAndDirectoriesRecursive(
    const string& base_path,
    vector<string>& files_and_directories);