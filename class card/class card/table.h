#pragma once

#include <iostream>
#include <cstdlib>
#include <locale.h> 
#include <vector>
#include <ctime>
#include <string.h>
#include <vector>
#include "card.h"

class CTable
{
private:
	std::vector <CCard> _cardsOnTable;
	static CCard _cozir;
public:

	CTable()
	{ }
	void PutOnTable(CCard card)
	{
		_cardsOnTable.push_back(card);
	}
	static void setTrump(CCard v)
	{
		_cozir = v;
	}

	CCard GetCard(int i)
	{
		return _cardsOnTable[i];
	}

	int AmountCardsOnTable()
	{
		return _cardsOnTable.size();
	}

	CCard getTrump() const
	{
		return _cozir;
	}
	~CTable()
	{ }

};