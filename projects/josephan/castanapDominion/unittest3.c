/*
 * author Andrew Joseph
 * 11/3/19
 * unittest3.c
 * unit test for ambassadorCard()
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
    int player = 0;
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
    for (i = 0; i < MAX_HAND; i++)
    {
        coppers[i] = copper;
        silvers[i] = silver;
        golds[i] = gold;
        minions[i] = minion;
    }
    
    int aceReturnValue;
    
    printf("\n\n**********************************\n");
    printf("*** Testing ambassadorCard() ***\n");
    printf("**********************************\n");
    
    // setup the game state
    int choice1 = 0;
    int choice2 = 0;
    int handPos = 1;
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
    G.handCount[player] = 5;
    G.handCount[1] = 5;
    memcpy(G.hand[player], minions, sizeof(int) * 5); // set all p1's cards to minions
    memcpy(G.hand[1], coppers, sizeof(int) * 5); // set all p2's cards to coppers
    
    //test print players hand
    /*
    printf("\n\nplayer1\n");
    for (i = 0; i < G.handCount[player]; i++) {
        printf("%d\n", G.hand[player][i]);
    }
    
    printf("\n\nplayer2\n");
    for (i = 0; i < G.handCount[1]; i++) {
        printf("%d\n", G.hand[1][i]);
    }
     */
    
    
    
    printf("\n********************************\n");
    printf("*** Negative Testing choice2 ***\n");
    printf("********************************\n");
    
    choice2 = 3;
    
    // call the function we're unit testing
    aceReturnValue = ambassadorCard(choice1, choice2, &G, handPos);
    
    printf("*** Testing choice2 > 2 ***\n");
    if (aceReturnValue == -1) {
        printf("Test Passed, return value: %d\n", aceReturnValue);
    } else {
        printf("Test failed, return val: %d\n", aceReturnValue);
    }
    
    choice2 = -1;
    aceReturnValue = ambassadorCard(choice1, choice2, &G, handPos);

    printf("*** Testing choice2 < 0 ***\n");
    if (aceReturnValue == -1) {
        printf("Test Passed, return value: %d\n", aceReturnValue);
    } else {
        printf("Test failed, return val: %d\n", aceReturnValue);
    }
    
    
    
    printf("\n*******************************************\n");
    printf("*** Negative Testing choice1 == handpos ***\n");
    printf("*******************************************\n");
    
    choice1 = 1;
    choice2 = 1;
    
    aceReturnValue = ambassadorCard(choice1, choice2, &G, handPos);
    printf("*** return val should be -1 ***\n");
    if (aceReturnValue == -1) {
        printf("Test Passed, return value: %d\n", aceReturnValue);
    } else {
        printf("Test failed, return val: %d\n", aceReturnValue);
    }
    
    
    printf("\n****************************************************************\n");
    printf("*** Negative test to check that too low handcount returns -1 ***\n");
    printf("****************************************************************\n");
    
    /* TO DO NEED TO FIX */
    
    // setup the game state
    choice1 = 0;
    choice2 = 0;
    handPos = 1;
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
    G.handCount[player] = 0;
    G.handCount[1] = 5;
    memcpy(G.hand[player], minions, sizeof(int) * 5); // set all p1's cards to minions
    memcpy(G.hand[1], coppers, sizeof(int) * 5); // set all p2's cards to coppers
    
    aceReturnValue = ambassadorCard(choice1, choice2, &G, handPos);
    printf("*** return val should be -1 ***\n");
    if (aceReturnValue == -1) {
        printf("Test Passed, return value: %d\n", aceReturnValue);
    } else {
        printf("Test failed, return val: %d\n", aceReturnValue);
    }
    
    
    
    printf("\n***********************\n");
    printf("*** Positive tests  ***\n");
    printf("***********************\n");
    
    // setup the game state
    choice1 = 0;
    choice2 = 1;
    handPos = 1;
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
    G.handCount[player] = 5;
    G.handCount[1] = 5;
    memcpy(G.hand[player], minions, sizeof(int) * 5); // set all p1's cards to minions
    memcpy(G.hand[1], coppers, sizeof(int) * 5); // set all p2's cards to coppers
    
    
    //test print players hand
    
    printf("\n\nplayer1\n");
    for (i = 0; i < G.handCount[player]; i++) {
        printf("%d\n", G.hand[player][i]);
    }
    
    printf("\n\nplayer2\n");
    for (i = 0; i < G.handCount[1]; i++) {
        printf("%d\n", G.hand[1][i]);
    }
    
    printf("\n****************************************************\n");
    printf("*** Check supply count gets increased correctly  ***\n");
    printf("****************************************************\n");
    
    // set supply count so we can test it against given outcome
    G.supplyCount[G.hand[player][choice1]] = 0;
    
    // get before hand count to check discarding
    int beforeHandCount = G.handCount[player];
    
    aceReturnValue = ambassadorCard(choice1, choice2, &G, handPos);
    
    printf("*** Supply count should increase from %d to %d ***\n", G.supplyCount[G.hand[player][choice1]], G.supplyCount[G.hand[player][choice1]] + choice2 );
    if ( G.supplyCount[G.hand[player][choice1]] ==  G.supplyCount[G.hand[player][choice1]] + choice2) {
        printf("Test Passed, supply count: %d\n", G.supplyCount[G.hand[player][choice1]]);
    } else {
        printf("Test failed, supply count: %d\n", G.supplyCount[G.hand[player][choice1]]);
    }
    
    
    
    
    printf("*** return val should be 0 ***\n");
    if (aceReturnValue == 0) {
        printf("Test Passed, return val: %d\n", aceReturnValue);
    } else {
        printf("Test failed, return val: %d\n", aceReturnValue);
    }
    
    
    printf("\n******************************************\n");
    printf("*** Check player discards 1 correctly  ***\n");
    printf("******************************************\n");
    printf("*** Hand count should go from %d to %d ***\n", beforeHandCount, beforeHandCount - 1);
    if( beforeHandCount - 1 == G.handCount[player]) {
        printf("Test Passed, hand count: %d\n", G.handCount[player]);
    } else {
        printf("Test Failed, hand count: %d\n", G.handCount[player]);
    }
    
    
    // setup the game state
    choice1 = 2;
    choice2 = 4;
    handPos = 4;
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
    G.handCount[player] = 10;
    G.handCount[1] = 10;
    memcpy(G.hand[player], minions, sizeof(int) * 10); // set all p1's cards to minions
    memcpy(G.hand[1], minions, sizeof(int) * 10); // set all p2's cards to coppers

    
    printf("\n\nplayer1\n");
    for (i = 0; i < G.handCount[player]; i++) {
        printf("%d\n", G.hand[player][i]);
    }
    
    printf("\n\nplayer2\n");
    for (i = 0; i < G.handCount[1]; i++) {
        printf("%d\n", G.hand[1][i]);
    }
    
    aceReturnValue = ambassadorCard(choice1, choice2, &G, handPos);
 
    
    printf("\n\nEnd of ambassadorCard() tests\n\n");
    
    return 0;
}

