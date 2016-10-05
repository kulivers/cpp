#define _CRT_SECURE_NO_WARNINGS
#include "String.h"
#include <cstring>

using namespace egorlab;

CString::CString(const char* content)
{
	_size = strlen(content);
	_content = new char[_size + 1];
	strcpy_s(_content,  _size + 1, content);


}

CString::CString(const CString& str)
{
	_size = str._size;
	_content = new char[_size + 1];
	strcpy_s(_content, _size + 1, str._content);

}

size_t CString::GetLength() const
{
	return _size;
}

bool CString::operator > (const CString &other) const
{
 if (other._size < _size)
	{
		return true;
	}
}

bool CString::operator <(const CString &other) const
{
	if (other._size > _size)
	{
		return true;
	}
}

const char* CString::GetData() const 
{ 
	return _content; 
}

bool CString::operator == (const CString &other) const
{
	if (other._size != _size)
	{
		return false;
	}
	
	return (strcmp(other._content, _content) == 0);
}




CString& CString::operator = (const CString &other)
{
	_size = other._size;	
	delete[] _content;
	_content = new char[_size + 1];
	strcpy_s(_content, _size + 1, other._content);

	return *this;
}

CString& CString::operator + (const CString &other)
{
	_size = _size + other._size ;
	char *reserve = new char[_size+1]; 
	strcpy_s(reserve, _size + 1, _content);// �������� �� �������� � ������
	strcat_s(reserve, _size + 1, other._content);
	delete[] _content;
	_content = new char[_size+1];
	strcpy_s(_content, _size+1, reserve);
	delete[] reserve;
	return *this;
}

CString& CString::operator - (const CString &other)
{
	int resSize = _size - other._size; //��������� ���� �� �������
	if (resSize < 0)
	{
		cout << "The first component is smaller then second" << endl;
		return *this;
	}
	DecreaseSize(resSize);

	return *this;
}

void CString::DecreaseSize(size_t newSize)
{
	//��������� ��������, ������� exception ���� �� �� ���
	if (newSize >= _size)
		throw new CStringException("Argument exception: DecreaseSize must be called with newSize less then _size");

	char *reserve = new char[newSize + 1]; //������� ����� ������. ��������� - �� ������� ������ ��� \0 � �����
	for (int i = 0; i < newSize + 1; i++)    //����������� � ���� ���������                            
		reserve[i] = _content[i];

	reserve[newSize] = 0; // \0 �� _content �� ����������� ��������, ����� ���� � ��������� �������
	_size = newSize;

	delete[] _content;// ������� ������
	_content = reserve; //������������� �����
}


CString& CString::operator += (const CString)
{
	_size = _size*2;
	char *reserve = new char[_size + 1];
	strcpy_s(reserve, _size + 1, _content);// �������� �� �������� � ������
	strcat_s(reserve, _size + 1, _content);
	delete[] _content;
	_content = new char[_size + 1];
	strcpy_s(_content, _size + 1, reserve);
	delete[] reserve;
	return *this;
}

CString & CString::operator ++()
{
	++_size; //!!! � ������ � ������ ��� ����� ���������?!?!?!?
	return *this;
}

CString& CString::operator ++(int)
{
	_size++; //!!! � ������ � ������ ��� ����� ���������?!?!?!?
	return *this;
}

CString & CString::operator --()
{
	if(_size == 0)
	{
		cout << "The first component is smaller then second" << endl;
		return *this;
	}
	DecreaseSize(1);

	return *this;
}

/////////////////////////////////////////////////////////////////////////////
//��������� -- � --(int) ������� ���������, ��� �� ���� ���������, ������ ��� ������ ���� =) //
/////////////////////////////////////////////////////////////////////////////
CString& CString::operator --(int)
{
	if (_size == 0)
	{
		cout << "The first component is smaller then second" << endl;
		return *this;
	}
	DecreaseSize(1);

	return *this;
}
//CString& CString::operator() (int x)
//{
//	return _content(x);
//}


//CString& CString::operator[] (int x)
//{
//	return _content[x];
//}

/*[15:51:41] Kuleshov Alexey: ���� += ��� ���� ����� ��� + ������ � �����
[15:52:06] Kuleshov Alexey: ��� == ��� ���� ����� ��� != ������ � !
[15:53:02] Kuleshov Alexey: bool operator!= (const CString& other)
{
       return !(operator==(other));
	   }
	   
	   
	   �� ���� - ��� ++ � +=*/