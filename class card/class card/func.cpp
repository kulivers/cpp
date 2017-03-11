#pragma once


#include "stdafx.h"
#include "card.h"
#include "table.h"
#include "player.h"
#include "Functions.h"

using namespace std;

CCard CTable::_cozir;

/*
ну слудующую функцию забывай - игроки кидают любую карту, и пуст это будет тип бито
и потом ход другого игрока - то же самое
и такипока колода не закончится                  
*/


void Discard(CTable& t, CPlayer& p1, CPlayer& p2)
{
	if (p1.EndTurn() && p2.EndTurn())
	{
		
	}
}
void SpreadCards(vector<CCard>& deck, CPlayer& p2)
{
	for (int p = 0; p < 6; p++) 
	{
		p2.add(deck.back());
		deck.pop_back();

	}
}

void ShowTrump(const CTable& t)
{
	cout << "Tramp is " << t.getTrump().GetAsString().c_str() << endl;
}


void Distribution(vector<CCard>& deck, CPlayer& p1, CPlayer& p2, CTable& t)//это не первый ход а  раздача
{
	SpreadCards(deck, p1);
	SpreadCards(deck, p2);
	p1.DisplayCards(p1);
	cout << endl;
	p2.DisplayCards(p2);
	t.setTrump(deck.back());
	deck.pop_back();
}

void FirstDrop(vector<CCard>& deck, CPlayer& p1, CPlayer& p2, CTable& t)
{
	if (p1.SmallestSuit(t.getTrump().GetSuit()) < p2.SmallestSuit(t.getTrump().GetSuit()))
		DropToTableRandCard(p1, t);
	else
		DropToTableRandCard(p2, t);

	if (p1.SmallestSuit(t.getTrump().GetSuit()) == p2.SmallestSuit(t.getTrump().GetSuit()))// если оба без козырей
		DropToTableRandCard(p1, t);//начинает первый, типо если будет онлайн игра то там все равно рандомно кто то первым будет
}




void DropToTableRandCard(CPlayer& p1, CTable& t)    
{
	CCard card = p1.GetRandomCard();
	p1.DeleteItem(card);
	t.PutOnTable(card);
	/*CCard c = p1.back();
	p1.pop_back();*/
}
