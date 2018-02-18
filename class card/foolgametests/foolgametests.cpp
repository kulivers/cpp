// foolgametests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "player.h"
#include "game.h"


TEST_CASE("getOneBit")
{
	uint8_t data[1];

	data[0] = 1;

	data[0] = 1 << 7;
	REQUIRE(1 == true);
}


SCENARIO("Add card to player and delete it")
{
	GIVEN("Player with one card")
	{
		CCard card;
		card.set(10, Suit::clubs);
		CPlayer player;
		player.add(card);

		REQUIRE(1 == player.GetSize());

		WHEN("we delete a card")
		{
			player.DeleteItem(card);

			THEN("no cards are in player's hand")
			{
				REQUIRE(0 == player.GetSize());
			}
		}
	}
}

vector<CCard> GetSixClubs()
{
	vector<CCard> result(6);
	result[0].set(6, Suit::clubs);
	result[1].set(7, Suit::clubs);
	result[2].set(8, Suit::clubs);
	result[3].set(9, Suit::clubs);
	result[4].set(10, Suit::clubs);
	result[5].set(11, Suit::clubs);

	return result;
}

vector<CCard> GetSixDiamonds()
{
	vector<CCard> result(6);
	result[0].set(6, Suit::diamonds);
	result[1].set(7, Suit::diamonds);
	result[2].set(8, Suit::diamonds);
	result[3].set(9, Suit::diamonds);
	result[4].set(10, Suit::diamonds);
	result[5].set(11, Suit::diamonds);

	return result;
}

SCENARIO("Find a player who plays first when only the second has the trump")
{
	GIVEN("Two players but only one with trump card")
	{
		CTable t; //not used at all, why is it in parameters?
		vector<CCard> deck; //not used at all, why is it in parameters?
		vector<CPlayer> players;

		GIVEN("Trump is hearts")
		{
			CCard trump;
			trump.set(10, Suit::hearts);
			t.setTrump(trump);
			{
				GIVEN("One player with six clubs")
				{
					players.push_back(CPlayer());
					auto cards = GetSixClubs();
					for (auto cardIt = cards.begin(); cardIt != cards.end(); cardIt++)
						players.back().add(*cardIt);

					WHEN("Another player with five diamonds and one heart")
					{
						players.push_back(CPlayer());
						cards = GetSixDiamonds();
						cards.back().set(6, Suit::hearts);

						for (auto cardIt = cards.begin(); cardIt != cards.end(); cardIt++)
							players.back().add(*cardIt);

						THEN("The second of them should move first")
						{
							REQUIRE(WhoPlaysFirst(deck, players, t) == 1);
						}
					}
				}
			}
		}
	}
}


SCENARIO("CanCoverASuit test")
{
	GIVEN("suit =0    ||    6 0 on the table   ||   player has hards: 5 0, 7 1, 8 3, 7 0, 10 0")
	{
		CPlayer player;
		CCard card(6, clubs);
		CCard trump(13, clubs);
		CTable table;
		table.setTrump(trump);
		player.add(CCard(5, clubs));
		player.add(CCard(7, diamonds));
		player.add(CCard(8, diamonds));
		player.add(CCard(7, clubs));
		player.add(CCard(10, clubs));

		player.CanCoverASuit(card);

		WHEN("Covered")
		{
			THEN("CanCoverASuit = 7, clubs")
			{
				{
					REQUIRE(player.CanCoverASuit(card) == CCard(7, clubs));
				}
			}
		}
	}
}





SCENARIO("Find a player who plays first when both have the trump")
{
	GIVEN("Two players but only one with 6th of trump card")
	{
		CTable t; //not used at all, why is it in parameters?
		vector<CCard> deck; //not used at all, why is it in parameters?
		vector<CPlayer> players;

		GIVEN("Trump is hearts")
		{
			CCard trump;
			trump.set(10, Suit::hearts);
			t.setTrump(trump);
			{
				GIVEN("One player with five clubs and 9th of heart")
				{
					players.push_back(CPlayer());
					auto cards = GetSixClubs();
					cards[4].set(9, Suit::hearts);
					for (auto cardIt = cards.begin(); cardIt != cards.end(); cardIt++)
						players.back().add(*cardIt);

					WHEN("Another player with five diamonds and one heart")
					{
						players.push_back(CPlayer());
						cards = GetSixDiamonds();
						cards.back().set(6, Suit::hearts);

						for (auto cardIt = cards.begin(); cardIt != cards.end(); cardIt++)
							players.back().add(*cardIt);

						THEN("The second of them should move first")
						{
							REQUIRE(WhoPlaysFirst(deck, players, t) == 1);
						}
					}
				}
			}
		}
	}
}


SCENARIO("When player is empty, but deck is not empty")
{
	GIVEN("player is empty,  deck is not empty ")
	{
		vector<CPlayer> players;
		players.push_back(CPlayer());
		players.push_back(CPlayer());
		vector<CCard> deck;
		deck.push_back(CCard(6, clubs));
		



		WHEN("End Of Game")
		{
			THEN("Func = true")
			{
				{
					REQUIRE(CGame::IsTheEndOfGame(players, deck) == false);
				}
			}
		}
	}
}


SCENARIO("Testing Conditions 7")
{
	GIVEN("CGame")
	{

		CGame::_deck.clear();
		CGame::_players.clear();
		CGame::_table.ClearTheBoard();
		
		CGame::_players.push_back(CPlayer());
		CGame::_players.push_back(CPlayer());
		CGame::_players[1].add(CCard(10, clubs));
		CGame::_table.PutOnTable(CCard(4, clubs));
		

		WHEN("End Of Game")
		{
			THEN("Func = End Of Game")
			{
				{
					REQUIRE(CGame::SetCondition() == CGame::Condition::TheEndOfGame);
				}
			}
		}
	}
}




SCENARIO("Testing Conditions 1")
{
	GIVEN("CGame")
	{

		CGame::_players.push_back(CPlayer());
		CGame::_players.push_back(CPlayer());
		for (int i = 0; i < 36; i++)
		{
		CGame::_deck.push_back(CCard(1, clubs));
		}
		WHEN("StartOfTheGame")
		{
			THEN("Func = StartOfTheGame")
			{
				{
					REQUIRE(CGame::SetCondition() == CGame::Condition::StartOfTheGame);
				}
			}
		}
	}
}


SCENARIO("Testing Conditions 2")//çäåñü ïîêàçûâàåò ÷òî 6 èãðîêîâ à íå 6 êàðò
{
	GIVEN("CGame")
	{
		CGame::_deck.clear();
		CGame::_players.clear();

		CGame::_players.push_back(CPlayer());
		CGame::_players.push_back(CPlayer());
		

		for (int i = 0; i < 24; i++)	
		{
			CGame::_deck.push_back(CCard(1, clubs));
		}


		for (int i = 0; i < 6; i++)
		{
			CGame::_players[0].add(CCard(1, clubs));
		}



		for (int i = 0; i < 6; i++)
		{
			CGame::_players[1].add(CCard(1, clubs));
		}


		WHEN("AfterDistribution")
		{
			THEN("Func = true")
			{
				{
					REQUIRE(CGame::SetCondition() == CGame::Condition::AfterDistribution);
				}
			}
		}
	}
}




SCENARIO("Testing Conditions 3")//	enum Condition { -StartOfTheGame, -AfterDistribution, -PlayerCanPopUp, PlayerCantPopUp, PlayerCanCoverCard, PlayerCantCoverCard, -TheEndOfGame };

{
	GIVEN("CGame")
	{
		CGame::_deck.clear();
		CGame::_players.clear();
		CGame::_table.ClearTheBoard();
		
		CGame::_players.push_back(CPlayer());
		CGame::_players.push_back(CPlayer());

		for (int i = 0; i < 24; i++)
		{
			CGame::_deck.push_back(CCard(1, clubs));
		}

		CGame::_players[0].add(CCard(5, clubs));
		CGame::_players[0].add(CCard(7, diamonds));
		CGame::_players[0].add(CCard(jack, spades));
		CGame::_players[0].add(CCard(10, clubs));
		CGame::_players[0].add(CCard(queen, clubs));


		CGame::_players[1].add(CCard(6, clubs));
		CGame::_players[1].add(CCard(8, diamonds));
		CGame::_players[1].add(CCard(6, hearts));
		CGame::_players[1].add(CCard(jack, clubs));
		CGame::_players[1].add(CCard(9, clubs));

		CGame::_table.PutOnTable(CCard(6, diamonds));
		CGame::_table.PutOnTable(CCard(5, hearts));

		
		
		CGame::AttackPlayer = 1;
		CGame::DefendPlayer = 0;
		WHEN("PlayerCanPopUp")
		{
			THEN("Func = true")
			{
				{
					REQUIRE(CGame::SetCondition() == CGame::Condition::PlayerCanPopUp);
				}
			}
		}
	}
}







SCENARIO("Testing Conditions 4")//	enum Condition { -StartOfTheGame, -AfterDistribution, -PlayerCanPopUp, -PlayerCantPopUp, PlayerCanCoverCard, PlayerCantCoverCard, -TheEndOfGame };

{
	GIVEN("CGame")
	{
		CGame::_deck.clear();
		CGame::_players.clear();
		CGame::_table.ClearTheBoard();
		CGame::AttackPlayer = 0;
		for (int i = 0; i < 24; i++)
		{
			CGame::_deck.push_back(CCard(1, clubs));
		}

		CGame::_players.push_back(CPlayer());
		CGame::_players.push_back(CPlayer());
		
		CGame::_players[0].add(CCard(12, clubs));
		CGame::_players[0].add(CCard(7, diamonds));
		CGame::_players[0].add(CCard(jack, spades));
		CGame::_players[0].add(CCard(10, clubs));
		CGame::_players[0].add(CCard(queen, clubs));


		CGame::_players[1].add(CCard(6, clubs));
		CGame::_players[1].add(CCard(8, diamonds));
		CGame::_players[1].add(CCard(6, hearts));
		CGame::_players[1].add(CCard(jack, clubs));
		CGame::_players[1].add(CCard(9, clubs));

		CGame::_table.PutOnTable(CCard(6, diamonds));
		CGame::_table.PutOnTable(CCard(5, hearts));

		CGame::AttackPlayer = 0;

		WHEN("PlayerCantPopUp")
		{
			THEN("Func = true")
			{
				{
					REQUIRE(CGame::SetCondition() == CGame::Condition::PlayerCantPopUp);
				}
			}
		}
	}
}





SCENARIO("Testing Conditions 5")//	enum Condition { -StartOfTheGame, -AfterDistribution, -PlayerCanPopUp, -PlayerCantPopUp, PlayerCanCoverCard, PlayerCantCoverCard, -TheEndOfGame };

{
	GIVEN("CGame")
	{
		CGame::_deck.clear();
		CGame::_players.clear();
		CGame::_table.ClearTheBoard();
		CGame::AttackPlayer = 0;
		CGame::DefendPlayer = 1;

		for (int i = 0; i < 24; i++)
		{
			CGame::_deck.push_back(CCard(1, clubs));
		}

		CGame::_players.push_back(CPlayer());
		CGame::_players.push_back(CPlayer());

		CGame::_players[0].add(CCard(12, clubs));
		CGame::_players[0].add(CCard(7, diamonds));
		CGame::_players[0].add(CCard(jack, spades));
		CGame::_players[0].add(CCard(10, clubs));
		CGame::_players[0].add(CCard(queen, clubs));


		CGame::_players[1].add(CCard(6, clubs));
		CGame::_players[1].add(CCard(8, diamonds));
		CGame::_players[1].add(CCard(6, hearts));
		CGame::_players[1].add(CCard(jack, clubs));
		CGame::_players[1].add(CCard(9, clubs));

		CGame::_table.PutOnTable(CCard(6, diamonds));


		WHEN("PlayerCanCoverCard")
		{
			THEN("Func = true")
			{
				{
					REQUIRE(CGame::SetCondition() == CGame::Condition::PlayerCanCoverCard);
				}
			}
		}
	}
}



SCENARIO("Testing Conditions 6")	
//	enum Condition { -StartOfTheGame, -AfterDistribution, -PlayerCanPopUp, -PlayerCantPopUp, -PlayerCanCoverCard, -PlayerCantCoverCard, -TheEndOfGame };

{
	GIVEN("CGame")
	{
		CGame::_deck.clear();
		CGame::_players.clear();
		CGame::_table.ClearTheBoard();
		CGame::AttackPlayer = 1;
		CGame::DefendPlayer = 0;

		for (int i = 0; i < 24; i++)
		{
			CGame::_deck.push_back(CCard(1, clubs));
		}

		CGame::_players.push_back(CPlayer());
		CGame::_players.push_back(CPlayer());

		CGame::_table.setTrump(CCard(3, hearts));

		CGame::_players[0].add(CCard(12, clubs));
		CGame::_players[0].add(CCard(jack, spades));
		CGame::_players[0].add(CCard(10, clubs));
		CGame::_players[0].add(CCard(queen, clubs));


		CGame::_players[1].add(CCard(6, clubs));
		CGame::_players[1].add(CCard(8, diamonds));
		CGame::_players[1].add(CCard(6, hearts));
		CGame::_players[1].add(CCard(jack, clubs));
		CGame::_players[1].add(CCard(9, clubs));

		CGame::_table.PutOnTable(CCard(6, diamonds));


		WHEN("PlayerCantCoverCard")
		{
			THEN("Func = true")
			{
				{
					REQUIRE(CGame::SetCondition() == CGame::Condition::PlayerCantCoverCard);
				}
			}
		}
	}


}

//ÈÍÎÃÄÀ ÁÜÅÒÑß ÊÀÐÒÎÉ ÌÅÍÜØÅ ×ÅÌ ÍÀ ÑÒÎËÅ(ÍÅ ÊÎÇÛÐÜ) È ÈÍÎÃÄÀ ÊÈÄÀÅÒ (ÎÒÁÈÂÀÅÒÑß) ÒÅÌ ×ÒÎ ÓÆÅ ÅÑÒÜ ÍÀ ÑÒÎËÅ
//
//if (CGame::_table.GetCard(CGame::_table.GetSize() - 1).GetSuit() == CGame::_table.getTrump())
//CGame::_players[CGame::DefendPlayer].DropToTableCard(CGame::_players[CGame::DefendPlayer].CanCoverASuit(CGame::_table.GetCard(CGame::_table.GetSize() - 1)));
//else
//CGame::_players[CGame::DefendPlayer].DropToTableCard(CGame::_players[CGame::DefendPlayer].CanCoverNotASuit(CGame::_table.GetCard(CGame::_table.GetSize() - 1), CGame::_table.getTrump()));
SCENARIO("Testing Covering Card")
{
	GIVEN("CGame")
	{
		CGame::_deck.clear();
		CGame::_players.clear();
		CGame::_table.ClearTheBoard();
		CGame::DefendPlayer = 1;
		CGame::AttackPlayer = 0;

		CGame::_players.push_back(CPlayer());
		CGame::_players.push_back(CPlayer());

		CGame::_table.setTrump(CCard(3, diamonds));
		CGame::_table.PutOnTable(CCard(jack, hearts));


		CGame::_players[0].add(CCard(7, diamonds));
		CGame::_players[0].add(CCard(11, diamonds));
		CGame::_players[0].add(CCard(7, clubs));
		CGame::_players[0].add(CCard(10, hearts));
		CGame::_players[0].add(CCard(2, hearts));
		CGame::_players[0].add(CCard(5, clubs));

		CGame::_players[1].add(CCard(jack, diamonds));
		CGame::_players[1].add(CCard(11, clubs));
		CGame::_players[1].add(CCard(6, clubs));
		CGame::_players[1].add(CCard(jack, clubs));
		CGame::_players[1].add(CCard(8, hearts));
		CGame::_players[1].add(CCard(queen, hearts));
		

		bool requred;
		CGame::_players[1].DropToTableCard(CGame::_players[1].CanCoverNotASuit(CGame::_table.GetCard(0), CGame::_table.getTrump()));

		if (CGame::_table.GetCard(1) == CCard(jack, diamonds) || CGame::_table.GetCard(1) == CCard(queen, hearts))
			requred = 1;
		else 
			requred = 0;

		WHEN("PlayerCoverCard")
		{
			THEN("Func = true")
			{
				{
					
					REQUIRE(requred == 1);
				}
			}
		}
	}


}