#include "UserInterface.h"
#include <iomanip>
#include <assert.h>


void UserInterface::output_h(map<string, vector<string> >& classes)
{
	
	TreeScanner scanner;
	int class_cnt = 0;
	ofstream output;
	output.open ("report.html");
	output << "<!DOCTYPE html><html><head> </head><body style=\"background-color:YellowGreen	;\">" ; //starting html

	if(classes.empty())
	{
		output<<"<b><p style=\"color:Red;\">No duplicates found!</p></b>";
		output << "</body></html>";
		output.close();
		system("report.html");
		return;
	}
	string memoryUnit[4] = {"B","KB","MB","GB"};

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
			
				output << "<p><p style=\"color:blue\";><b>"
						<<int(fileSize*filesCntInGroup) 
						<<" "<<memoryUnit[unit]<<"; "<<int(fileSize)
						<<" "<<memoryUnit[unit]<<" per file" 
						<<"\tMemory loss : "<<int(fileSize*(filesCntInGroup-1))<<" "
						<<memoryUnit[unit]<<"</p></b>";		

			
			
			for (int i = 0; i < filesCntInGroup; i++)	
				output << " <id=\"header\" style=\"color:Chocolate\"; ><b> "
				<<filenames[i] <<"<br> <hr></b>";
			
		}	
	}
	
	
		output<<  "<p><p style=\"color:DarkRed\";><b>If you want to delete duplicates use the command prompt to choose which to preserve </b></p><br><hr>";
		output << "</body></html>";
		output.close();
		 system("report.html");
		deleteDuplicates(classes,'h');
	
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
	string memoryUnit[4] = {"B","KB","MB","GB"};

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
		
			cout<<'\t'<<int(fileSize*filesCntInGroup)<<" "<<memoryUnit[unit]<<" ; "
				<<int(fileSize)<<" "<<memoryUnit[unit]<<" per file\n"
				<<"\tMemory loss : "<<int(fileSize*(filesCntInGroup-1))
				<<" "<<memoryUnit[unit]<<endl;	
		

        for (size_t i = 0; i < filesCntInGroup; i++)
			cout <<'\t'<<i+1<<')'<< filenames[i] << endl;
		cout << endl;
	}
	deleteDuplicates(classes,'c');
}

void UserInterface::deleteFile(string fname)
{
		if(!DeleteFileA(fname.c_str()))
			cerr<<"Error deleting"<<endl;
}


void UserInterface::deleteDuplicates (map<string, vector<string> >& classes,char token)
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
            int keep;
			cin>>keep;
			keep--;//real index
            if(keep<0 || keep>= (int)filenames.size())
			{
				cout<<"Wrong choice.";
				return;
			}
			while(filename_cnt < filenames.size())
			{
                if((int)filename_cnt!=keep)
					deleteFile(filenames[filename_cnt]);
				filename_cnt++;
			}
			classes.erase(it);
			cout<<endl;
			switch (token)
			{
				case 'c':
				output(classes);
				break;
				case 'h':
				output_h(classes);
				break;
			}
			return;
		}
	}
}

