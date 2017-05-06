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
	static std::vector <CCard> _cardsOnTable;
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

	static int GetSize()
	{
		return _cardsOnTable.size();
	}

	void DeleteItem(CCard card)         // пральна??!
	{
		int n;
		for (int i = 0; i < _cardsOnTable.size(); i++)
		{
			if (card.GetAsString() == _cardsOnTable[i].GetAsString())
				n = i;
		}
		_cardsOnTable.erase(_cardsOnTable.begin() + n, _cardsOnTable.begin() + n);
		
	}

	CCard GetCard(int i)
	{
		return _cardsOnTable[i];
	}



	Suit getTrump() const
	{
		return _cozir.GetSuit();
	}
	~CTable()
	{ }

};