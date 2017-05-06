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
	cout << "Tramp is " << t.getTrump().GetAsString().c_str() << endl;
}



CPlayer WhoPlaysFirst(vector<CCard>& deck, CPlayer& p1, CPlayer& p2, CTable& t)//кто первый ходит
{
	if (p1.SmallestSuit(t.getTrump().GetSuit()) < p2.SmallestSuit(t.getTrump().GetSuit()))
		return p1;
	else
		return p2;

	if (p1.SmallestSuit(t.getTrump().GetSuit()) == p2.SmallestSuit(t.getTrump().GetSuit()))// если оба без козырей
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

void DropToTableRandCard(CPlayer& p1, CTable& t)    //кидает рандомную карту
{
	CCard card = p1.GetRandomCard();
	p1.DeleteItem(card);
	t.PutOnTable(card);
	/*CCard c = p1.back();
	p1.pop_back();*/
}

void DropToTableCard(CCard card, CPlayer& p1, CTable& t)    //кидает определенную карту
{
	p1.DeleteItem(card);
	t.PutOnTable(card);
	/*CCard c = p1.back();
	p1.pop_back();*/
}



CPlayer WhoseTurn(vector<CPlayer>& players, CPlayer& lastP)                         //удалить можно
{ 
	int IndxOfLast;
	for (int i = 0; i < players.size(); i++)//находим чей ход
	{
		for (int j = 0; j < players[i].GetSize(); i++)
		{
			if (players[i].GetCardC(j) == lastP.GetCardC(j))// если хоть одна карта совпадает то это тот игрок

				IndxOfLast = i;
		}
	}
	return players[IndxOfLast + 1];
}


void DistributionOfLakingCards(vector<CPlayer>& players, vector<CCard>& deck)//раздача карт тем у кого не хватает
{
	for (int i = 0; i < players.size(); i++)
	{
		if (players.size() < 7)
		{
			while (players.size() == 6)
			{
				CCard save;
				save.set(deck[0].GetNumb(), deck[0].GetSuit()); //правильно что 0?
				deck.erase(deck.begin());						// и здесь
				players[i].add(save);
			}
		}
	}
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




void Turn(vector<CPlayer>& _players, vector<CCard>& deck, CTable& t, CPlayer FirstTurnPlayer)//в цикле после первого хода
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

	DropToTableRandCard(_players[AttackPlayer], t); //здесь атакер кидает под дефуендера

	// сделать так, что если колличество карт на столе - четное значение, то кидает карту Подкидывающий 1 или 2(только одну), а если нечетное то Дефендер отбивается
	// цикл пока подкидывальщики могут подкинуть подкидывают )0)) а дефендер отбивается если может


	while (_players[FirstPopUpPlayer].CanPopUp(t) || _players[SecondPopUpPlayer].CanPopUp(t))
	{
		//если на столе четное колличество карт то подкидывают одну карту

		if (t.GetSize() % 2 == 0)
		{
			if (_players[FirstPopUpPlayer].CanPopUp(t))
				DropToTableRandCard(_players[FirstPopUpPlayer], t);
			else
				DropToTableRandCard(_players[SecondPopUpPlayer], t);
		}

		// если нечетное то бьется
		if (t.GetSize() % 2 != 0)
		{
			if (t.GetCard(t.GetSize()).GetSuit() == t.getTrump()) // если последняя карта на столе(которую подкинули), это козырь
			{
				_players[FirstPopUpPlayer].CanCoverASuit(); //возвращает карту
			}
		}
	}
	
	
	
}
