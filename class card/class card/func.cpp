#pragma once




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
	SpreadCards(deck, p1);
	SpreadCards(deck, p2);
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