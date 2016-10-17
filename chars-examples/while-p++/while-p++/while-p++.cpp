// while-p++.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

bool CompareStrings(const char* p, const char* q)
{
	//comparing strings p and q
	while (*p && *q && *p++ == *q++);
	return !(*p || *q);
}

int main()
{
	char* p = "Hi there";
	char* q = "Hi there";

	cout << "Are the strings equal? That's very " << (CompareStrings(p, q) ? "true" : "false") << endl;

    return 0;
}

