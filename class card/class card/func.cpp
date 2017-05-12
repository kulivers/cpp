#pragma once


#include "stdafx.h"
#include "card.h"
#include "table.h"
#include "player.h"
#include <iterator>
#include <algorithm>
#include "Functions.h"

using namespace std;

/*
ну слудующую функцию забывай - игроки кидают любую карту, и пуст это будет тип бито
и потом ход другого игрока - то же самое
и такипока колода не закончится                  
*/
CCard CTable::_cozir;
std::vector <CCard> CTable::_cardsOnTable;


void SpreadCards(vector<CCard>& deck, CPlayer& p)        //раздача карт одному игроку
{
	while(p.GetSize() < 6 && !deck.empty()) 
	{
		p.add(deck.back());
		deck.pop_back();
	}
}

void ShowTrump(const CTable& t) // показать козырь
{
	cout << "Tramp is " << t.getTrump() << endl;
}



CPlayer WhoPlaysFirst(vector<CCard>& deck, CPlayer& p1, CPlayer& p2, CTable& t)//кто первый ходит
{
	if (p1.SmallestSuit(t.getTrump()) < p2.SmallestSuit(CTable::getTrump()))
		return p1;
	else
		return p2;

	if (p1.SmallestSuit(t.getTrump()) == p2.SmallestSuit(t.getTrump()))// если оба без козырей
		return p1;//начинает первый, типо если будет онлайн игра то там все равно рандомно кто то первым будет
	
}

bool RuleCanThrowUp(CCard card, CTable& t) // можно подкинуть?
{
		for (int j = 0; j < t.GetSize(); j++)
		{
			if (card.GetNumb() == t.GetCard(j).GetNumb())
				return true;
			else
				return false;
		}
}

CCard DropToTableRandCard(CPlayer& p1)    //кидает рандомную карту
{
	CCard card = p1.GetRandomCard();
	p1.DeleteItem(card);
	CTable::PutOnTable(card);
	/*CCard c = p1.back();
	p1.pop_back();*/

	return card;
}






void DistributionOfLakingCards(vector<CPlayer>& _players, vector<CCard>& deck)//раздача карт тем у кого не хватает
{
	CCard save;
	for (int i = 0; i < _players.size(); i++)//идем по  игрокам
	{
		if (_players[i].GetSize() < 7)//если кол-во карт у игрока не будет = 6
		{
			while (_players[i].GetSize() != 6)
			{
				save.set(deck[deck.size()].GetNumb(), deck[deck.size()].GetSuit()); //правильно ? типо последнюю карту берем
				deck.pop_back();
				_players[i].add(save);
			}
		}
	}
}


void Distribution(vector<CPlayer>& _players, vector<CCard>& deck)
{
	CTable::setTrump(deck.front());
	DistributionOfLakingCards(_players, deck);
}

bool TheEndOfGame(vector<CPlayer>& players)
{
	int CountNotAnEmptyPlayers=0; //колличество непустых игроков
	for (int i = 0; i < players.size(); i++)
	{
		if (players[i].HasCards() == true)
			CountNotAnEmptyPlayers++;
	}
	if (CountNotAnEmptyPlayers == 1)
		return true;
	else
		return false;
}




int NumberOfPlayer(CPlayer a, vector<CPlayer> players)
{
	int d;
	for (int i = 0; i < players.size(); i++)
	{
		if (a.GetCardC(0) == players[i].GetCardC(0))
			d = i;
	}
	return d;
}




void Turn(vector<CPlayer>& _players, vector<CCard>& deck, const CPlayer& FirstTurnPlayer)//в цикле после первого хода
{
	if (deck.size() != 0)
		DistributionOfLakingCards(_players, deck); //раздаем карты кому не хватает




	int AttackPlayer = NumberOfPlayer(FirstTurnPlayer, _players) + 1;
	int DefendPlayer;
	int FirstPopUpPlayer;
	int SecondPopUpPlayer;

	if (AttackPlayer == _players.size())// задаем DefendPlayer
	{
		DefendPlayer = 0;
	}
	else
	{
		DefendPlayer = AttackPlayer + 1;
	}


	////Задаем подкидывающих
	FirstPopUpPlayer = DefendPlayer - 1;
	SecondPopUpPlayer = DefendPlayer + 1;
	if (DefendPlayer == _players.size())
	{
		FirstPopUpPlayer = DefendPlayer - 1;
		SecondPopUpPlayer = 0;
	}
	if (DefendPlayer == 0)
	{
		FirstPopUpPlayer = _players.size();
		SecondPopUpPlayer = DefendPlayer + 1;
	}

	CCard lastcard = DropToTableRandCard(_players[AttackPlayer]); //здесь атакер кидает под дефуендера

	// сделать так, что если колличество карт на столе - четное значение, то кидает карту Подкидывающий 1 или 2(только одну), а если нечетное то Дефендер отбивается
	// цикл пока подкидывальщики могут подкинуть подкидывают )0)) а дефендер отбивается если может

	// здесь дефендер бьется
	_players[DefendPlayer].BeatOneCard(lastcard);


	while (_players[FirstPopUpPlayer].CanPopUp() || _players[SecondPopUpPlayer].CanPopUp())
	{
		//если на столе четное колличество карт то подкидывают одну карту
		CCard lastCard;
		CCard dropToTable;
		if (CTable::GetSize() % 2 == 0)
		{
			if (_players[FirstPopUpPlayer].CanPopUp())
				lastCard = DropToTableRandCard(_players[FirstPopUpPlayer]);
			else
				lastCard = DropToTableRandCard(_players[SecondPopUpPlayer]);
		}

		
		// если нечетное то бьется
		if (CTable::GetSize() % 2 != 0)
		{
			if (lastCard.GetSuit() == CTable::getTrump()) // если последняя карта на столе(которую подкинули), это козырь
			{
				dropToTable = _players[DefendPlayer].CanCoverASuit(lastCard); //возвращает карту
				_players[DefendPlayer].DropToTableCard(dropToTable);
			}
			else
			{
				dropToTable = dropToTable = _players[DefendPlayer].CanCoverNotASuit(lastCard, CTable::getTrump());
				_players[DefendPlayer].DropToTableCard(dropToTable);
			}
			if (dropToTable.GetNumb() == 0)
			{
				_players[DefendPlayer].TakeCardInHand();
			}
		}
	}
	
	
	
}


void TurnForTwoPlayers(vector<CPlayer>& _players, vector<CCard>& deck, const CPlayer& FirstTurnPlayer)
{
	if (deck.size() != 0)
		DistributionOfLakingCards(_players, deck); //раздаем карты кому не хватает




	int AttackPlayer = NumberOfPlayer(FirstTurnPlayer, _players) + 1;
	int DefendPlayer;

	if (AttackPlayer == _players.size())// задаем DefendPlayer
	{
		DefendPlayer = 0;
	}
	else
	{
		DefendPlayer = _players.size();
	}


	
	if (DefendPlayer == _players.size())
	{
		
		AttackPlayer = 0;
	}
	if (DefendPlayer == 0)
	{
		AttackPlayer = _players.size();
	}

	CCard lastcard = DropToTableRandCard(_players[AttackPlayer]); //здесь атакер кидает под дефуендера

	// сделать так, что если колличество карт на столе - четное значение, то кидает карту Подкидывающий 1 или 2(только одну), а если нечетное то Дефендер отбивается
	// цикл пока подкидывальщики могут подкинуть подкидывают )0)) а дефендер отбивается если может

	// здесь дефендер бьется
	_players[DefendPlayer].BeatOneCard(lastcard);

	CCard lastCard;
	CCard dropToTable;

	while (_players[AttackPlayer].CanPopUp())
	{
		//если на столе четное колличество карт то подкидывают одну карту
	
		if (CTable::GetSize() % 2 == 0)
		{
			if (_players[AttackPlayer].CanPopUp())
				lastCard = DropToTableRandCard(_players[AttackPlayer]);
		}


		// если нечетное то бьется
		if (CTable::GetSize() % 2 != 0)
		{
			if (lastCard.GetSuit() == CTable::getTrump()) // если последняя карта на столе(которую подкинули), это козырь
			{
				dropToTable = _players[DefendPlayer].CanCoverASuit(lastCard); //возвращает карту
				_players[DefendPlayer].DropToTableCard(dropToTable);
			}
			else
			{
				dropToTable = dropToTable = _players[DefendPlayer].CanCoverNotASuit(lastCard, CTable::getTrump());
				_players[DefendPlayer].DropToTableCard(dropToTable);
			}
			if (dropToTable.GetNumb() == 0)
			{
				_players[DefendPlayer].TakeCardInHand();
			}
		}
	}



}


