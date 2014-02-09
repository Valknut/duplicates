#include "HashGenerator.h"
#include "TreeScanner.h"
#include "UserInterface.h"
#include "filesystem.h"
#include "utils.h"

#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;


int main(int argc, char* argv[]) {
  string error_message =
      "Please enter the absolute or relative path to a directory.";

  // Parse the command line arguments.
  if (argc != 2) {
    cout << error_message << endl;
    return 1;
  }
  string base_directory = string(argv[1]);
  if (!IsDirectory(base_directory)) {
    cout << error_message << endl;
    return 1;
  }

  // Find and print out equivalence class information.
  map<string, vector<string> > classes;
  GroupIntoEquivalenceClasses(base_directory, classes);

  int class_cnt = 0;
  for (map<string, vector<string> >::iterator it = classes.begin();
       it != classes.end();
       it++) {
    cout << "Equivalence class #" << (++class_cnt) << endl;
    vector<string>& filenames = it->second;
    for (int i = 0; i < filenames.size(); i++) {
      size_t bytes = FileSizeInBytes(filenames[i]);
      cout << filenames[i] << endl;
    }
    cout << endl;
  }
  return 0;
}