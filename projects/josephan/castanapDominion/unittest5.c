/*
 * author Andrew Joseph
 * 11/3/19
 * unittest5.c
 * unit test for mineCard()
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

// assert a == to b
int assertAequalsB(int a, int b) {
    if (a == b) {
        return 1;
    }
    return 0;
}

int main() {
    int i;
    int player1 = 0;
    int player2 = 1;
    int seed = 1000;
    int numPlayer = 2;
    int r;
    int k[10] = {minion, estate, council_room, feast, gardens, mine
        , remodel, smithy, village, great_hall};
    struct gameState G;
    // arrays of all coppers, silvers, and golds
    int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];
    int minions[MAX_HAND];
    int estates[MAX_HAND];
    int ambassadors[MAX_HAND];
    for (i = 0; i < MAX_HAND; i++)
    {
        coppers[i] = copper;
        silvers[i] = silver;
        golds[i] = gold;
        minions[i] = minion;
        estates[i] = estate;
        ambassadors[i] = ambassador;
    }
    
    
    //printf ("TESTING updateCoins():\n");
    printf("\n\n******************************\n");
    printf("*** Testing mineCard() ***\n");
    printf("********************************\n");
    
    
    printf("\n\n***************************************************\n");
    printf("*** Testing playing 1 copper and gaining 1 silver ***\n");
    printf("*****************************************************\n");
    // setup the game state
    
    int choice1 = 4;
    int choice2 = 5;
    int handPos = 0;
    
    int mceReturnVal;

    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
    G.handCount[player1] = 5;
    G.handCount[1] = 5;
    memcpy(G.hand[player1], coppers, sizeof(int) * 5); // set all p1's cards to coppers
    memcpy(G.hand[player2], coppers, sizeof(int) * 5); // set all p2's cards to coppers
    
    //count how many coppers and silvers are in hand before func call
    int beforeNumCoppers = 0;
    int afterNumCoppers = 0;
    
    int beforeNumSilvers = 0;
    int afterNumSilvers = 0;
    for (i = 0; i < G.handCount[player1]; i++) {
        if (G.hand[player1][i] == copper) {
            beforeNumCoppers++;
        }
        if (G.hand[player1][i] == silver) {
            beforeNumSilvers++;
        }
    }
    
    mceReturnVal = mineCard(choice1, choice2, &G, handPos);
    
    
    printf("*** Positive Testing, func should return 0 ***\n");
    if (mceReturnVal == 0) {
        printf("Test passed. Function return value: %d\n", mceReturnVal);
    } else {
        printf("Test failed. Function return value: %d\n", mceReturnVal);
    }
    
    // get numCoppers and numSilvers after func call
    for (i = 0; i < G.handCount[player1]; i++) {
        if (G.hand[player1][i] == copper) {
            afterNumCoppers++;
        }
        if (G.hand[player1][i] == silver) {
            afterNumSilvers++;
        }
    }
    
    printf("*** Number of Coppers in hand should go from %d to %d ***\n", beforeNumCoppers, beforeNumCoppers - 1);
    if (beforeNumCoppers - 1 == afterNumCoppers) {
        printf("Test passed. Number of coppers: %d\n", afterNumCoppers);
    } else {
        printf("Test failed. Number of coppers: %d\n", afterNumCoppers);
    }
    
  
    
    printf("*** Number of Silvers in hand should go from %d to %d ***\n", beforeNumSilvers, beforeNumSilvers + 1);
    if (beforeNumSilvers + 1 == afterNumSilvers) {
        printf("Test passed. Number of silvers: %d\n", afterNumSilvers);
    } else {
        printf("Test failed. Number of silvers: %d\n", afterNumSilvers);
    }
    
    printf("\n\n*************************************************\n");
    printf("*** Testing playing 1 silver and gaining 1 gold ***\n");
    printf("***************************************************\n");
    // setup the game state
    
    choice1 = 5;
    choice2 = 6;
    handPos = 0;
    
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
    G.handCount[player1] = 5;
    G.handCount[1] = 5;
    memcpy(G.hand[player1], silvers, sizeof(int) * 5); // set all p1's cards to silvers
    memcpy(G.hand[player2], coppers, sizeof(int) * 5); // set all p2's cards to coppers
    
    //count how many coppers and silvers are in hand before func call
    
    beforeNumSilvers = 0;
    afterNumSilvers = 0;
    int beforeNumGolds = 0;
    int afterNumGolds = 0;
    
    for (i = 0; i < G.handCount[player1]; i++) {
        if (G.hand[player1][i] == gold) {
            beforeNumGolds++;
        }
        if (G.hand[player1][i] == silver) {
            beforeNumSilvers++;
        }
    }
    
    mceReturnVal = mineCard(choice1, choice2, &G, handPos);
    
    
    printf("*** Positive Testing, func should return 0 ***\n");
    if (mceReturnVal == 0) {
        printf("Test passed. Function return value: %d\n", mceReturnVal);
    } else {
        printf("Test failed. Function return value: %d\n", mceReturnVal);
    }
    
    // get numCoppers and numSilvers after func call
    for (i = 0; i < G.handCount[player1]; i++) {
        if (G.hand[player1][i] == gold) {
            afterNumGolds++;
        }
        if (G.hand[player1][i] == silver) {
            afterNumSilvers++;
        }
    }
    
    printf("*** Number of silvers in hand should go from %d to %d ***\n", beforeNumSilvers, beforeNumSilvers - 1);
    if (beforeNumSilvers - 1 == afterNumSilvers) {
        printf("Test passed. Number of silvers: %d\n", afterNumSilvers);
    } else {
        printf("Test failed. Number of silvers: %d\n", afterNumSilvers);
    }
    
    
    
    printf("*** Number of golds in hand should go from %d to %d ***\n", beforeNumGolds, beforeNumGolds + 1);
    if (beforeNumGolds + 1 == afterNumGolds) {
        printf("Test passed. Number of golds: %d\n", afterNumGolds);
    } else {
        printf("Test failed. Number of golds: %d\n", afterNumGolds);
    }
    
    
    
    printf("\n\n***************************************************\n");
    printf("*** Negative Testing, playing a non treasure card ***\n");
    printf("*****************************************************\n");
    // setup the game state
    
    choice1 = 1;
    choice2 = 5;
    handPos = 0;
    
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
    G.handCount[player1] = 5;
    G.handCount[1] = 5;
    memcpy(G.hand[player1], estates, sizeof(int) * 5); // set all p1's cards to estates
    memcpy(G.hand[player2], coppers, sizeof(int) * 5); // set all p2's cards to coppers
    
    
    mceReturnVal = mineCard(choice1, choice2, &G, handPos);
    
    
    printf("*** Negative Testing, func should return -1 ***\n");
    if (mceReturnVal == -1) {
        printf("Test passed. Function return value: %d\n", mceReturnVal);
    } else {
        printf("Test failed. Function return value: %d\n", mceReturnVal);
    }
    
    printf("*** Negative Testing, func should return -1 ***\n");
    printf("*** Passed in an estate card ***\n");
    if (mceReturnVal == -1) {
        printf("Test passed. Function return value: %d\n", mceReturnVal);
    } else {
        printf("Test failed. Function return value: %d\n", mceReturnVal);
    }
    
    choice1 = 5;
    choice2 = 4;
    memcpy(G.hand[player1], silvers, sizeof(int) * 5); // set all p1's cards to estates
    
    printf("*** Negative Testing, func should return -1 ***\n");
    printf("*** flipped choice1 and choice2 ***\n");
    if (mceReturnVal == -1) {
        printf("Test passed. Function return value: %d\n", mceReturnVal);
    } else {
        printf("Test failed. Function return value: %d\n", mceReturnVal);
    }

    
    
    printf("\n\nEnd of mineCard() tests\n\n");
    
    return 0;
}
