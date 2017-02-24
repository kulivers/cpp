#pragma once
#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <locale.h> 
#include <vector>
#include <ctime>
#include <string.h>
#include <vector>

class CCard
{
private:
	int _number;
	Suit _suit;
public:
	CCard()                   // �����������
	{ }
	void set(int n, Suit s)  // ��������� ��������
	{
		_suit = s; _number = n;
	}
	string GetAsString() const;

};


class CPlayer
{
private:
	vector <CCard> _cardsInHand;
public:
	CPlayer()                   // �����������
	{ }

	void add(CCard n)  // 
	{
		_cardsInHand.push_back(n);
	}
	void DisplayCards(CPlayer p1);
	~CPlayer()
	{}

};


class CTable
{
private:
	vector <CCard> _cardsOnTable;
	CCard _cozir;// ����� ������� ����� ��� �������
public:
	CTable()                   // �����������
	{ }
	void setTrump(CCard v)
	{
		_cozir = v;
	}

	CCard getTrump() const
	{
		return _cozir;
	}
	~CTable()
	{ }

};
