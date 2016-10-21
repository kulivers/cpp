// while-p++.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define IN
#define OUT
#define HARDCORE

bool CompareStrings(const char* p, const char* q)
{
	//comparing strings p and q
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
	char* p = new char[255] { "Hi thereeeeeeeeeeeee\0" };
	char* q = "Hi there";

	int a = 10;
	int b = 20;
	int c = 30;
	int d = 40;

	cout << (a = b = c = d) << endl;

	CopyStrings(q, p);
	cout << p << endl;

	cout << "Are the strings equal? That's very " << (CompareStrings(p, q) ? "true" : "false") << endl;

	delete[] p;

    return 0;
}

