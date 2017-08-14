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




void SpreadCards(vector<CCard>& deck, CPlayer& p2);
void ShowTrump(const CTable& t);
void Distribution(vector<CPlayer>& _players, vector<CCard>& deck);
int WhoPlaysFirst(vector<CCard>& deck, vector<CPlayer>& _players, CTable& t);
bool RuleCanThrowUp(CCard card, CTable& t);
CCard DropToTableRandCard(CPlayer& p1, CTable& t);

void ClearTheBoard(CTable &t, vector<CCard> save);
void DistributionOfLakingCards(vector<CPlayer>& players, vector<CCard>& deck);
CPlayer WhoseTurn(vector<CPlayer>& players, CPlayer& lastP);



void Turn(vector<CPlayer>& _players, vector<CCard>& deck, int FirstTurnPlayer);//в цикле после первого хода
void TurnForTwoPlayers(vector<CPlayer>& _players, vector<CCard>& deck, int FirstTurnPlayer);
bool AllPlayersHaveSixCards(vector<CPlayer> _players);
bool AllPlayersHaveNoCards(vector<CPlayer> _players);


class CGame
{
private:
	enum Condition { StartOfTheGame, AfterDistribution, PlayerCanPopUp, PlayerCantPopUp, PlayerCanCoverCard, PlayerCantCoverCard, TheEndOfGame };
	/*static vector<CCard> _deck;
	static vector<CPlayer> _players;
	static CTable _table;
	int AttackPlayer;
	int DefendPlayer;*/
public:

	CGame()
	{ }

	/* void setAandD(int a, int d)
	{
		AttackPlayer = a;
		DefendPlayer = d;
	}

	static void SetItems(vector<CCard> deck, vector<CPlayer> players, CTable table, int attackPlayer, int defendPlayer)
	{
		_deck = deck;
		_players = players;
		_table.setTrump(table.getTrumpCard()); 
	}*/

	Condition condition;
	static vector<CCard> _deck;
	static vector<CPlayer> _players;
	static CTable _table;
	int AttackPlayer;
	int DefendPlayer;

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

		if (AllPlayersHaveNoCards(_players) == true)
			return  TheEndOfGame;
			
	}
	static bool TheEndOfGame(const vector<CPlayer>& players, const vector<CCard>& deck);

	
};