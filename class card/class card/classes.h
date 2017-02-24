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
// от 2 до 10 обычные числа


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
	CCard()                   // конструктор
	{ }
	void set(int n, Suit s)  // установка значения
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


class CPlayer
{
private:
	std::vector <CCard> _cardsInHand;
public:
	CPlayer()                   // конструктор
	{ }

	void add(CCard n)  // 
	{
		_cardsInHand.push_back(n);
	}

	void DisplayCards(CPlayer p1)
	{
		for (int i = 0; i < p1._cardsInHand.size(); i++)
		{

			std::cout << p1._cardsInHand[i].GetAsString().c_str() << " " << std::endl;
		}
	}

	~CPlayer()
	{}

};


class CTable
{
private:
	std::vector <CCard> _cardsOnTable;
	CCard _cozir;// карта которая лежит под колодой
public:
	CTable()                   // конструктор
	{ }
	void setTrump(CCard v)
	{
		_cozir = v;
	}

	CCard getTrump() const
	{
		return _cozir;
	}
	~CTable()
	{ }

};
