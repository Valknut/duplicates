#include "UserInterface.h"
#include <iomanip>


void UserInterface::output_h(map<string, vector<string> > classes)
{
	TreeScanner scanner;
	bool areThereDuplicates=false;
	int class_cnt = 0;
	ofstream output;
    output.open ("report.html");
    output << "<!DOCTYPE html><html><head></head><body style=\"background-color:blue	;\">" ; //starting html

	cout<<fixed<<setprecision(2);
	for (map<string, vector<string> >::iterator it = classes.begin();it != classes.end();it++)
	{
		vector<string>& filenames = it->second;
		size_t filesCntInGroup=filenames.size();
		if(filesCntInGroup>1)
		{
			areThereDuplicates=true;
			double fileSize = scanner.FileSizeInBytes(filenames[0]);
			output <<" <h  style=\"background-color:green	;\"> "
				<<"<b>Duplicate group #" << (++class_cnt) <<"</b></h>" << endl;
			int unit=0;
			while(fileSize>=1024)
			{
				fileSize/=1024;
				unit++;
			}
			if(unit==0)
			{
				output << "<p><span style='font-weight: bold'>"
					<<int(fileSize*filesCntInGroup)<<"</span><span>" 
					<<" B ; "<<int(fileSize)<<"</span><span>"
					<<" B per file"<< "</span><span>"
					<<"\tMemory loss : "<<int(fileSize*(filesCntInGroup-1))<<" B" <<"</span></p>";	
			}
			if(unit==1)
			{
				output << "<p><span style='font-weight: bold'>"
					<<int(fileSize*filesCntInGroup)<<"</span><span>" 
					<<" KB ; "<<int(fileSize)<<"</span><span>"
					<<" KB per file"<< "</span><span>"
					<<"\tMemory loss : "<<int(fileSize*(filesCntInGroup-1))<<" KB" <<"</span></p>";
			}
			if(unit==2)
			{
					output << "<p><span style='font-weight: bold'>"
					<<int(fileSize*filesCntInGroup)<<"</span><span>" 
					<<" MB ; "<<int(fileSize)<<"</span><span>"
					<<" MB per file"<< "</span><span>"
					<<"\tMemory loss : "<<int(fileSize*(filesCntInGroup-1))<<" MB" <<"</span></p>";
			}
			if(unit>=3)
			{
					output << "<p><span style='font-weight: bold'>"
					<<int(fileSize*filesCntInGroup)<<"</span><span>" 
					<<" MB ; "<<int(fileSize)<<"</span><span>"
					<<" MB per file"<< "</span><span>"
					<<"\tMemory loss : "<<int(fileSize*(filesCntInGroup-1))<<" MB" <<"</span></p>";
			}
			
			for (int i = 0; i < filesCntInGroup; i++)
				output << " <id=\"header\" style=\"background-color:#00FF00;\"> " <<filenames[i] <<"<br> <hr>";
			
		}	
	}
	if(!areThereDuplicates)
		output<<"<p>No duplicates found!</p>";
	output << "</body></html>";
    output.close();
}

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
			
			for (int i = 0; i < filesCntInGroup; i++)
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
}
