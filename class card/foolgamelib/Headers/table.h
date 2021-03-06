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
	static void PutOnTable(CCard card)
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

	static void DeleteItem(CCard card)         // �������??! NET
	{
		int n;
		for (int i = 0; i < _cardsOnTable.size(); i++)
		{
			if (card.GetAsString() == _cardsOnTable[i].GetAsString())
				n = i;
		}

		_cardsOnTable.erase(_cardsOnTable.begin() + n, _cardsOnTable.begin() + n);//�� ��������


		_cardsOnTable.erase(_cardsOnTable.begin() + n);// ����� ������ �� �����������

		//vecIntSecond.erase(vecIntSecond.begin() + 1);///������� 1 ������� �������


	}

	static CCard GetCard(int i)// ���
	{
		return _cardsOnTable[i];
	}

	static int getNumbOfTrump()
	{
		return _cozir.GetNumb();
	}

	static Suit getTrump()
	{
		return _cozir.GetSuit();
	}
	
	static CCard getTrumpCard()
	{
		return CCard(_cozir.GetNumb(), _cozir.GetSuit());
	}

	static void ClearTheBoard()
	{
		_cardsOnTable.clear();
	}
	


	~CTable()
	{ }

};