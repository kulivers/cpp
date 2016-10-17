#define _CRT_SECURE_NO_WARNINGS
#include "String.h"
#include <cstring>

using namespace egorlab;

CString::CString(const char* content)
{
	_size = strlen(content);
	_content = new char[_size + 1];
	strcpy_s(_content, _size + 1, content);


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
	_size = _size + other._size;
	char *reserve = new char[_size + 1];
	strcpy_s(reserve, _size + 1, _content);// êîïèðóåì èç êîíòåíòà â ðåçåðâ
	strcat_s(reserve, _size + 1, other._content);
	delete[] _content;
	_content = new char[_size + 1];
	strcpy_s(_content, _size + 1, reserve);
	delete[] reserve;
	return *this;
}

CString& CString::operator - (const CString &other)
{
	int resSize = _size - other._size; //óìåíüøèëè ñàéç äî íóæíîãî
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
	//ïðîâåðÿåì ïàðàìåòð, áðîñàåì exception åñëè îí íå òîò
	if (newSize >= _size)
		throw new CStringException("Argument exception: DecreaseSize must be called with newSize less then _size");

	char *reserve = new char[newSize + 1]; //ñäåëàëè íîâûé ðåçåðâ. êîíòåéíåð - íà åäèíèöó áîëüøå äëÿ \0 â êîíöå
	for (int i = 0; i < newSize + 1; i++)    //ñêîïèðîâàëè â ýòîò êîíòåéíåð                            
		reserve[i] = _content[i];

	reserve[newSize] = 0; // \0 èç _content íå ñêîïèðóåòñÿ ïîëþáîìó, ïèøåì ñàìè â ïîñëåäíèé ýëåìåíò
	_size = newSize;

	delete[] _content;// óäàëèëè ñòàðûé
	_content = reserve; //ïåðåíàçíà÷èëè íîâûé
}


CString& CString::operator += (const CString)
{
	_size = _size * 2;
	char *reserve = new char[_size + 1];
	strcpy_s(reserve, _size + 1, _content);// êîïèðóåì èç êîíòåíòà â ðåçåðâ
	strcat_s(reserve, _size + 1, _content);
	delete[] _content;
	_content = new char[_size + 1];
	strcpy_s(_content, _size + 1, reserve);
	delete[] reserve;
	return *this;
}

CString & CString::operator ++()
{
	++_size; //!!! À ÏÐÎÁÅË Â ÑÒÐÎÊÓ ÊÒÎ ÁÓÄÅÒ ÄÎÁÀÂËßÒÜ?!?!?!?
	return *this;
}

CString& CString::operator ++(int)
{
	_size++; //!!! À ÏÐÎÁÅË Â ÑÒÐÎÊÓ ÊÒÎ ÁÓÄÅÒ ÄÎÁÀÂËßÒÜ?!?!?!?
	return *this;
}

CString & CString::operator --()
{
	if (_size == 0)
	{
		cout << "The first component is smaller then second" << endl;
		return *this;
	}
	DecreaseSize(1);

	return *this;
}

/////////////////////////////////////////////////////////////////////////////
//ÎÏÅÐÀÒÎÐÛ -- è --(int) ÑÄÅËÀÍÛ ÎÄÈÍÀÊÎÂÎ, ÝÒÎ ÍÅ ÅÑÒÜ ÏÐÀÂÈËÜÍÎ, ÑÄÅËÀÉ ÊÀÊ ÄÎËÆÍÎ ÁÛÒÜ =) //
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

/*[15:51:41] Kuleshov Alexey: òèïà += ýòî òîæå ñàìîå ÷òî + òîëüêî ñ ñîáîé
[15:52:06] Kuleshov Alexey: èëè == ýòî òîæå ñàìîå ÷òî != òîëüêî ñ !
[15:53:02] Kuleshov Alexey: bool operator!= (const CString& other)
{
return !(operator==(other));
}


èç íåãî - äâà ++ è +=*/