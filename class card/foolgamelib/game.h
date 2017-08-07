#pragma once

#include <iostream>
#include <cstdlib>
#include <locale.h> 
#include <vector>
#include <ctime>
#include <string.h>
#include <vector>
#include "card.h"
#include "player.h"
#include "table.h"


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

class CGame
{
private:
	enum Condition { StartOfTheGame, AfterDistribution, PlayerCanPopUp, PlayerCantPopUp, PlayerCanCoverCard, PlayerCantCoverCard, TheEndOfGame };
	static vector<CCard> _deck;
	static vector<CPlayer> _players;
	CTable _table;
	int AttackPlayer;
	int DefendPlayer;
public:

	CGame()
	{ }

	Condition condition;


	Condition SetCondition()
	{
		if (_deck.size() == 36)
			return StartOfTheGame;



		if (AllPlayersHaveSixCards(_players) == true && _deck.size() == (36 - 6 * _players.size()))
			return  AfterDistribution;

		
		if (_table.GetSize() != 0 && _table.GetSize() % 2 == 0 && _players[AttackPlayer].CanPopUp()==true)
			return  PlayerCanPopUp;

		if (_table.GetSize() != 0 && _table.GetSize() % 2 == 0 && _players[AttackPlayer].CanPopUp() == false)
			return  PlayerCantPopUp;
	
	
		if (_players[DefendPlayer].CanBeat(CTable::GetCard(CTable::GetSize())) == true)
			return  PlayerCanCoverCard;
	
		if (_players[DefendPlayer].CanBeat(CTable::GetCard(CTable::GetSize())) == false)
			return  PlayerCantCoverCard;

		if (AllPlayersHaveNoCards(_players) ==true)
			return  TheEndOfGame;
			
	}

};