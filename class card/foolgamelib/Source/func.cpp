#pragma once


#include "stdafx.h"
#include <algorithm>
#include <iterator>


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
std::vector <CCard> CTable::_cardsOnTable;






int main()
{
	return 0;
};