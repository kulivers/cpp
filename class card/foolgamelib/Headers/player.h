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

	int SmallestSuit(Suit suit) // наименьший козырь
	{
		int SmallestNumb = 15; //туз-14
		for (int i = 0; i < _cardsInHand.size(); i++)
		{
			if (_cardsInHand[i].GetSuit() == suit && _cardsInHand[i].GetNumb() < SmallestNumb) // если козырь краты совпадает и номер карты меньше чем наименьший номер 
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

	bool EndTurn() //датчик нажати€ на enter в конце хода
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

	void DeleteItem(CCard card) //здась
	{
		int index = 9999;
		for (int i = 0; i < _cardsInHand.size(); i++)// индекс кар€вый, может быть что нет карты
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

	void TakeCardInHand() // игрок берет карты со стола
	{
		CCard save;

		for (int i = 0; i < CTable::GetSize(); i++)
		{

			add(CTable::GetCard(i));// кладем игроку карту в руку
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

	
	CCard CanCoverASuit(CCard card)//  возвращает карту с 1000 номером если не может (ок)

	{
		CCard save;
		std::vector<CCard> CanCover; //козыр€ больше нашего, выберем наименьший
		save.set(0, CTable::getTrump()); // если есть козыр€ но не может побить то вернетс€ ето
	
		if (HasTrump(CTable::getTrump())) 
		{
			for (int i = 0; i < GetSize(); i++)
			{
				if ((GetNumbC(i) > card.GetNumb()) && (CTable::getTrump() == GetSuitC(i))) // не заходит сюда!!!јјјјјјјјјјјјјјјјјјјјјјјјјјјјјјјјјјјјјјјјјјјјјјјјјјјјјјјјјјјјјјјјјјјјјјјј!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!‘
				{
					save.set(GetNumbC(i), GetSuitC(i));
					CanCover.push_back(save);
				}
			}
		}

		int minSuit = 1000;

		for (int i = 0; i < CanCover.size(); i++)//выбираем наименьший
		{
			if (CanCover[i].GetNumb() < minSuit)
				minSuit = CanCover[i].GetNumb();
		}
		save.set(minSuit, CTable::getTrump());
		return save;
	}


	CCard CanCoverNotASuit(CCard card, Suit trump)// может побить не козырь ?  (ок)
	{
		CCard save;
		save.set(0, trump); // если есть козыр€ но не может побить то вернетс€ ето
		std::vector<CCard> CanCoverByNotASuit;  // карты которыми мы можем покрыть (не козыр€) сначала, а потом елси таких нет, пихаем туда все козыр€ и ищем наименьший
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

			for (int i = 0; i < CanCoverByNotASuit.size(); i++)//выбираем наименьший
			{
				if (minNumb < CanCoverByNotASuit[i].GetNumb())
				{
					minNumb = CanCoverByNotASuit[i].GetNumb();
					save.set(minNumb, CanCoverByNotASuit[i].GetSuit());
				}
			}

		}

		else
		{

			int minNumb = 1000;
			for (int i = 0; i < CanCoverByASuit.size(); i++)//выбираем наименьший
			{
				if (minNumb < CanCoverByASuit[i].GetNumb())
				{
					minNumb = CanCoverByASuit[i].GetNumb();
					save.set(minNumb, CanCoverByASuit[i].GetSuit());
				}
			}
			
		}
		


		return save;// возвращает карту с 1000 номером если не может

	}

	void BeatOneCard(CCard lastCard)  // когда атакер кинул под дефендера одну карту и он бьетс€, до цикла подкидывальщиков
	{
		//если на столе четное колличество карт то подкидывают одну карту
		CCard dropToTable;

		if (lastCard.GetSuit() == CTable::getTrump()) // если последн€€ карта на столе(которую подкинули), это козырь
		{
			dropToTable = this->CanCoverASuit(lastCard); //возвращает карту

			if (dropToTable.GetNumb() == 1000)

			{
				//удал€ем карту с номером 1000
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


	void DropToTableCard(CCard card)    //кидает определенную карту
	{
		(*this).DeleteItem(card);
		CTable::PutOnTable(card);
		/*CCard c = p1.back();
		p1.pop_back();*/
	}


	bool CanPopUp()//подкинуть
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


	CCard PopUpCard()//подкинуть
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
