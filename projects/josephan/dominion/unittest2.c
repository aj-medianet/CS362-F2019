/*
 * author Andrew Joseph
 * 11/3/19
 * unittest2.c
 * unit test for minionCardEffect()
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
    
    
    //printf ("TESTING updateCoins():\n");
    printf("\n\n**********************************\n");
    printf("*** Testing minionCardEffect() ***\n");
    printf("**********************************\n");
    
    // setup the game state
    int choice1 = 0;
    int choice2 = 0;
    int handPos = 0;
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
    G.handCount[player] = 5;
    G.handCount[1] = 5;
    memcpy(G.hand[player], minions, sizeof(int) * 5); // set all p1's cards to minions
    memcpy(G.hand[1], coppers, sizeof(int) * 5); // set all p2's cards to coppers
    
    int beforeNumActions = G.numActions; // get num of actions for before call count
    int beforeNumMinions = 0; // count num of minions in hand
    for (i = 0; i < G.handCount[player]; i++) {
        if (G.hand[player][i] == minion) {
            beforeNumMinions++;
        }
    }
    
    int beforeNumCoins = G.coins;
    int afterNumCoins;
    
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
    
    printf("\n****************************\n");
    printf("*** Testing choice1 == 0 ***\n");
    printf("*** Testing choice2 == 0 ***\n");
    printf("****************************\n");
    
    
    // call the function we're unit testing
    minionCardEffect(choice1, choice2, &G, handPos, player);
    
    printf("\n*** Check numActions increases by 1 from %d to %d ***\n", beforeNumActions, beforeNumActions + 1);
    if (beforeNumActions + 1 == G.numActions) {
        printf("Test Passed. numActions: %d\n", G.numActions);
    } else {
        printf("Test Failed. numActions: %d\n", G.numActions);
    }
    
    printf("*** Check discard our card from %d to %d ***\n", beforeNumMinions, beforeNumMinions - 1);
    int afterNumMinions = 0;
    for (i = 0; i < G.handCount[player]; i++) {
        if (G.hand[player][i] == minion) {
            afterNumMinions++;
        }
    }
    if (beforeNumMinions - 1 == afterNumMinions) {
        printf("Test Passed. Number of minion cards in hand: %d\n", afterNumMinions);
    } else {
        printf("Test Failed. Number of minion cards in hand: %d\n", afterNumMinions);
    }
    
    printf("*** Check number of coins. Should stay the same at %d because choice1 = 0 \n", beforeNumCoins);
    afterNumCoins = G.coins;
    if (beforeNumCoins == afterNumCoins) {
        printf("Test Passed. Number of coins: %d\n", afterNumCoins);
    } else {
        printf("Test Failed. Number of coins: %d\n", afterNumCoins);
    }
    
    
    
    // **  NEXT TEST **
    
    printf("\n****************************\n");
    printf("*** Testing choice1 == 1 ***\n");
    printf("*** Testing choice2 == 1 ***\n");
    printf("****************************\n");
    
    // setup the game state
    int k1[10] = {minion, estate, council_room, feast, gardens, mine
        , remodel, smithy, village, great_hall};
    choice1 = 1;
    choice2 = 1;
    handPos = 0;
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k1, seed, &G); // initialize a new game
    memcpy(G.hand[player], minions, sizeof(int) * 5); // set all p1's cards to minions
    memcpy(G.hand[1], coppers, sizeof(int) * 5); // set all p2's cards to coppers
    
    beforeNumActions = G.numActions; // get num of actions for before call count
    beforeNumMinions = 0; // count num of minions in hand
    for (i = 0; i < G.handCount[player]; i++) {
        if (G.hand[player][i] == minion) {
            beforeNumMinions++;
        }
    }
    
    beforeNumCoins = G.coins;
    
    // call the function we're unit testing
    minionCardEffect(choice1, choice2, &G, handPos, player);
    
    printf("\n*** Check numActions increases by 1 from %d to %d ***\n", beforeNumActions, beforeNumActions + 1);
    if (beforeNumActions + 1 == G.numActions) {
        printf("Test Passed. numActions: %d\n", G.numActions);
    } else {
        printf("Test Failed. numActions: %d\n", G.numActions);
    }
    
    printf("*** Check discard our card from %d to %d ***\n", beforeNumMinions, beforeNumMinions - 1);
    afterNumMinions = 0;
    for (i = 0; i < G.handCount[player]; i++) {
        if (G.hand[player][i] == minion) {
            afterNumMinions++;
        }
    }
    if (beforeNumMinions - 1 == afterNumMinions) {
        printf("Test Passed. Number of minion cards in hand: %d\n", afterNumMinions);
    } else {
        printf("Test Failed. Number of minion cards in hand: %d\n", afterNumMinions);
    }
    
    printf("*** Check number of coins. Should increase from %d to %d because choice1 = 1 \n", beforeNumCoins, beforeNumCoins + 2);
    afterNumCoins = G.coins;
    if (beforeNumCoins + 2 == afterNumCoins) {
        printf("Test Passed. Number of coins: %d\n", afterNumCoins);
    } else {
        printf("Test Failed. Number of coins: %d\n", afterNumCoins);
    }
    
    
    
    
    
    // **  NEXT TEST **
    
    printf("\n****************************\n");
    printf("*** Testing choice1 == 1 ***\n");
    printf("*** Testing choice2 == 0 ***\n");
    printf("****************************\n");
    
    // setup the game state
    int k2[10] = {minion, estate, council_room, feast, gardens, mine
        , remodel, smithy, village, great_hall};
    choice1 = 1;
    choice2 = 0;
    handPos = 0;
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k2, seed, &G); // initialize a new game
    memcpy(G.hand[player], minions, sizeof(int) * 5); // set all p1's cards to minions
    memcpy(G.hand[1], coppers, sizeof(int) * 5); // set all p2's cards to coppers
    
    beforeNumActions = G.numActions; // get num of actions for before call count
    beforeNumMinions = 0; // count num of minions in hand
    for (i = 0; i < G.handCount[player]; i++) {
        if (G.hand[player][i] == minion) {
            beforeNumMinions++;
        }
    }
    
    beforeNumCoins = G.coins;
    
    // call the function we're unit testing
    minionCardEffect(choice1, choice2, &G, handPos, player);
    
    printf("\n*** Check numActions increases by 1 from %d to %d ***\n", beforeNumActions, beforeNumActions + 1);
    if (beforeNumActions + 1 == G.numActions) {
        printf("Test Passed. numActions: %d\n", G.numActions);
    } else {
        printf("Test Failed. numActions: %d\n", G.numActions);
    }
    
    printf("*** Check discard our card from %d to %d ***\n", beforeNumMinions, beforeNumMinions - 1);
    afterNumMinions = 0;
    for (i = 0; i < G.handCount[player]; i++) {
        if (G.hand[player][i] == minion) {
            afterNumMinions++;
        }
    }
    if (beforeNumMinions - 1 == afterNumMinions) {
        printf("Test Passed. Number of minion cards in hand: %d\n", afterNumMinions);
    } else {
        printf("Test Failed. Number of minion cards in hand: %d\n", afterNumMinions);
    }
    
    printf("*** Check number of coins. Should increase from %d to %d because choice1 = 1 \n", beforeNumCoins, beforeNumCoins + 2);
    afterNumCoins = G.coins;
    if (beforeNumCoins + 2 == afterNumCoins) {
        printf("Test Passed. Number of coins: %d\n", afterNumCoins);
    } else {
        printf("Test Failed. Number of coins: %d\n", afterNumCoins);
    }
    
    
    
    
    
    // **  NEXT TEST **
    
    printf("\n****************************\n");
    printf("*** Testing choice1 == 0 ***\n");
    printf("*** Testing choice2 == 1 ***\n");
    printf("****************************\n");
    
    // setup the game state
    int k3[10] = {minion, estate, council_room, feast, gardens, mine
        , remodel, smithy, village, great_hall};
    choice1 = 0;
    choice2 = 1;
    handPos = 0;
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k3, seed, &G); // initialize a new game
    memcpy(G.hand[player], minions, sizeof(int) * 5); // set all p1's cards to minions
    memcpy(G.hand[1], coppers, sizeof(int) * 5); // set all p2's cards to coppers
    
    beforeNumActions = G.numActions; // get num of actions for before call count
    beforeNumMinions = 0; // count num of minions in hand
    for (i = 0; i < G.handCount[player]; i++) {
        if (G.hand[player][i] == minion) {
            beforeNumMinions++;
        }
    }
    
    // call the function we're unit testing
    minionCardEffect(choice1, choice2, &G, handPos, player);
    
    printf("\n*** Check numActions increases by 1 from %d to %d ***\n", beforeNumActions, beforeNumActions + 1);
    if (beforeNumActions + 1 == G.numActions) {
        printf("Test Passed. numActions: %d\n", G.numActions);
    } else {
        printf("Test Failed. numActions: %d\n", G.numActions);
    }
    
    
    printf("*** Check number of coins. Should stay the same at %d because choice1 = 0 \n", beforeNumCoins);
    afterNumCoins = G.coins;
    if (beforeNumCoins == afterNumCoins) {
        printf("Test Passed. Number of coins: %d\n", afterNumCoins);
    } else {
        printf("Test Failed. Number of coins: %d\n", afterNumCoins);
    }
    
    
    printf("*** Check that we get into the choice2 else statement  \n");
    printf("*** Check current player should discard hand and draw4  \n");
    printf("*** Check other players with >5 cards should discard hand and draw 4 \n");
    afterNumMinions = 0;
    for (i = 0; i < G.handCount[player]; i++) {
        if (G.hand[player][i] == minion) {
            afterNumMinions++;
        }
    }
    if (afterNumMinions == 0) {
        printf("Test Passed. Number of minion cards in hand: %d\n", afterNumMinions);
    } else {
        printf("Test Failed. Number of minion cards in hand: %d\n", afterNumMinions);
    }
    
    
    
    printf("\n\nEnd of minionCardEffect() tests\n\n");
    
    return 0;
}
