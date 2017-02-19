#pragma once
#include "stdafx.h"
#include <stdio.h>
#include "func.cpp"

void SpreadCards(vector<CCard>& deck, CPlayer& p2);
void ShowTrump(const CTable& t);
void CPlayer::DisplayCards(CPlayer p1);
string CCard::GetAsString() const;