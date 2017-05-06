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

	int GetNumb()
	{
		return _number;
	}

	Suit GetSuit()
	{
		return _suit;
	}

	
	bool operator== (const CCard& other) const
	{
		if (this == &other)
			return true;

		if (_suit != other._suit)
			return false;

		if (_number != other._number)
			return false;

		return true;
	}


	std::string GetAsString() const
	{
		std::string result;
		char buffer[3];
		if (_number >= 2 && _number <= 10)
		{
			_itoa_s(_number, buffer, 3, 10);
			result = buffer;
		}
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
