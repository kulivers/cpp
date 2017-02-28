#pragma once

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
