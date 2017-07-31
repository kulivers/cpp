// foolgametests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "player.h"

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