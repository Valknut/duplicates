#include "HashGenerator.h"
#include "TreeScanner.h"
#include "UserInterface.h"
#include "filesystem.h"
#include "utils.h"

#include <iomanip>
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

  cout<<fixed<<setprecision(2);

  bool areThereDuplicates=false;
  int class_cnt = 0;
  for (map<string, vector<string> >::iterator it = classes.begin();
       it != classes.end();
       it++) 
  {
    vector<string>& filenames = it->second;
	size_t filesCntInGroup=filenames.size();

	if(filesCntInGroup>1)
	{
		areThereDuplicates=true;
		double fileSize = FileSizeInBytes(filenames[0]);
		cout << "Duplicate group #" << (++class_cnt) << endl;
		int unit=0;
		while(fileSize>=1024)
		{
			fileSize/=1024;
			unit++;
		}
		if(unit==0)
		{
			cout<<'\t'<<int(fileSize*filesCntInGroup)<<" B ; "<<int(fileSize)<<" B per file\n"
				<<"\tMemory loss : "<<int(fileSize*(filesCntInGroup-1))<<" B\n";	
		}
		if(unit==1)
		{
			cout<<'\t'<<fileSize*filesCntInGroup<<" KB ; "<<fileSize<<" KB per file\n"
				<<"\tMemory loss : "<<fileSize*(filesCntInGroup-1)<<" KB\n";	
		}
		if(unit==2)
		{
			cout<<'\t'<<fileSize*filesCntInGroup<<" MB ; "<<fileSize<<" MB per file\n"
				<<"\tMemory loss : "<<fileSize*(filesCntInGroup-1)<<" MB\n";	
		}
		if(unit>=3)
		{
			cout<<'\t'<<fileSize*filesCntInGroup<<" GB ; "<<fileSize<<" GB per file\n"
				<<"\tMemory loss : "<<fileSize*(filesCntInGroup-1)<<" GB\n";	
		}
		


		for (int i = 0; i < filesCntInGroup; i++)
			cout <<'\t'<< filenames[i] << endl;
		cout << endl;
	}
  }
  if(!areThereDuplicates)
	  cout<<"No duplicates found!\n";

  return 0;
}