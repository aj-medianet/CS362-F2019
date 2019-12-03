//Unit Test 1
//Author: Shawn McMannis
//CS 362 Software Engineering II
//Last Mod Date: 12/3/2019

#include "dominion.h"
#include "compare.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TESTFUNCTION "cardEffect()"

int main(int argc, char *argv[])
{
	//Set card array
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};

	//Declare game states
	struct gameState G;

	//Delcare random seed
	int seed = time(NULL);

	//Declare maximum hand size
	int handCount = 2;

	printf("----------------- Testing Function: %s ----------------\n", TESTFUNCTION);

	//TEST 1: mine case of cardEffect function not trashing card as intended
	printf("TEST 1: mine case of cardEffect function not trashing card as intended\n");

	//Set game state
	memset(&G, 23, sizeof(struct gameState));

	//Initialize a new game
	initializeGame(2, k, seed, &G);

	//Set hand variables
	G.handCount[0] = handCount;
	G.hand[0][0] = mine;
	G.hand[0][1] = copper;

	//Call the function
	cardEffect(mine, 1, silver, 0, &G, 0, 0);

	printf("mine card should not be in playedCards array\n");
	COMPARE(G.playedCards[0] != mine);
	
	printf("----------------- Testing Finished: %s ----------------\n\n\n", TESTFUNCTION);
}
