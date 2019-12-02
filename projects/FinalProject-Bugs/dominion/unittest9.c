/*
 * unittest9.c
 *
 
 */

/*
 * Include the following lines in your makefile:
 *
 * unittest9: unittest9.c dominion.o rngs.o
 *      gcc -o unittest9 -g  unittest9.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
//#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "tribute"

/* 	Custom assert function: Asserts if expected and actual results are the same.
	Parameters:	int expected = expected results
				int actual = actual results
	Return:		1 if they are the same
				0 if they are not the same
*/
int myAssert(int expected, int actual){
	return expected == actual;
}

int main() {

    int seed = 1000;
    int numPlayers = 2;
	int handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int currentPlayer = 0, nextPlayer = 1;
    int numActionsOld = 0, numActionsNew = 0;
	struct gameState G, testG;
	
	int k[10] = { adventurer, embargo, village, minion, mine, 
				baron, cutpurse, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	/* Print players' cards
	for(int i = 0; i < numPlayers; i++){
		for(int j = 0; j < 5; j++){
			printf("Player: %d, hand: %d\n", i, G.hand[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
	*/

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 9: Tribute card correctly adds two numActions in case of duplicate revealed cards. --------------
	printf("TEST 9: Tribute card incorrectly adds numActions in case of duplicate revealed treasures.\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// Make next player have no cards in deck and two cards in discard
	testG.hand[currentPlayer][handPos] = tribute;	// Set card at handPos as tribute
	testG.deckCount[nextPlayer] = 2;
	testG.discardCount[nextPlayer] = 2;
	testG.deck[nextPlayer][0] = copper;	// Deck has two copper cards only
	testG.deck[nextPlayer][1] = copper;	

	numActionsOld = testG.numActions;

	cardEffect(tribute, choice1, choice2, choice3, &testG, handPos, &bonus);

	numActionsNew = testG.numActions;

	printf("num actions before function call = %d\n", numActionsOld);
	printf("expected num actions after function call = %d\n", numActionsOld);
	printf("actual num actions = %d\n", numActionsNew);
	printf("assert = %d\n\n", myAssert(numActionsOld, numActionsNew));		

	// ----------- TESTS FINISHED. --------------
	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);

	return 0;
}

