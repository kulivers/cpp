#pragma once

#include <iostream>
#include <cstdlib>
#include <locale.h> 
#include <vector>
#include <ctime>
#include <string.h>
#include <vector>


//must be declared BEFORE CCard
enum Suit { clubs, diamonds, hearts, spades };



const int jack = 11;
const int queen = 12;
const int king = 13;
const int ace = 14;

class CCard
{
private:
	int _number;
	Suit _suit;
public:
	CCard()
	{ }
	void set(int n, Suit s)
	{
		_suit = s; _number = n;
	}

	std::string GetAsString() const
	{
		std::string result;

		if (_number >= 2 && _number <= 10)
			result = '0' + _number;
		else
		{
			switch (_number)
			{
			case jack:  result = 'J'; break;
			case queen: result = 'Q'; break;
			case king:  result = 'K'; break;
			case ace:   result = 'A'; break;
			}
		}
		switch (_suit)
		{
		case clubs:    result += 'c'; break;
		case diamonds: result += 'd'; break;
		case hearts:   result += 'h'; break;
		case spades:   result += 's'; break;
		}

		return result;
	}
};
