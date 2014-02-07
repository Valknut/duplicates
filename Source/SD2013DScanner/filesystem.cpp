#include "filesystem.h"

bool IsFile(const string& path) {
  DWORD attributes = GetFileAttributesA(path.c_str());
  return !(attributes & FILE_ATTRIBUTE_DIRECTORY);
}

bool IsDirectory(const string& path) {
  DWORD attributes = GetFileAttributesA(path.c_str());
  return attributes & FILE_ATTRIBUTE_DIRECTORY;
}


string ReadFileContents(const string& filename) {
  ifstream stream(filename.c_str(), std::ifstream::binary);
  string content;
  char buf[BUFFER_SIZE];
  while (!stream.fail() && !stream.eof()) {
    stream.read(buf, BUFFER_SIZE);
    content += string(buf, stream.gcount());
  }
  stream.close();
  return content;
}

size_t FileSizeInBytes(const string& filename) {
  
  return ReadFileContents(filename).size();
}

vector<string> GetFilesAndDirectoriesFlat(const string& directory) {
  vector<string> files_and_directories;

  string path = directory + "\\*";
  WIN32_FIND_DATAA find_data;
  HANDLE find_data_handle = FindFirstFileA(path.c_str(), &find_data);

  if (find_data_handle == INVALID_HANDLE_VALUE) {
    return files_and_directories;
  }

  while (true) {
    if (string(find_data.cFileName) != "." &&
        string(find_data.cFileName) != "..") {
      files_and_directories.push_back(find_data.cFileName);
    }
    if (!FindNextFileA(find_data_handle, &find_data)) break;
  }
  FindClose(find_data_handle);
  return files_and_directories;
}


void GetFilesAndDirectoriesRecursive(
    const string& base_path,
    vector<string>& files_and_directories) {

  files_and_directories.push_back(base_path);
  if (IsDirectory(base_path)) {
    vector<string> files_and_directories_flat =
        GetFilesAndDirectoriesFlat(base_path);
    for (int i = 0; i < files_and_directories_flat.size(); i++) {
      string name = files_and_directories_flat[i];
      GetFilesAndDirectoriesRecursive(
          base_path + "\\" + name,
          files_and_directories);
    }
  }
}