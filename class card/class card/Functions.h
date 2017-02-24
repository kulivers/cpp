#pragma once

#include <vector>
#include "classes.h"

void firstTurn(std::vector<CCard>& deck, CPlayer& p1, CPlayer& p2, CTable& t);
void SpreadCards(std::vector<CCard>& deck, CPlayer& p2);
void ShowTrump(const CTable& t);

