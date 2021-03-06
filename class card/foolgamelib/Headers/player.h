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
	enum Activity { attack, defend };
private:
	std::vector <CCard> _cardsInHand;
	Activity _condition;
public:
	CPlayer()
	{ }


	void ChangeCondition()
	{
		if (_condition == attack)
			_condition = defend;
		else
		_condition = attack;
	}

	void SetAttack()
	{
		_condition = attack;
	}

	void SetDefend()
	{
		_condition = defend;
	}

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
		}
		CTable::ClearTheBoard();
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
		save.set(1000, CTable::getTrump()); // ���� ���� ������ �� �� ����� ������ �� �������� ���
	
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
		save.set(1000, trump); // ���� ���� ������ �� �� ����� ������ �� �������� ���
		std::vector<CCard> CanCoverByNotASuit;  // ����� �������� �� ����� ������� (�� ������) �������, � ����� ���� ����� ���, ������ ���� ��� ������ � ���� ����������
		std::vector<CCard> CanCoverByASuit;


		for (int i = 0; i < GetSize(); i++)
		{
			if (GetNumbC(i) > card.GetNumb() && GetSuitC(i) == card.GetSuit())
				CanCoverByNotASuit.push_back(GetCardC(i));
		}


		if (CanCoverByNotASuit.size() == 0)
		{
			for (int i = 0; i < GetSize(); i++)
			{
				if (GetSuitC(i) == CTable::getTrump())
					CanCoverByASuit.push_back(GetCardC(i));
			}
		}



		if (CanCoverByNotASuit.size() != 0)
		{
			
			int minNumb = 1000;

			for (int i = 0; i < CanCoverByNotASuit.size(); i++)//�������� ����������
			{
				if (minNumb > CanCoverByNotASuit[i].GetNumb())
				{
					minNumb = CanCoverByNotASuit[i].GetNumb();
					save.set(minNumb, CanCoverByNotASuit[i].GetSuit());
				}
			}

		}

		else
		{

			int minNumb = 1000;
			for (int i = 0; i < CanCoverByASuit.size(); i++)//�������� ����������
			{
				if (minNumb > CanCoverByASuit[i].GetNumb())
				{
					minNumb = CanCoverByASuit[i].GetNumb();
					save.set(minNumb, CanCoverByASuit[i].GetSuit());
				}
			}
			
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
		

		if (dropToTable.GetNumb() < 11)
			cout << dropToTable.GetNumb() << " ";

		if (dropToTable.GetNumb() == 11)
			cout << "jack ";
		if (dropToTable.GetNumb() == 12)
			cout << "queen ";
		if (dropToTable.GetNumb() == 13)
			cout << "king ";
		if (dropToTable.GetNumb() == 14)
			cout << "ace ";


		if (dropToTable.GetSuit() == clubs)
			cout << "clubs" << endl;

		if (dropToTable.GetSuit() == diamonds)
			cout << "diamonds" << endl;

		if (dropToTable.GetSuit() == hearts)
			cout << "hearts" << endl;

		if (dropToTable.GetSuit() == spades)
			cout << "spades" << endl;


	}


	void DropToTableCard(CCard card)    //������ ������������ �����
	{
		(*this).DeleteItem(card);
		CTable::PutOnTable(card);
		/*CCard c = p1.back();
		p1.pop_back();*/
	}


	bool CanPopUp()//���������
	{
		for (int i = 0; i < CTable::GetSize(); i++)
		{
			for (int j = 0; j < _cardsInHand.size(); j++)
			{
				if (CTable::GetCard(i).GetNumb() == _cardsInHand[j].GetNumb())
					return true;
				
			}
		}

		return false;

	}


	CCard PopUpCard()//���������
	{
		for (int i = 0; i < CTable::GetSize(); i++)
		{
			for (int j = 0; j < _cardsInHand.size(); j++)
			{
				if (CTable::GetCard(i).GetNumb() == _cardsInHand[j].GetNumb())
					return _cardsInHand[j];
			}
		}



	}


	bool CanBeat(CCard card)
	{
		if (card.GetSuit() == CTable::getTrump())
			if (CanCoverASuit(card).GetNumb() != 1000)
				return true;

		if (card.GetSuit() != CTable::getTrump())
			if (CanCoverNotASuit(card, CTable::getTrump()).GetNumb() != 1000)
				return true;

		return false;
		
	}


	~CPlayer()
	{}

};
