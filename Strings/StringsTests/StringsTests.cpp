// StringsTests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\Strings\String.h"
#include <iostream>
#include "..\Strings\String.cpp"

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
	CString sda = "ssssss7";
	CString test;
	test = sda + string;
	cout << test.GetData() << endl;
}

void TestMinus()             //не предусмотренно если отнимаемый сайз больше и еще в контент ссссссс7 не попадает а попадает мусор: string	{_content=0x0165eea0 "aaa" _size=0x00000003 }	
{
	CString myString = "ssssss7";
	CString minusString = "aaa";
	const CString mustBeResult = "ssss"; 

	if (!(mustBeResult == (myString - minusString))) //=((((((((((((((( из-за некоторых Я НЕ МОГУ ВЫЗВАТЬ ОПЕРАТОР !=    
	{
		cout << "Minus test error: expected " << mustBeResult.GetData()
			<< ", but actually there is " << (myString - minusString).GetData() << endl;
	}
}

void testPreMinus(const CString& string)
{
	CString sda = "sssssss";
	
}


void TestDPlus()
{
	CString a = "aaa";
	cout << a.GetData() << "." << endl;
	a++;

	cout << a.GetData() << "." << endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	TestDPlus();
		

	return 0;
}

