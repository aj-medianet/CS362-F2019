//Unit Test 3
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

	//TEST 3: remodel case of cardEffect function returns -1 despite choosing an affordable card to gain
	printf("TEST 3: remodel case of cardEffect function returns -1 despite choosing an affordable card to gain\n");

	//Set game state
	memset(&G, 23, sizeof(struct gameState));

	//Initialize a new game
	initializeGame(2, k, seed, &G);

	//Set hand variables
	G.handCount[0] = handCount;
	G.hand[0][0] = remodel;
	G.hand[0][1] = estate;

	//Call the function
	int ret = cardEffect(remodel, 1, estate, 0, &G, 0, 0);

	printf("Return value should be 0\n");
	COMPARE(ret == 0);
	
	printf("----------------- Testing Finished: %s ----------------\n\n\n", TESTFUNCTION);
}
