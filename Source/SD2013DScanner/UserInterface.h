#pragma once
#include "TreeScanner.h"
#include "Windows.h"

class UserInterface
{
public:
	void output(map<string, vector<string> > classes);
private:
	void deleteFile(string fname);
public:
	void deleteDuplicates ( map<string, vector<string> >classes);

};

