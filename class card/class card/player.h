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


	bool HasTrump(Suit trump)
	{
		bool HasAnyTrumps = false;
		for (int i = 0; i < _cardsInHand.size(); i++)
		{
			if (_cardsInHand[i].GetSuit() == trump)
				HasAnyTrumps = true;
		}
		return HasAnyTrumps;
	}
	
	int SmallestSuit(Suit suit) // ���������� ������
	{
		int SmallestNumb = 15; //���-14
		for (int i = 0; i < 6; i++)
		{
			if (_cardsInHand[i].GetSuit() == suit && _cardsInHand[i].GetNumb() < SmallestNumb) // ���� ������ ����� ��������� � ����� ����� ������ ��� ���������� ����� 
				SmallestNumb = _cardsInHand[i].GetNumb();
		}
		return SmallestNumb;
	}

	int GetSize()
	{
		return _cardsInHand.size();
	}

	CCard GetRandomCard()
	{	
		int randomNumb = rand() % _cardsInHand.size() - 1;
		return _cardsInHand[randomNumb];
	}

	CCard GetCardC(int i)
	{
		return _cardsInHand[i];
	}

	bool EndTurn()//������ ������� �� enter � ����� ����
	{
		if (_getch() == 13)
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

	void TakeCardInHand(CPlayer p1, CTable t) // ����� ����� �����
	{
		CCard save;
		for (int i = 0; i < t.GetSize(); i++)
		{
			p1.add(t.GetCard(i));// ������ ������ ����� � ����
			t.DeleteItem(t.GetCard(i)); // ������� �� �� �����
		}
	}


	~CPlayer()
	{}

};
