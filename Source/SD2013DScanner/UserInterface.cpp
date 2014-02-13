#include "UserInterface.h"
#include <iomanip>


void UserInterface::output(map<string, vector<string> > classes)
{
	TreeScanner scanner;
	bool areThereDuplicates=false;
	int class_cnt = 0;
	

	cout<<fixed<<setprecision(2);
	for (map<string, vector<string> >::iterator it = classes.begin();it != classes.end();it++)
	{
		vector<string>& filenames = it->second;
		size_t filesCntInGroup=filenames.size();
		if(filesCntInGroup>1)
		{
			areThereDuplicates=true;
			double fileSize = scanner.FileSizeInBytes(filenames[0]);
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
			
			for (size_t i = 0; i < filesCntInGroup; i++)
				cout <<'\t'<< filenames[i] << endl;
			cout << endl;
		}	
	}


	if(!areThereDuplicates)
		cout<<"No duplicates found!\n";
}

void UserInterface::deleteFile(string fname)
{
		if(!DeleteFileA(fname.c_str()))
			cerr<<"Error deleting"<<endl;
}


void UserInterface::deleteDuplicates ( map<string, vector<string> >classes)
{


	clock_t start = clock();
	for (map<string, vector<string> >::iterator it = classes.begin();it != classes.end();it++)
	{
		vector <string>& filenames = it->second;
		if(filenames.size() > 1)
		{
			size_t cnt = 1;
			while(cnt < filenames.size())
			{
				deleteFile(filenames[cnt++]);
			}
		}
	
	}
	clock_t end = clock();
	cout<<"Deleting took : " << (double) (end - start) << endl;
	
}
