/*
 * unittest10.c
 *
 
 */

/*
 * Include the following lines in your makefile:
 *
 * unittest10: unittest10.c dominion.o rngs.o
 *      gcc -o cardtest10 -g  unittest10.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
//#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "ambassador"

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

    int handPos = 0, choice1 = 1, choice2 = 2, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int currentPlayer = 0;
	int numCardsOld = 0, numCardsNew = 0;
	int aTest = 0;
	struct gameState G;
	
	int k[10] = { adventurer, embargo, village, minion, mine, 
				ambassador, cutpurse, tribute, smithy, council_room};

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
	
	// ----------- TEST 10: Ambassador card does not discard copies of revealed cards from player's hand. --------------
	printf("TEST 10: Ambassador card does not discard copies of revealed cards from player's hand.\n");

	// copy the game state to a test case
	//memcpy(&testG, &G, sizeof(struct gameState));
	handPos = 0;
	choice1 = 1;
	choice2 = 2;
	G.hand[currentPlayer][handPos] = ambassador;	// Make card at handPos == ambassador
	G.hand[currentPlayer][choice1] = adventurer;	// Make card at choice1 == adventurer
	G.hand[currentPlayer][choice1+1] = adventurer;	// Make next two cards == adventurer
	G.hand[currentPlayer][choice1+2] = adventurer;
	G.hand[currentPlayer][choice1+3] = baron;
	numCardsOld = numHandCards(&G);

	aTest = cardEffect(ambassador, choice1, choice2, choice3, &G, handPos, &bonus);

	numCardsNew = numHandCards(&G);

	printf("num cards before function call:%d\n", numCardsOld);
	printf("num cards after function call:%d - 3\n", numCardsOld);
	printf("actual num cards = %d\n", numCardsNew);
	printf("assert = %d\n\n", myAssert(numCardsOld - 3, numCardsNew));

	// ----------- TESTS FINISHED. --------------
	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);

	return 0;
}

