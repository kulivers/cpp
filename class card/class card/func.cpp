#pragma once


#include "stdafx.h"
#include "card.h"
#include "table.h"
#include "player.h"
#include "Functions.h"

using namespace std;

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


void firstTurn(vector<CCard>& deck, CPlayer& p1, CPlayer& p2, CTable& t)
{
	SpreadCards(deck, p1);
	SpreadCards(deck, p2);
	p1.DisplayCards(p1);
	cout << endl;
	p2.DisplayCards(p2);
	t.setTrump(deck.back());
	deck.pop_back();



}
