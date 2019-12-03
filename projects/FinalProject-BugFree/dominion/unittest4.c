//Unit Test 4
//Author: Shawn McMannis
//CS 362 Software Engineering II
//Last Mod Date: 12/3/2019

#include "dominion.h"
#include "compare.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TESTFUNCTION "isGameOver()"

int main(int argc, char *argv[])
{
	//Set card array
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};

	//Declare game states
	struct gameState G;

	//Delcare random seed
	int seed = time(NULL);

	printf("----------------- Testing Function: %s ----------------\n", TESTFUNCTION);

	//TEST 4: isGameOver function not iterating through all supply counts
	printf("TEST 4: isGameOver function not iterating through all supply counts\n");

	//Set game state
	memset(&G, 23, sizeof(struct gameState));

	//Initialize a new game
	initializeGame(2, k, seed, &G);

	//Set supply count values
	G.supplyCount[province] = 1;
	G.supplyCount[estate] = 0;
	G.supplyCount[mine] = 0;
	G.supplyCount[treasure_map] = 0;

	//Call the function
	int ret = isGameOver(&G);

	printf("Return value should be 1\n");
	COMPARE(ret == 1);
	
	printf("----------------- Testing Finished: %s ----------------\n\n\n", TESTFUNCTION);
}
