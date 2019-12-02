/*
 * unittest8.c
 *
 
 */

/*
 * Include the following lines in your makefile:
 *
 * unittest8: unittest8.c dominion.o rngs.o
 *      gcc -o unittest8 -g  unittest8.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
//#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFUNCTION "playCard()"

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

    int i;
    int handPos = 0, choice1 = 1, choice2 = 0, choice3 = 0, coin_bonus = 0;
	int card = baron;
    int seed = 1000;
    int numPlayers = 2;
    int currentPlayer = 0;
	int numCards = 0;
    int numCoinsNew = 0;
	int testP = 0;
	int testC = 0;
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

	printf("----------------- Testing Function: %s ----------------\n", TESTFUNCTION);

	// ----------- TEST 8: Bonus coins not updated correctly during cardEffect()in playCard() when playing Baron. --------------
	printf("TEST 8: Bonus coins not updated correctly during cardEffect() in playCard() when playing Baron.\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	handPos = 0;
	choice1 = 1;
	choice2 = 0;
	choice3 = 0; 
	card = baron;

	currentPlayer = whoseTurn(&testG);
	numCards = numHandCards(&testG);

	testG.hand[currentPlayer][handPos] = baron;	// Make sure handPos card == baron

	for(i = 1; i < numCards-1; i++)	// Change three cards in hand to estate.
		testG.hand[currentPlayer][i] = estate;
	testG.hand[currentPlayer][numCards-1] = duchy;	// Changed last card to duchy

	testG.phase = 0;		// Make sure phase is > 0
	testG.numActions = 2; 	// Make sure numActions > 0

	testP = playCard(handPos, choice1, choice2, choice3, &testG);	// Run playCard

	numCoinsNew = testG.coins;	// Store new numCoins

	testC = cardEffect(baron, choice1, choice2, choice3, &testG, handPos, &coin_bonus);
	printf("expected num coins after estate discarded = 4\n");
	printf("actual = %d\n", numCoinsNew);
	printf("assert = %d\n\n", myAssert(4, numCoinsNew));
	
	// ----------- TESTS FINISHED. --------------
	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTFUNCTION);

	return 0;
}