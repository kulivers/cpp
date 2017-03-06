#pragma once
#include <windows.h>
#include <conio.h>
#include <iostream>
#include <cstdlib>
#include <locale.h> 
#include <vector>
#include <ctime>
#include <string.h>
#include <vector>

#include "card.h"

class CPlayer
{
private:
	std::vector <CCard> _cardsInHand;
public:
	CPlayer()
	{ }

	



	CCard GetRandomCard()
	{	
		int randomNumb = rand() % _cardsInHand.size() - 1;
		return _cardsInHand[randomNumb];
	}


	bool EndTurn()//датчик нажатия на enter в конце хода
	{
		if (getch() == 13)
		return true;
	}

	int GetNumbC(int i)
	{
		return _cardsInHand[i].GetNumb();
	}

	Suit GetSuitC(int i)
	{
		return _cardsInHand[i].GetSuit();
	}

	void DeleteItem(CCard card)
	{
		int n;
		for (int i = 0; i < _cardsInHand.size(); i++)
		{
			if (card.GetAsString() == _cardsInHand[i].GetAsString())
				n = i;
		}
		_cardsInHand.erase(_cardsInHand.begin() + n, _cardsInHand.begin() + n);
		
	}
	void add(CCard n)
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
