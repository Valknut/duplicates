#include "SHA1.h"
#include "TreeScanner.h"
#include "UserInterface.h"

#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;


int main(int argc, char* argv[])
{
	TreeScanner scanner;
	UserInterface UI;

  // Parse the command line arguments.
  if (argc != 2)
  {
	  cout << "Please enter the path to a directory." << endl;
      return 1;
  }
  string mainDir = string(argv[1]);
  if (!scanner.IsDirectory(mainDir))
  {
	  cout << "Please enter the path to a directory." << endl;
      return 1;
  }

  // Find and print out equivalence class information.
  map<string, vector<string> > classes;
  scanner.GroupIntoClasses(mainDir,classes);

  UI.output(classes);

 
  return 0;
}