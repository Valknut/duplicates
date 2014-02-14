#include "TreeScanner.h"


bool TreeScanner::IsFile (const string& path)
{
	DWORD attributes = GetFileAttributesA(path.c_str());
	return !(attributes & FILE_ATTRIBUTE_DIRECTORY);
}

bool TreeScanner::IsDirectory(const string& path)
{
    DWORD attributes = GetFileAttributesA(path.c_str());
	return attributes & FILE_ATTRIBUTE_DIRECTORY;
}


size_t TreeScanner::FileSizeInBytes(const string& filename) 
{
	size_t size=0;
    ifstream is (filename, ios::binary|ios::ate);
	if (is)
		size= is.tellg();
	is.close();
	return size;  
}

vector<string> TreeScanner::GetFilesAndDirectoriesFlat(const string& directory)
{
	vector<string> files_and_directories;
	string path = directory + "\\*";
	WIN32_FIND_DATAA find_data;
	HANDLE find_data_handle = FindFirstFileA(path.c_str(), &find_data);

	if (find_data_handle == INVALID_HANDLE_VALUE)
		return files_and_directories;

	while (true)
	{
		if (string(find_data.cFileName) != "." &&string(find_data.cFileName) != "..")
			files_and_directories.push_back(find_data.cFileName);

		if (!FindNextFileA(find_data_handle, &find_data))
			break;
	}
    FindClose(find_data_handle);
    return files_and_directories;
}

void TreeScanner::GetFilesAndDirectoriesRecursive(const string& base_path,vector<string>& files_and_directories)
{
	files_and_directories.push_back(base_path);
	if (IsDirectory(base_path))
	{
		vector<string> files_and_directories_flat =	GetFilesAndDirectoriesFlat(base_path);
		for (int i = 0; i < files_and_directories_flat.size(); i++)
		{
			string name = files_and_directories_flat[i];
		    GetFilesAndDirectoriesRecursive(base_path + "\\" + name,files_and_directories);
		}
	}
}

void TreeScanner::GroupIntoClasses(const string& base_directory,map<string, vector<string> >& classes)
{
	classes.clear();
    if (!IsDirectory(base_directory))
		return;
    vector<string> files_and_directories;
	GetFilesAndDirectoriesRecursive(base_directory, files_and_directories);
#pragma omp parallel for
	for (int i = 0; i < files_and_directories.size(); i++)
	{
		string& name = files_and_directories[i];
		SHA1 hash;
		if (IsFile(name))
			classes[hash.from_file(name)].push_back(name);
	}
	map<string, vector<string> >::iterator it = classes.begin();
	while(it != classes.end())
	{
		if(it->second.size()==1)
			classes.erase(it++);
		else
			it++;
	}
}