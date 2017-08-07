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
#include "table.h"
#include "card.h"

/*
ENUM
ATTACKER
DEFENDER

STATUS
*/

using namespace std;

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
		for (size_t i = 0; i < _cardsInHand.size(); i++)
		{
			if (_cardsInHand[i].GetSuit() == trump)
				HasAnyTrumps = true;
		}
		return HasAnyTrumps;
	}

	int SmallestSuit(Suit suit) // ���������� ������
	{
		int SmallestNumb = 15; //���-14
		for (int i = 0; i < _cardsInHand.size(); i++)
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

	bool HasCards() const
	{
		return !_cardsInHand.empty();
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

	void DeleteItem(CCard card) //�����
	{
		int index = 9999;
		for (int i = 0; i < _cardsInHand.size(); i++)// ������ �������, ����� ���� ��� ��� �����
		{
			if (card.GetNumb() == _cardsInHand[i].GetNumb() && card.GetSuit() == _cardsInHand[i].GetSuit())
				index = i;
		}
		if (index != 9999)
			_cardsInHand.erase(_cardsInHand.begin() + index);


		//auto it = find(_cardsInHand.begin(), _cardsInHand.end(), card);
		//_cardsInHand.erase(it);
	}

	void add(CCard n)
	{
		_cardsInHand.push_back(n);
	}

	void DisplayCards()
	{
		for (int i = 0; i < _cardsInHand.size(); i++)
		{
			std::cout << _cardsInHand[i].GetAsString().c_str() << " ";
		}
		std::cout << std::endl;
	}

	void TakeCardInHand() // ����� ����� ����� �� �����
	{
		CCard save;

		for (int i = 0; i < CTable::GetSize(); i++)
		{

			add(CTable::GetCard(i));// ������ ������ ����� � ����
			CTable::DeleteItem(CTable::GetCard(i)); // ������� �� �� �����
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

	
	CCard CanCoverASuit(CCard card)//  ���������� ����� � 1000 ������� ���� �� ����� (��)

	{
		CCard save;
		std::vector<CCard> CanCover; //������ ������ ������, ������� ����������
		save.set(0, CTable::getTrump()); // ���� ���� ������ �� �� ����� ������ �� �������� ���
	
		if (HasTrump(CTable::getTrump())) 
		{
			for (int i = 0; i < GetSize(); i++)
			{
				if ((GetNumbC(i) > card.GetNumb()) && (CTable::getTrump() == GetSuitC(i))) // �� ������� ����!!!������������������������������������������������������������������������!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!�
				{
					save.set(GetNumbC(i), GetSuitC(i));
					CanCover.push_back(save);
				}
			}
		}

		int minSuit = 1000;

		for (int i = 0; i < CanCover.size(); i++)//�������� ����������
		{
			if (CanCover[i].GetNumb() < minSuit)
				minSuit = CanCover[i].GetNumb();
		}
		save.set(minSuit, CTable::getTrump());
		return save;
	}


	CCard CanCoverNotASuit(CCard card, Suit trump)// ����� ������ �� ������ ?  (��)
	{
		CCard save;
		save.set(0, trump); // ���� ���� ������ �� �� ����� ������ �� �������� ���
		std::vector<CCard> CanCover;  // ����� �������� �� ����� ������� (�� ������) �������, � ����� ���� ����� ���, ������ ���� ��� ������ � ���� ����������
		for (int i = 0; i < GetSize(); i++)
		{
			if (GetNumbC(i) > card.GetNumb() && GetSuitC(i) == card.GetSuit())
				CanCover.push_back(GetCardC(i));
			if (GetSuitC(i) == CTable::getTrump())
				CanCover.push_back(GetCardC(i));
		}

		//numbers.empty()=1 ���� ������ ������
		if (CanCover.size() == 0)// ���� ������
		{
			for (int i = 0; i < GetSize(); i++)
			{
				if (GetSuitC(i) == CTable::getTrump())
					CanCover.push_back(GetCardC(i));
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

		return save;// ���������� ����� � 1000 ������� ���� �� �����

	}

	void BeatOneCard(CCard lastCard)  // ����� ������ ����� ��� ��������� ���� ����� � �� ������, �� ����� ����������������
	{
		//���� �� ����� ������ ����������� ���� �� ����������� ���� �����
		CCard dropToTable;

		if (lastCard.GetSuit() == CTable::getTrump()) // ���� ��������� ����� �� �����(������� ���������), ��� ������
		{
			dropToTable = this->CanCoverASuit(lastCard); //���������� �����

			if (dropToTable.GetNumb() == 1000)

			{
				//������� ����� � ������� 1000
				DeleteItem(dropToTable);
				this->TakeCardInHand();
			}
			else
				DropToTableCard(dropToTable);
		}
		else
		{
			dropToTable = this->CanCoverNotASuit(lastCard, CTable::getTrump());

			if (dropToTable.GetNumb() == 1000)
			{
				DeleteItem(dropToTable);
				this->TakeCardInHand();
			}
			else
				DropToTableCard(dropToTable);
		}
		cout << dropToTable.GetNumb() << " " << dropToTable.GetSuit() << endl;


	}


	void DropToTableCard(CCard card)    //������ ������������ �����
	{
		(*this).DeleteItem(card);
		CTable::PutOnTable(card);
		/*CCard c = p1.back();
		p1.pop_back();*/
	}


	bool CanPopUp()
	{
		for (int i = 0; i < CTable::GetSize(); i++)
		{
			for (int j = 0; j < _cardsInHand.size(); j++)
			{
				if (CTable::GetCard(i).GetNumb() == _cardsInHand[j].GetNumb())//������ ������
					return true;
			}
		}

		return false;

	}


	bool CanBeat(CCard card)
	{
		if (CanCoverASuit(card).GetNumb() != 1000 && CanCoverNotASuit(card, CTable::getTrump()).GetNumb() != 1000)
			return true;
		else
			return false;
		
	}


	~CPlayer()
	{}

};
