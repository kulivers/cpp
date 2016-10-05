#pragma once
#include <iostream>

using namespace std;

namespace egorlab
{
	class CShape
	{
		virtual void Draw()
		{

			cout << "CShape" << endl;
		}
	};


	class CCircle : CShape
	{
		int _x;
		int _y;
		int _radius;

		virtual void Draw()
		{
			cout << "CCircle" << endl;
		}
	};



	class CString
	{
		char* _content;
		size_t _size;

	public:
		CString()
		{
		}

		~CString()
		{
			delete[] _content;
		}

		CString(const char* content);//constructor
		CString(const CString& str);//copy

	public:
		size_t GetLength() const;

		const char* GetData() const;
		bool operator> (const CString &other) const;
		bool operator< (const CString &other) const;
		bool operator== (const CString &other) const;
		CString& operator= (const CString &other);
		CString& operator+ (const CString &other);
		CString& operator- (const CString &other);
		CString& operator+= (const CString);
		CString& operator++ ();
		CString& operator++ (int);
		CString& operator-- ();
		CString& operator-- (int);
		CString& operator() (int x);
		CString& operator[] (int x);

	private:
		void DecreaseSize(size_t newSize);
	};


	struct CStringException
	{
		string _exceptionMessage;
		
		CStringException(const string& exceptionMessage)
		{
			_exceptionMessage = exceptionMessage;
		}
	};
}