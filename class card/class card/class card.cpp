﻿// class card.cpp : Defines the entry point for the console application.CCard
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


/*аа, нее, все правильно у тебя, просто сама функция firstTurn выше чем CCard, и компилятор ее не понимает
перетащи CCard на самый верх в файле, скомпилиться
а лучше растащи каждый класс в свой h-ник
и смотри, ты берешь из колоды одну случайную карту, но у нас колода уже перемешана, так что можно брать просто верхнюю
а если сделаешь deck вектором, то
deck.back() вернет последнюю карту
http://www.cplusplus.com/reference/vector/vector/back/
а deck.pop_back() аккуратно удалит ее из колоды
http://www.cplusplus.com/reference/vector/vector/pop_..
а то ты карту из deck взял, а сам deck не изменил
только счетчик карт уменьшил
козырь по английски - trump, поменяй, не позорься)
код который выводит карты на экран вынеси в отдельную функцию - даешь ему вектор карт, он выводит
чего-нить понял?) вопщем неплохо нарисовал, молодец. Методы в классе - всегда с большой буквы (player.Add)
и обычно метод - это глагол, а переменная - существительная. Переменная save странно названа, лучше saved или cardForPlayer или просто card
вотЪ)*/


int main()
{
	setlocale(LC_ALL, "RUS");
	//SetConsoleCP(1251);// установка кодовой страницы win-cp 1251 в поток ввода (CP_UTF8)
	//SetConsoleOutputCP(1251); // установка кодовой страницы win-cp 1251 в поток вывода
	//system("chcp 1251");

	const int deckSize = 17;
	vector<CCard> deck(deckSize);
	int j;
	cout << endl;
	for (j = 0; j < deck.size(); j++)   // создаем упорядоченную колоду карт
	{
		int num = (j % 13) + 2;
		Suit su = Suit(j / 13);
		deck[j].set(num, su);
	}

	// показываем исходную колоду
	cout << "Исходная колода:\n";
	for (j = 0; j < deck.size(); j++)
	{
		cout << deck[j].GetAsString().c_str();
		cout << "  ";
		if (!((j + 1) % 13))      // начинаем новую строку после каждой 13-й карты
			cout << endl;
	}
	cout << endl;

	srand(time(NULL));         // инициализируем генератор случайных чисел
	for (j = 0; j < deck.size(); j++)
	{
		int k = rand() % deck.size();     // выбираем случайную карту
		CCard temp = deck[j];     // и меняем ее с текущей
		deck[j] = deck[k];
		deck[k] = temp;
	}
	// показываем исходную колоду
	cout << "колода до раздачи:\n";
	for (j = 0; j < deck.size(); j++)
	{
		cout << deck[j].GetAsString().c_str();
		cout << "  ";
		if (!((j + 1) % 13))      // начинаем новую строку после каждой 13-й карты
			cout << endl;
	}
	cout << endl;




	CTable table;
	vector<CPlayer> _players(2);

	cout << endl;
	cout << endl;
	cout << endl;

	Distribution(_players, deck);


	/*	cout << " колода после раздачи: " << endl;
		for (j = 0; j < deck.size(); j++)
		{
		cout << deck[j].GetAsString().c_str();
		cout << "  ";
		if (!((j + 1) % 13))      // начинаем новую строку после каждой 13-й карты
		cout << endl;
		}
		cout << endl;
		*/

	cout << "Раздача" << endl;
	for (int i = 0; i < _players.size(); i++) // 
	{
		cout << i + 1 << "й игрок: " << endl;
		_players[i].DisplayCards();
		cout << endl << endl;
	}


	cout << "козырь:  clubs, diamonds, hearts, spades-----------";
	ShowTrump(table);
	cout << endl;


	int numbOfTurn = 0;
	int AttackPlayer;
	int DefendPlayer;

	while (TheEndOfGame(_players) != true)
	{

			if (numbOfTurn == 0)
		{
			AttackPlayer = WhoPlaysFirst(deck, _players, table);
			cout << "Начало" << numbOfTurn + 1 << "го хода" << endl;

			TurnForTwoPlayers(_players, deck, AttackPlayer);

			for (int i = 0; i < _players.size(); i++)
			{
				cout << i + 1 << "й игрок: " << endl;
				_players[i].DisplayCards();
				cout << endl;
			}

			cout << "Конец хода" << endl;
			numbOfTurn++;

			if (AttackPlayer == 1)// меняем
				DefendPlayer = 0;
			else
				DefendPlayer = 1;

			if (DefendPlayer == 1)// меняем
				AttackPlayer = 0;
			else
				AttackPlayer = 1;
			table.ClearTheBoard();
			//_getch();

		}
		else
		{
			cout << "Начало" << numbOfTurn + 1 << "го хода" << endl;

			TurnForTwoPlayers(_players, deck, AttackPlayer); //ЗДЕСЬ

			for (int i = 0; i < _players.size(); i++)
			{
				cout << i + 1 << "й игрок: " << endl;
				_players[i].DisplayCards();
				cout << endl;
			}
			cout << "Конец хода" << endl;

			if (AttackPlayer == 1)// меняем
				DefendPlayer = 0;
			else
				DefendPlayer = 1;

			if (DefendPlayer == 1)// меняем
				AttackPlayer = 0;
			else
				AttackPlayer = 1;
		}


			table.ClearTheBoard();
	}
	cout << endl;
	return 0;
}