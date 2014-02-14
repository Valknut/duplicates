#include "UserInterface.h"
#include <iomanip>


void UserInterface::output_h(map<string, vector<string> > classes)
{
	TreeScanner scanner;
	int class_cnt = 0;
	ofstream output;
    output.open ("report.html");
    output << "<!DOCTYPE html><html><head></head><body style=\"background-color:YellowGreen	;\">" ; //starting html

	cout<<fixed<<setprecision(2);
	for (map<string, vector<string> >::iterator it = classes.begin();it != classes.end();it++)
	{
		vector<string>& filenames = it->second;
		size_t filesCntInGroup=filenames.size();
		if(filesCntInGroup>1)
		{

			double fileSize = scanner.FileSizeInBytes(filenames[0]);
			output <<" <h  style=\"color:green	;\"> "
				<<"<b>Duplicate group #" << (++class_cnt) <<"</b></h>" << endl;
			int unit=0;
			while(fileSize>=1024)
			{
				fileSize/=1024;
				unit++;
			}
			if(unit==0)
			{
				output << "<p><p style=\"color:blue\";><b>"
 						<<int(fileSize*filesCntInGroup) 
 						<<" B ; "<<int(fileSize)
 						<<" B per file" 
 						<<"\tMemory loss : "<<int(fileSize*(filesCntInGroup-1))<<" B" <<"</p></b>";		
			}
			if(unit==1)
			{
				output << "<p><p style=\"color:blue\";><b>"
 						<<int(fileSize*filesCntInGroup) 
 						<<" KB ; "<<int(fileSize)
 						<<" KB per file"
 						<<"\tMemory loss : "<<int(fileSize*(filesCntInGroup-1))<<" KB" <<"</p></b>";
			}
			if(unit==2)
			{
					output << "<p><p style=\"color:blue\";><b>"
 							<<int(fileSize*filesCntInGroup)
 							<<" MB ; "<<int(fileSize)
 							<<" MB per file"
 							<<"\tMemory loss : "<<int(fileSize*(filesCntInGroup-1))<<" MB" <<"</p></b>";
			}
			if(unit>=3)
			{
					output << "<p><p style=\"color:blue\";><b>"
 							<<int(fileSize*filesCntInGroup) 
							<<" GB ; "<<int(fileSize)
 							<<" GB per file"
 							<<"\tMemory loss : "<<int(fileSize*(filesCntInGroup-1))<<" GB" <<"</p></b>";
			}
			
			for (int i = 0; i < filesCntInGroup; i++)
				output << " <id=\"header\" style=\"color:Chocolate\"; ><b> " <<filenames[i] <<"<br> <hr></b>";
			
		}	
	}
	if(class_cnt==0)
	{
		output<<"<p>No duplicates found!</p>";
		output << "</body></html>";
 		output.close();
 	}
 	else
 	{
 		output<<  "<p><p style=\"color:DarkRed\";><b>If you want to delete duplicates use the command prompt to choose which to preserve </b></p><br><hr>";
 		output << "</body></html>";
 		output.close();
 		 system("report.html");
 		deleteDuplicates(classes);
 	}
}

void UserInterface::output(map<string, vector<string> >& classes)
{
	if(classes.empty())
	{
		cout<<"No duplicates found!\n";
		return;
	}
	TreeScanner scanner;
	size_t class_cnt = 0;

	cout<<fixed<<setprecision(2);
	for (map<string, vector<string> >::iterator it = classes.begin();it != classes.end();it++)
	{
		vector<string>& filenames = it->second;
		size_t filesCntInGroup=filenames.size();
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
			cout <<'\t'<<i+1<<')'<< filenames[i] << endl;
		cout << endl;
	}
	deleteDuplicates(classes);
}

void UserInterface::deleteFile(string fname)
{
		if(!DeleteFileA(fname.c_str()))
			cerr<<"Error deleting"<<endl;
}


void UserInterface::deleteDuplicates (map<string, vector<string> >& classes)
{
	cout<<"Do you want to delete the redundant files ? (Y/N)";
	char answer;
	cin>>answer;
	if(answer!='y'&&answer!='Y')
		return;

	size_t choosenGroup=1;
	if(classes.size()>1)
	{
		cout<<"Select a group #: ";
		cin>>choosenGroup;
		if(choosenGroup<1 || choosenGroup>classes.size())
		{
			cout<<"Wrong choice.";
			return;
		}
	}
		
			
	size_t group_cnt=0;
	for (map<string, vector<string> >::iterator it = classes.begin();it != classes.end();it++)
	{
		vector <string>& filenames = it->second;
		if(++group_cnt==choosenGroup)
		{
			size_t filename_cnt = 0;
			cout<<"Which file do you want to keep ?";
			size_t keep;
			cin>>keep;
			keep--;//real index
			if(keep<0 || keep>=filenames.size())
			{
				cout<<"Wrong choice.";
				return;
			}
			while(filename_cnt < filenames.size())
			{
				if(filename_cnt!=keep)
					deleteFile(filenames[filename_cnt]);
				filename_cnt++;
			}
			classes.erase(it);
			cout<<endl;
			output(classes);
			return;
		}
	}
}
