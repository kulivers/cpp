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

bool CString::operator > (const CString &other)
{
 if (other._size < _size)
	{
		return true;
	}
}

bool CString::operator <(const CString &other)
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

bool CString::operator == (const CString &other) 
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
	char *reserve = new char[resSize]; //������� ����� ������. ��������� 
	for (int i = 0; i < resSize; i++)    //����������� � ���� ���������                            ��� ��������� � resSize, ����� ��������� ������ ������ reserve ��� ���� � ��
	{
		reserve[i] = _content[i];
	}
	delete[] _content;// ������� ������
	_content = new char[resSize + 1];//������� ����� � ����� ��������
	strcpy_s(_content, resSize + 1, reserve);// ����������� ���� ������
	delete[] reserve;// ������� ������
	return *this;
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

CString & operator ++()
{
	++_size;
}

CString operator ++(CString & n, int);
{
	_size++;
}

CString & operator --(CString & n);//����������
{

}
CString operator --(CString & n, int);//�����������
{

}

/*[15:51:41] Kuleshov Alexey: ���� += ��� ���� ����� ��� + ������ � �����
[15:52:06] Kuleshov Alexey: ��� == ��� ���� ����� ��� != ������ � !
[15:53:02] Kuleshov Alexey: bool operator!= (const CString& other)
{
       return !(operator==(other));
	   }
	   
	   
	   �� ���� - ��� ++ � +=*/