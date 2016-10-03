// StringsTests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\Strings\String.h"
#include <iostream>


using namespace egorlab;

void TestcomparisonBiggerConstructor()
{

}

void TestcomparisonSmallerConstructor()
{

}

void TestStringDefaultConstructor()
{
	CString str;
	if (str.GetLength() != 0)
		cout << "TestStringDefaultConstructor fails: Default constructor created not-empty string" << endl; 
}

void TestStringCopyConstructor()
{
	CString str("my text");

	if (str.GetLength() == 0)
		cout << "TestStringCopyConstructor fails: copy constructor created empty string" << endl;

	if (str.GetLength() != 7)
		cout << "TestStringCopyConstructor fails: copy constructor created invalid string" << endl;

	if (strlen(str.GetData()) != 7)
		cout << "TestStringCopyConstructor fails: copy constructor created invalid string" << endl;
}

void ConstructorTest()
{
	CString str(CString("my test"));

	if (str.GetLength() == 0)
		cout << "TestStringCopyConstructor fails: copy constructor created empty string" << endl;

	if (str.GetLength() != 7)
		cout << "TestStringCopyConstructor fails: copy constructor created invalid string" << endl;

	if (strlen(str.GetData()) != 7)
		cout << "TestStringCopyConstructor fails: copy constructor created invalid string" << endl;
}


void Run(const CString& s)
{

}

void Run(const char* ss)
{

}

class CLogger
{
private:
	void WriteToFile(const CString& msg) const
	{
		cout << "CLogger says: " << msg.GetData() << endl;
	}
public:
	CLogger(const CString& filename)
	{}

	void operator()(const CString& msg) const
	{
		WriteToFile(msg);
	}
};

void Do(const CString& s1, void(*logger) (const CString&))
{
	logger("start");
	ConstructorTest();
	logger("ConstructorTest ok");
	TestStringDefaultConstructor();
	TestStringCopyConstructor();
	logger("start s2");

	CString s2("bbbb");
	s2 = s1;

	if (s2 == s1)
		cout << "ok" << endl;
}

void Do(const CString& s1, const CLogger& logger)
{
	logger("start");
	ConstructorTest();
	logger("ConstructorTest ok");
	TestStringDefaultConstructor();
	TestStringCopyConstructor();
	logger("start s2");

	CString s2("bbbb");
	s2 = s1;

	if (s2 == s1)
		cout << "ok" << endl;
}

template<class T>
void Do(const CString& s1, T logger)
{
	logger("start");
	ConstructorTest();
	logger("ConstructorTest ok");
	TestStringDefaultConstructor();
	TestStringCopyConstructor();
	logger("start s2");

	CString s2("bbbb");
	s2 = s1;

	if (s2 == s1)
		cout << "ok" << endl;
}

void LogMessage(const CString& string)
{
	cout << string.GetData() << endl;
}

void LogMessageToFile(const CString& string)
{
	cout << string.GetData() << endl;
}

void testPlus(const CString& string)
{
	CString sda = "sssssss";
	CString test;
	test = sda + string;
	cout << test.GetData() << endl;
}

void testMinus(const CString& string)
{
	CString sda = "sssssssaaaaaaa";
	CString test;
	test = sda - string;
	cout << test.GetData() << endl;
}

void testPreMinus(const CString& string)
{
	CString sda = "sssssss";
	
}

int _tmain(int argc, _TCHAR* argv[])
{
	//CLogger llll("c:\\temp\egorlab.log");

	//llll("a record to log");

	//Do("s1", LogMessageToFile);
	//Do("s11", llll);
	//testMinus("aaaaaaa");

	return 0;
}

