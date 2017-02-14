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
		char operator *();
		CString& operator++ ();
		CString operator++ (int);
		CString& operator-- ();
		CString& operator-- (int);
		CString& operator() (int x);
		CString& operator[] (int x);
		CString& operator-> ();
		CString& operator* (char *x);

	private:
		void ChangeSize(size_t newSize);
		friend istream& operator>>(istream& stream, CString& str);
		friend ostream& operator<<(ostream& a, const CString& b);
	};

	ostream& operator<<(ostream& a, const CString& b)
	{
		a << b.GetData();
		return a;
	}

	//перегрузка для cin
	istream& operator>>(istream& stream, CString& str)
	{
		//char buf[256];
		str.ChangeSize(1000);
		stream >> str._content;
		str.ChangeSize(strlen(str._content));

		return stream;
	}

	struct CStringException
	{
		string _exceptionMessage;

		CStringException(const string& exceptionMessage)
		{
			_exceptionMessage = exceptionMessage;
		}
	};
}