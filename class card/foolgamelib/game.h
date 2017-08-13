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




void SpreadCards(vector<CCard>& deck, CPlayer& p)        //������� ���� ������ ������
{
	while (p.GetSize() < 6 && !deck.empty())
	{
		p.add(deck.back());
		deck.pop_back();
	}
}

void ShowTrump(const CTable& t) // �������� ������
{
	cout << "Numb: " << t.getNumbOfTrump() << " Suit" << t.getTrump() << endl;
}



int WhoPlaysFirst(vector<CCard>& deck, vector<CPlayer>& _players, CTable& t)//��� ������ �����
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

bool RuleCanThrowUp(CCard card, CTable& t) // ����� ���������?
{
	for (int j = 0; j < t.GetSize(); j++)
	{
		if (card.GetNumb() == t.GetCard(j).GetNumb())
			return true;
		else
			return false;
	}
}

CCard DropToTableRandCard(CPlayer& p1)    //������ ��������� �����
{
	CCard card = p1.GetRandomCard();
	p1.DeleteItem(card);
	CTable::PutOnTable(card);
	/*CCard c = p1.back();
	p1.pop_back();*/

	return card;
}






void DistributionOfLakingCards(vector<CPlayer>& _players, vector<CCard>& deck)//������� ���� ��� � ���� �� �������
{
	CCard save;
	for (int i = 0; i < _players.size(); i++)//���� ��  �������
	{
		if (_players[i].GetSize() < 7)//���� ���-�� ���� � ������ �� ����� = 6
		{
			while (_players[i].GetSize() != 6)
			{
				if (deck.size() == 0)
					return;

				save = deck.back();
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

bool TheEndOfGame(const vector<CPlayer>& players, const vector<CCard>& deck)// �������� ������� ��� � ������ ���� ��� ����
{
	if (deck.size() != 0)
		return false;

	for (int i = 0; i < players.size(); i++)
	{
		if (!players[i].HasCards())
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




void Turn(vector<CPlayer>& _players, vector<CCard>& deck, int FirstTurnPlayer)//� ����� ����� ������� ����
{
	if (deck.size() != 0)
		DistributionOfLakingCards(_players, deck); //������� ����� ���� �� �������




	int AttackPlayer = FirstTurnPlayer + 1;
	int DefendPlayer;
	int FirstPopUpPlayer;
	int SecondPopUpPlayer;

	if (AttackPlayer == _players.size())// ������ DefendPlayer
	{
		DefendPlayer = 0;
	}
	else
	{
		DefendPlayer = AttackPlayer + 1;
	}


	////������ �������������
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

	CCard lastcard = DropToTableRandCard(_players[AttackPlayer]); //����� ������ ������ ��� ����������

	// ������� ���, ��� ���� ����������� ���� �� ����� - ������ ��������, �� ������ ����� ������������� 1 ��� 2(������ ����), � ���� �������� �� �������� ����������
	// ���� ���� ��������������� ����� ��������� ����������� )0)) � �������� ���������� ���� �����

	// ����� �������� ������
	_players[DefendPlayer].BeatOneCard(lastcard);


	while (_players[FirstPopUpPlayer].CanPopUp() || _players[SecondPopUpPlayer].CanPopUp())
	{
		//���� �� ����� ������ ����������� ���� �� ����������� ���� �����
		CCard lastCard;
		CCard dropToTable;
		if (CTable::GetSize() % 2 == 0)
		{
			if (_players[FirstPopUpPlayer].CanPopUp())
				lastCard = DropToTableRandCard(_players[FirstPopUpPlayer]);
			else
				lastCard = DropToTableRandCard(_players[SecondPopUpPlayer]);
		}


		// ���� �������� �� ������
		if (CTable::GetSize() % 2 != 0)
		{
			if (lastCard.GetSuit() == CTable::getTrump()) // ���� ��������� ����� �� �����(������� ���������), ��� ������
			{
				dropToTable = _players[DefendPlayer].CanCoverASuit(lastCard); //���������� �����
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


void TurnForTwoPlayers(vector<CPlayer>& _players, vector<CCard>& deck, int AttackPlayer)
{
	if (deck.size() != 0)
		DistributionOfLakingCards(_players, deck); //������� ����� ���� �� �������



	int DefendPlayer;

	if (AttackPlayer == 1)// ������ DefendPlayer
	{
		DefendPlayer = 0;
	}
	else
	{
		DefendPlayer = 1;
	}



	CCard lastcard = DropToTableRandCard(_players[AttackPlayer]); //����� ������ ������ ��� ���������� 
	cout << "����� " << AttackPlayer + 1 << " ������ �� ����: " << lastcard.GetNumb() << " " << lastcard.GetSuit() << endl;

	// ������� ���, ��� ���� ����������� ���� �� ����� - ������ ��������, �� ������ ����� ������������� 1 ��� 2(������ ����), � ���� �������� �� �������� ����������
	// ���� ���� ��������������� ����� ��������� ����������� )0)) � �������� ���������� ���� �����

	// ����� �������� ������

	cout << "����� " << DefendPlayer + 1 << " ������ �� ����: ";
	_players[DefendPlayer].BeatOneCard(lastcard);//��
	CCard dropToTable;



	while (_players[AttackPlayer].CanPopUp()) //����� c�������������� ����
	{
		//���� �� ����� ������ ����������� ���� �� ����������� ���� �����


		if (CTable::GetSize() % 2 == 0)
		{
			if (CTable::GetSize() == 0)   // ���� ������ ��� ���� �� ������� 
				break;
			else
			{
				lastcard = DropToTableRandCard(_players[AttackPlayer]);// ����� ��� ����� ���������� �� ������� �����, � �� ���������
			}
		}


		// ���� �������� �� ������
		if (CTable::GetSize() % 2 != 0)
		{
			if (lastcard.GetSuit() == CTable::getTrump()) // ���� ��������� ����� �� �����(������� ���������), ��� ������
			{
				dropToTable = _players[DefendPlayer].CanCoverASuit(lastcard); //���������� �����      
				_players[DefendPlayer].DropToTableCard(dropToTable);
			}
			else
			{
				dropToTable = dropToTable = _players[DefendPlayer].CanCoverNotASuit(lastcard, CTable::getTrump());
				_players[DefendPlayer].DropToTableCard(dropToTable);
			}
			if (dropToTable.GetNumb() == 0)
			{
				_players[DefendPlayer].TakeCardInHand();
			}
		}
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



class CGame
{
private:
	enum Condition { StartOfTheGame, AfterDistribution, PlayerCanPopUp, PlayerCantPopUp, PlayerCanCoverCard, PlayerCantCoverCard, TheEndOfGame }
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


	
};