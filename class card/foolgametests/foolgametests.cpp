// foolgametests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "player.h"
#include "functions.h"

TEST_CASE("getOneBit")
{
	uint8_t data[1];
	
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

SCENARIO("Find a player who plays first when there're no trump")
{
	GIVEN("Two players with no trump card")
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

					WHEN("Another player with six diamonds")
					{
						players.push_back(CPlayer());
						cards = GetSixDiamonds();
						for (auto cardIt = cards.begin(); cardIt != cards.end(); cardIt++)
							players.back().add(*cardIt);

						THEN("The first of them could move first")
						{
							REQUIRE(WhoPlaysFirst(deck, players, t) == 0);
						}
					}
				}
			}
		}
	}
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