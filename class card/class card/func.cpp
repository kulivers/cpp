#pragma once


#include "stdafx.h"
#include "card.h"
#include "table.h"
#include "player.h"
#include "Functions.h"

using namespace std;

/*
ну слудующую функцию забывай - игроки кидают любую карту, и пуст это будет тип бито
и потом ход другого игрока - то же самое
и такипока колода не закончится                  
*/
CCard CTable::_cozir;


void SpreadCards(vector<CCard>& deck, CPlayer& p2)//раздача карт одному игроку
{
	for (int p = 0; p < 6; p++) 
	{
		p2.add(deck.back());
		deck.pop_back();

	}
}

void ShowTrump(const CTable& t) // показать козырь
{
	cout << "Tramp is " << t.getTrump().GetAsString().c_str() << endl;
}


void Distribution(vector<CCard>& deck, CPlayer& p1, CPlayer& p2, CTable& t)        //это не первый ход а  раздача
{
	SpreadCards(deck, p1);
	SpreadCards(deck, p2);
	p1.DisplayCards(p1);
	cout << endl;
	p2.DisplayCards(p2);
	t.setTrump(deck.back());
	deck.pop_back();
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
		for (int j = 0; j < t.AmountCardsOnTable(); j++)
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

void DropToTableCard(CCard card, CPlayer& p1, CTable& t)    //кидает карту
{
	p1.DeleteItem(card);
	t.PutOnTable(card);
	/*CCard c = p1.back();
	p1.pop_back();*/
}

CCard CanCoverASuit(CCard card, CPlayer& p1, Suit trump)// может побить козырь?
{
	CCard save;
	vector<CCard> CanCover; //козыря больше нашего, выберем наименьший
	save.set(0, trump); // если есть козыря но не может побить то вернется ето
		if (p1.HasTrump(trump) == true)// у игрока есть козыря?
		{
			for (int i = 0; i < p1.GetSize(); i++)
			{
				if (card.GetNumb() > p1.GetNumbC(i))
				save.set(p1.GetNumbC(i), p1.GetSuitC(i));
				CanCover.push_back(save);
			}
		}
		int minSuit = 1000;
		for (int i = 0; i < CanCover.size(); i++)//выбираем наименьший
		{
			if (minSuit < CanCover[i].GetNumb())
				minSuit = CanCover[i].GetNumb();
		}
		save.set(minSuit, trump);
		return save;
}// возвращает карту с 0 номером если не может

CCard CanCoverNotASuit(CCard card, CPlayer& p1, Suit trump)// может побить не козырь ? 
{
	CCard save;
	save.set(0, trump); // если есть козыря но не может побить то вернется ето
	vector<CCard> CanCover;  // карты которыми мы можем покрыть (не козыря) сначала, а потом елси таких нет, пихаем туда все козыря и ищем наименьший
	for (int i = 0; i < p1.GetSize(); i++)
	{
		if (p1.GetNumbC(i) > card.GetNumb() && p1.GetSuitC(i) == card.GetSuit())
			CanCover.push_back(p1.GetCardC(i));
	}
	
	//numbers.empty()=1 если вектор пустой
	if (CanCover.size() == 0)// ищем козыря
	{
		for (int i = 0; i < p1.GetSize(); i++)
		{
			if (p1.GetSuitC(i) == trump)
				CanCover.push_back(p1.GetCardC(i));
		}

		int minSuit = 1000;
		for (int i = 0; i < CanCover.size(); i++)//выбираем наименьший
		{
			if (minSuit < CanCover[i].GetNumb())
				minSuit = CanCover[i].GetNumb();
		}
		save.set(minSuit, trump);
	}
	else// если можно побить не козырем                        //здесь начал тупить, ниже проверить
	{
		int minNumb = 1000;
		for (int i = 0; i < CanCover.size(); i++)//выбираем наименьший
		{
			if (CanCover[i].GetNumb() < minNumb)
				minNumb = CanCover[i].GetNumb();
		}
		save.set(minNumb, card.GetSuit());		
	}
	
	return save;// возвращает карту с 0 номером если не может

}

void ClearTheBoard(CTable &t, vector<CCard> save)// бито
{
	CCard saveC;
	for (int i = 0; i < t.GetSize(); i++)
	{
		saveC = t.GetCard(i);
		t.DeleteItem(saveC);
		save.push_back(saveC);
	}
}