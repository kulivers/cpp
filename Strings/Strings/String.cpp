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
	strcpy_s(reserve, _size + 1, _content);// копируем из контента в резерв
	strcat_s(reserve, _size + 1, other._content);
	delete[] _content;
	_content = new char[_size+1];
	strcpy_s(_content, _size+1, reserve);
	delete[] reserve;
	return *this;
}

CString& CString::operator - (const CString &other)
{
	int resSize = _size - other._size; //уменьшили сайз до нужного
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
	//проверяем параметр, бросаем exception если он не тот
	if (newSize >= _size)
		throw new CStringException("Argument exception: DecreaseSize must be called with newSize less then _size");

	char *reserve = new char[newSize + 1]; //сделали новый резерв. контейнер - на единицу больше для \0 в конце
	for (int i = 0; i < newSize + 1; i++)    //скопировали в этот контейнер                            
		reserve[i] = _content[i];

	reserve[newSize] = 0; // \0 из _content не скопируется полюбому, пишем сами в последний элемент
	_size = newSize;

	delete[] _content;// удалили старый
	_content = reserve; //переназначили новый
}


CString& CString::operator += (const CString)
{
	_size = _size*2;
	char *reserve = new char[_size + 1];
	strcpy_s(reserve, _size + 1, _content);// копируем из контента в резерв
	strcat_s(reserve, _size + 1, _content);
	delete[] _content;
	_content = new char[_size + 1];
	strcpy_s(_content, _size + 1, reserve);
	delete[] reserve;
	return *this;
}

CString & CString::operator ++()
{
	++_size; //!!! А ПРОБЕЛ В СТРОКУ КТО БУДЕТ ДОБАВЛЯТЬ?!?!?!?
	return *this;
}

CString& CString::operator ++(int)
{
	_size++; //!!! А ПРОБЕЛ В СТРОКУ КТО БУДЕТ ДОБАВЛЯТЬ?!?!?!?
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
//ОПЕРАТОРЫ -- и --(int) СДЕЛАНЫ ОДИНАКОВО, ЭТО НЕ ЕСТЬ ПРАВИЛЬНО, СДЕЛАЙ КАК ДОЛЖНО БЫТЬ =) //
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

/*[15:51:41] Kuleshov Alexey: типа += это тоже самое что + только с собой
[15:52:06] Kuleshov Alexey: или == это тоже самое что != только с !
[15:53:02] Kuleshov Alexey: bool operator!= (const CString& other)
{
       return !(operator==(other));
	   }
	   
	   
	   из него - два ++ и +=*/