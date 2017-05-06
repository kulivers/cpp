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
#include <algorithm>

#include "card.h"
/*
ENUM
ATTACKER
DEFENDER

STATUS
*/

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
		if (randomNumb < 0)
			randomNumb = 0;

		return _cardsInHand[randomNumb];
	}
	
	bool HasCards()
	{
		if (!_cardsInHand.empty())
			return true;
		else
			return false;
	}

	CCard GetCardC(int i)
	{
		return _cardsInHand[i];
	}

	bool EndTurn() //������ ������� �� enter � ����� ����
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
		auto it = find(_cardsInHand.begin(), _cardsInHand.end(), card);
		_cardsInHand.erase(it);
	}

	void add(CCard n)
	{
		_cardsInHand.push_back(n);
	}

	void DisplayCards(CPlayer p1) 
	{
		for (int i = 0; i < p1._cardsInHand.size(); i++)
		{
			std::cout << p1._cardsInHand[i].GetAsString().c_str() << " ";
		}
		std::cout << std::endl;
	}

	void TakeCardInHand(CPlayer p1, CTable t) // ����� ����� ����� �� �����
	{
		CCard save;
		for (int i = 0; i < t.GetSize(); i++)
		{
			p1.add(t.GetCard(i));// ������ ������ ����� � ����
			t.DeleteItem(t.GetCard(i)); // ������� �� �� �����
		}
	}

	CPlayer equal(CPlayer player)
	{
		CPlayer save;
		for (int i = 0; i < player.GetSize(); i++)
		{
			save.add(player.GetCardC(i));
		}
		return save;
	}


	CCard CanCoverASuit(CCard card, CPlayer& p1, Suit trump)// ����� ������ ������?
	{
		CCard save;
		vector<CCard> CanCover; //������ ������ ������, ������� ����������
		save.set(0, trump); // ���� ���� ������ �� �� ����� ������ �� �������� ���
		if (p1.HasTrump(trump) == true)// � ������ ���� ������?
		{
			for (int i = 0; i < p1.GetSize(); i++)
			{
				if (card.GetNumb() > p1.GetNumbC(i))
					save.set(p1.GetNumbC(i), p1.GetSuitC(i));
				CanCover.push_back(save);
			}
		}
		int minSuit = 1000;
		for (int i = 0; i < CanCover.size(); i++)//�������� ����������
		{
			if (minSuit < CanCover[i].GetNumb())
				minSuit = CanCover[i].GetNumb();
		}
		save.set(minSuit, trump);
		return save;
	}// ���������� ����� � 0 ������� ���� �� �����

	CCard CanCoverNotASuit(CCard card, CPlayer& p1, Suit trump)// ����� ������ �� ������ ? 
	{
		CCard save;
		save.set(0, trump); // ���� ���� ������ �� �� ����� ������ �� �������� ���
		vector<CCard> CanCover;  // ����� �������� �� ����� ������� (�� ������) �������, � ����� ���� ����� ���, ������ ���� ��� ������ � ���� ����������
		for (int i = 0; i < p1.GetSize(); i++)
		{
			if (p1.GetNumbC(i) > card.GetNumb() && p1.GetSuitC(i) == card.GetSuit())
				CanCover.push_back(p1.GetCardC(i));
		}

		//numbers.empty()=1 ���� ������ ������
		if (CanCover.size() == 0)// ���� ������
		{
			for (int i = 0; i < p1.GetSize(); i++)
			{
				if (p1.GetSuitC(i) == trump)
					CanCover.push_back(p1.GetCardC(i));
			}

			int minSuit = 1000;
			for (int i = 0; i < CanCover.size(); i++)//�������� ����������
			{
				if (minSuit < CanCover[i].GetNumb())
					minSuit = CanCover[i].GetNumb();
			}
			save.set(minSuit, trump);
		}
		else// ���� ����� ������ �� �������                        //����� ����� ������, ���� ���������
		{
			int minNumb = 1000;
			for (int i = 0; i < CanCover.size(); i++)//�������� ����������
			{
				if (CanCover[i].GetNumb() < minNumb)
					minNumb = CanCover[i].GetNumb();
			}
			save.set(minNumb, card.GetSuit());
		}

		return save;// ���������� ����� � 0 ������� ���� �� �����

	}


	bool CanPopUp(CTable& t)
	{
		int a = 0;
		for (int i = 0; i < t.GetSize(); i++)
		{
			for (int j = 0; j < _cardsInHand.size(); j++)
			{
				if (t.GetCard(i).GetNumb() == _cardsInHand[i].GetNumb())
					a++;
			}
		}
		if (a != 0)
			return true;
		else
			return false;
	}


	
	~CPlayer()
	{}

};
