// while-p++.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define IN
#define OUT
//#define HARDCORE

bool CompareStrings(const char* p, const char* q)
{
	//comparing strings p and q    *q-то что лежит по ссылке 
	while (*p && *q && *p++ == *q++);
	return !(*p || *q);
}

char* CopyStrings(IN const char* in, OUT char* out)
{
#ifdef HARDCORE
	while (*in && *out && (*out++ = *in++));
#else
	while (*in && *out)
	{
		*out = *in;
		if (!(*out = *in))
			break;

		*out++;
		*in++;
	}
#endif

	if (*out)
		*out = 0;

	return out;
}

int main()
{
	int a = 10;
	int& ra = a;
	int* aa = &a;
	ra = 20;
	*aa = 30;
	cout << ra;

    return 0;
}

