// class card.cpp : Defines the entry point for the console application.CCard
//
#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <locale.h> 
#include <vector>
#include <ctime>
#include "card.h"
#include "table.h"
#include "player.h"
#include "Functions.h"



using namespace std;

/////////////////////////////////////////////////////////////

class CTable;
class CCard;
class CPlayer;

/////////////////////////////////////////////////////////////


/*��, ���, ��� ��������� � ����, ������ ���� ������� firstTurn ���� ��� CCard, � ���������� �� �� ��������
�������� CCard �� ����� ���� � �����, ������������
� ����� ������� ������ ����� � ���� h-���
� ������, �� ������ �� ������ ���� ��������� �����, �� � ��� ������ ��� ����������, ��� ��� ����� ����� ������ �������
� ���� �������� deck ��������, ��
deck.back() ������ ��������� �����
http://www.cplusplus.com/reference/vector/vector/back/
� deck.pop_back() ��������� ������ �� �� ������
http://www.cplusplus.com/reference/vector/vector/pop_..
� �� �� ����� �� deck ����, � ��� deck �� �������
������ ������� ���� ��������
������ �� ��������� - trump, �������, �� ��������)
��� ������� ������� ����� �� ����� ������ � ��������� ������� - ����� ��� ������ ����, �� �������
����-���� �����?) ������ ������� ���������, �������. ������ � ������ - ������ � ������� ����� (player.Add)
� ������ ����� - ��� ������, � ���������� - ���������������. ���������� save ������� �������, ����� saved ��� cardForPlayer ��� ������ card
����)*/




int main()
{
	setlocale(LC_ALL, "RUS");
	vector<CCard> deck(52);
	int j;
	cout << endl;
	for (j = 0; j < 52; j++)   // ������� ������������� ������ ����
	{
		int num = (j % 13) + 2;
		Suit su = Suit(j / 13);
		deck[j].set(num, su);
	}


	// ���������� �������� ������
	cout << "�������� ������:\n";
	for (j = 0; j < 52; j++)
	{
		cout << deck[j].GetAsString().c_str();
		cout << "  ";
		if (!((j + 1) % 13))      // �������� ����� ������ ����� ������ 13-� �����
			cout << endl;
	}
	srand(time(NULL));         // �������������� ��������� ��������� �����
	for (j = 0; j < 52; j++)
	{
		int k = rand() % 52;     // �������� ��������� �����
		CCard temp = deck[j];     // � ������ �� � �������
		deck[j] = deck[k];
		deck[k] = temp;
	}
	// ���������� �������� ������
	cout << " ������:\n";
	for (j = 0; j < 52; j++)
	{
		cout << deck[j].GetAsString().c_str();
		cout << "  ";
		if (!((j + 1) % 13))      // �������� ����� ������ ����� ������ 13-� �����
			cout << endl;
	}


	CPlayer player1, player2;
	CTable table;

	cout << endl;
	cout << endl;
	cout << endl;
	firstTurn(deck, player1, player2, table);



	cout << " ������:\n";
	for (j = 0; j < deck.size(); j++)
	{
		cout << deck[j].GetAsString().c_str();
		cout << "  ";
		if (!((j + 1) % 13))      // �������� ����� ������ ����� ������ 13-� �����
			cout << endl;
	}


	return 0;
}