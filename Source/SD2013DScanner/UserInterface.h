#pragma once
#include "TreeScanner.h"
#include "Windows.h"

/// Constructs the user interface and contains.
/// the different types ot output and input forms.
class UserInterface
{
public:
	/// Outputs the groups of duplicates in the command prompt.
	/// Shows the size consumed by duplicate files.
	///@param classes A map of strings and vectors of strings grouping files(directories) by their hash value.
	void output(map<string, vector<string> >& classes);

	void output_h(map <string, vector<string > >& classes);

private:
	/// Deletes a single file.
	///@param fname A string of a directory to a file.
	void deleteFile(string fname);
public:


	///Deletes a group of duplicates except one chosen by the user.
	///@param class_cnt Keeps count of how many duplicates groups there are.
	///@param token HTML/CMD mode token.
	void deleteDuplicates ( map<string, vector<string> >& classes,char token);


};

