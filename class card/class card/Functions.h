#pragma once

#include <vector>
#include "card.h"
#include "table.h"
#include "player.h"

using namespace std;


void SpreadCards(vector<CCard>& deck, CPlayer& p2);
void ShowTrump(const CTable& t);
void Distribution(vector<CCard>& deck, CPlayer& p1, CPlayer& p2);
CPlayer WhoPlaysFirst(vector<CCard>& deck, CPlayer& p1, CPlayer& p2, CTable& t);
bool RuleCanThrowUp(CCard card, CTable& t);
void DropToTableRandCard(CPlayer& p1, CTable& t);
void DropToTableCard(CCard card, CPlayer& p1, CTable& t);
void ClearTheBoard(CTable &t, vector<CCard> save);
bool TheEndOfGame(vector<CPlayer>& players);
void DistributionOfLakingCards(vector<CPlayer>& players, vector<CCard>& deck);
CPlayer WhoseTurn(vector<CPlayer>& players, CPlayer& lastP);