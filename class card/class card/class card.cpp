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
	vector<CCard> deck(52);
	int j;
	cout << endl;
	for (j = 0; j < 52; j++)   // создаем упорядоченную колоду карт
	{
		int num = (j % 13) + 2;
		Suit su = Suit(j / 13);
		deck[j].set(num, su);
	}


	// показываем исходную колоду
	cout << "Исходная колода:\n";
	for (j = 0; j < 52; j++)
	{
		cout << deck[j].GetAsString().c_str();
		cout << "  ";
		if (!((j + 1) % 13))      // начинаем новую строку после каждой 13-й карты
			cout << endl;
	}
	srand(time(NULL));         // инициализируем генератор случайных чисел
	for (j = 0; j < 52; j++)
	{
		int k = rand() % 52;     // выбираем случайную карту
		CCard temp = deck[j];     // и меняем ее с текущей
		deck[j] = deck[k];
		deck[k] = temp;
	}
	// показываем исходную колоду
	cout << " колода:\n";
	for (j = 0; j < 52; j++)
	{
		cout << deck[j].GetAsString().c_str();
		cout << "  ";
		if (!((j + 1) % 13))      // начинаем новую строку после каждой 13-й карты
			cout << endl;
	}


	CPlayer player1, player2;
	CTable table;

	cout << endl;
	cout << endl;
	cout << endl;
	firstTurn(deck, player1, player2, table);



	cout << " колода:\n";
	for (j = 0; j < deck.size(); j++)
	{
		cout << deck[j].GetAsString().c_str();
		cout << "  ";
		if (!((j + 1) % 13))      // начинаем новую строку после каждой 13-й карты
			cout << endl;
	}


	return 0;
}