#pragma once

#include <vector>
#include "card.h"
#include "table.h"
#include "player.h"

using namespace std;


void Distribution(std::vector<CCard>& deck, CPlayer& p1, CPlayer& p2, CTable& t);
void SpreadCards(std::vector<CCard>& deck, CPlayer& p2);
void ShowTrump(const CTable& t);
void DropToTableRandCard(CPlayer& p1, CTable& t);
void FirstDrop(vector<CCard>& deck, CPlayer& p1, CPlayer& p2, CTable& t);