// class card.cpp : Defines the entry point for the console application.CCard
//

#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <locale.h> 
#include <vector>
#include <ctime>
using namespace std;



enum Suit { clubs, diamonds, hearts, spades };
// от 2 до 10 обычные числа


const int jack = 11;
const int queen = 12;
const int king = 13;
const int ace = 14;


/////////////////////////////////////////////////////////////




class CCard
{
private:
	int _number;
	Suit _suit;
public:
	CCard()                   // конструктор
	{ }
	void set(int n, Suit s)  // установка значения
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
	CPlayer()                   // конструктор
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
	CCard _cozir;// карта которая лежит под колодой
public:
	CTable()                   // конструктор
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

void SpreadCards(vector<CCard>& deck, CPlayer& p2)
{
	for (int p = 0; p < 6; p++)  // раздача второму
	{
		p2.add(deck.back());
		deck.pop_back();// чтобы карты в колоде уменьшались

	}
}

void ShowTrump(const CTable& t)
{
	cout << "Tramp is " << t.getTrump().GetAsString().c_str() << endl;
}


void firstTurn(vector<CCard>& deck, CPlayer& p1, CPlayer& p2, CTable& t)
{
	SpreadCards(deck,  p1);
	SpreadCards(deck,  p2);
	p1.DisplayCards(p1);
	cout << endl;
	p2.DisplayCards(p2);
	t.setTrump(deck.back());
	deck.pop_back();
	


}


/////////////////////////////////////////////////////////////

void CPlayer::DisplayCards(CPlayer p1)
{
	for (int i = 0; i < p1._cardsInHand.size(); i++)
	{
		
		cout << p1._cardsInHand[i].GetAsString().c_str() << " " << endl;
	}
}

string CCard::GetAsString() const
{
	string result;
	if (_number >= 2 && _number <= 10)
		result = '0' + _number;
	else
	{
		switch (_number)
		{
		case jack:  result = 'J'; break;
		case queen: result = 'Q'; break;
		case king:  result = 'K'; break;
		case ace:   result = 'A'; break;
		}
	}
	switch (_suit)
	{
	case clubs:    result += 'c'; break;
	case diamonds: result += 'd'; break;
	case hearts:   result += 'h'; break;
	case spades:   result += 's'; break;
	}

	return result;
}
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
