#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\SD2013DScanner\TreeScanner.cpp"
#include "..\SD2013DScanner\SHA1.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TreeScanner_Test
{		
	TEST_CLASS(TreeScanner_Test)
	{
	public:
		TreeScanner scan;
		
		TEST_METHOD(IsFile_Test)
		{
			Assert::IsTrue(scan.IsFile("D:/SDP/Source/test_dir/bravo.txt"));
			Assert::IsFalse(scan.IsFile("D:/SDP/Source"));
		}
		TEST_METHOD(IsDirectory_Test)
		{
			Assert::IsTrue(scan.IsDirectory("D:/SDP/Source"));
			Assert::IsFalse(scan.IsDirectory("D:/SDP/Source/test_dir/alpha.txt"));
		}
		TEST_METHOD(FileSizeInBytes_Test)
		{
			Assert::IsTrue(scan.FileSizeInBytes("D:/SDP/Source/test_dir/charlie.txt")==5);
			Assert::AreEqual(scan.FileSizeInBytes("D:/SDP/Source/test_dir/MU.jpg"),
				scan.FileSizeInBytes("D:/SDP/Source/test_dir/New folder/united.jpg"));
		}
		TEST_METHOD(GetFilesAndDirectoriesFlat_Test)
		{
			vector<string> test;
			Assert::IsTrue(test.empty());
			test=scan.GetFilesAndDirectoriesFlat("D:/SDP/Source/test_dir");
			Assert::IsTrue(test.size()==5);
		}
		TEST_METHOD(GetFilesAndDirectoriesRecursive_Test)
		{
			vector<string> test;
			Assert::IsTrue(test.empty());
			scan.GetFilesAndDirectoriesRecursive("D:/SDP/Source/test_dir",test);
			Assert::IsTrue(test.size()==8);
			Assert::AreEqual(test.front(),string("D:/SDP/Source/test_dir"));
		}
		TEST_METHOD(GroupIntoClasses_Test)
		{
			map<string, vector<string> > test;
			Assert::IsTrue(test.empty());
			scan.GroupIntoClasses("D:/SDP/Source/test_dir",test);
			Assert::IsTrue(test.size()==4);

		}

	};
}