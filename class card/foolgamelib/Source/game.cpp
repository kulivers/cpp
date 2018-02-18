#pragma once


#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <iterator>
#include "card.h"
#include "table.h"
#include "player.h"
#include "game.h"

using namespace std;

/*
ну слудующую функцию забывай - игроки кидают любую карту, и пуст это будет тип бито
и потом ход другого игрока - то же самое
и такипока колода не закончится
*/
CCard CTable::_cozir;
std::vector <CCard> CTable::_cardsOnTable;

CGame::Condition CGame::condition;
vector<CCard> CGame::_deck;
vector<CPlayer> CGame::_players;
CTable CGame::_table;
int CGame::AttackPlayer;
int CGame::DefendPlayer;
int CGame::NumberOfTurn;

void SpreadCards(vector<CCard>& deck, CPlayer& p)        //раздача карт одному игроку
{
	while (p.GetSize() < 6 && !deck.empty())
	{
		p.add(deck.back());
		deck.pop_back();
	}
}

//void ShowTrump(const CTable& t) // показать козырь
//{
//	if (t.getNumbOfTrump() < 11 )
//		cout << t.getNumbOfTrump() << " " ;
//	
//	if (t.getNumbOfTrump() == 11)
//		cout << "jack " ;
//	if (t.getNumbOfTrump() == 12)
//		cout << "queen ";
//	if (t.getNumbOfTrump() == 13)
//		cout << "king ";
//	if (t.getNumbOfTrump() == 14)
//		cout << "ace ";
//
//
//
//	if (t.getTrump() == clubs)
//		cout << "clubs" << endl;
//
//	if (t.getTrump() == diamonds)
//		cout << "diamonds" << endl;
//
//	if (t.getTrump() == hearts)
//		cout << "hearts" << endl;
//
//	if (t.getTrump() == spades)
//		cout << "spades" << endl;
//
//
//
//}



int WhoPlaysFirst(vector<CCard>& deck, vector<CPlayer>& _players, CTable& t)//кто первый ходит
{
	int index;

	int minSuit = 999;
	for (int i = 0; i < _players.size(); i++)
	{
		if (_players[i].SmallestSuit(CTable::getTrump()) < minSuit)
		{
			minSuit = _players[i].SmallestSuit(CTable::getTrump());
			index = i;
		}
	}
	return index;
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
				if (deck.size() == 0)
					return;

				if (deck.size() != 0)
				{
				save = deck.back();
				deck.pop_back();
				_players[i].add(save);
				}
			}
		}
	}
}


void Distribution(vector<CPlayer>& _players, vector<CCard>& deck)
{
	CTable::setTrump(deck.front());
	DistributionOfLakingCards(_players, deck);
}

 bool CGame::IsTheEndOfGame(const vector<CPlayer>& players, const vector<CCard>& deck)// добавить условие что в колоде тоже нет карт
{
	if (deck.size() != 0)
		return false;

	for (int i = 0; i < players.size(); i++)
	{
		if (!(players[i].HasCards()) && _deck.size() == 0)
			return true;
	}

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






bool AllPlayersHaveSixCards(vector<CPlayer> _players)
{
	for (int i = 0; i < _players.size(); i++)
	{
		if (_players[i].GetSize() != 6)
			return false;
	}
	return true;
}

bool AllPlayersHaveNoCards(vector<CPlayer> _players)
{
	for (int i = 0; i < _players.size(); i++)
	{
		if (_players[i].GetSize() != 0)
			return false;
	}
	return true;
}


bool PlayersHaveNotEnoughCards(vector<CPlayer> _players)
{
	for (int i = 0; i < _players.size(); i++)
	{
		if (_players[i].GetSize() < 6)
			return true;
	}
	return false;
}


static void CleaningResurses()
{
	CGame::_deck.clear();
	CGame::_players.clear();
	CGame::_table.ClearTheBoard();
	CGame::_players.push_back(CPlayer());
	CGame::_players.push_back(CPlayer());

}


static void ChangeAttackerAndDefender()
{
	if (CGame::AttackPlayer == 0)
		
		CGame::DefendPlayer = 1;
	else
	{ 
	CGame::AttackPlayer = 1;
	CGame::DefendPlayer = 0;
	}
}



static void MakeAndShowDeck()
{

	static const  int deckSize = 36;
	int j;
	for (j = 0; j < deckSize; j++)   // создаем упорядоченную колоду карт
	{
		int num = (j % 13) + 2;
		Suit su = Suit(j / 13);
		CGame::_deck.push_back(CCard(num, su));

	}


	// показываем исходную колоду
	cout << "Исходная колода:\n";
	for (j = 0; j < CGame::_deck.size(); j++)
	{
		cout << CGame::_deck[j].GetAsString().c_str();
		cout << "  ";
		if (!((j + 1) % 13))      // начинаем новую строку после каждой 13-й карты
			cout << endl;
	}
	cout << endl;

	srand(time(NULL));         // инициализируем генератор случайных чисел
	for (j = 0; j < CGame::_deck.size(); j++)
	{
		int k = rand() % CGame::_deck.size();     // выбираем случайную карту
		CCard temp = CGame::_deck[j];     // и меняем ее с текущей
		CGame::_deck[j] = CGame::_deck[k];
		CGame::_deck[k] = temp;
	}
	// показываем исходную колоду
	cout << "колода до раздачи:\n";
	for (j = 0; j < CGame::_deck.size(); j++)
	{
		cout << CGame::_deck[j].GetAsString().c_str();
		cout << "  ";
		if (!((j + 1) % 13))      // начинаем новую строку после каждой 13-й карты
			cout << endl;
	}

	cout << endl;
	cout << "Trump: ";

	switch (CGame::_table.getTrump())//enum Suit { clubs, diamonds, hearts, spades };
	{
	case 0:
	{
		cout << "clubs";
		break;
	}

	case 1:
	{
		cout << "diamonds";
		break;
	}

	case 2:
	{
		cout << "hearts";
		break;
	}

	case 3:
	{
		cout << "spades";
		break;
	}


	}
	cout << endl;
	cout << endl;

}
	


int b_main()
{
	return 0;
}