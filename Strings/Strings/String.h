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
		bool operator > (const CString &other);
		bool operator < (const CString &other);
		bool operator == (const CString &other);
		CString& operator = (const CString &other);
		CString& operator + (const CString &other);
		CString& operator - (const CString &other);
		CString& operator += (const CString);
		CString& operator ++ (const CString);
	};



}