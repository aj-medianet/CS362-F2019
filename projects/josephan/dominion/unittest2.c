/*
 * author Andrew Joseph
 * 1/3/19
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
    for (i = 0; i < MAX_HAND; i++)
    {
        coppers[i] = copper;
        silvers[i] = silver;
        golds[i] = gold;
    }
    
    
    //printf ("TESTING updateCoins():\n");
    printf("**********************************\n");
    printf("*** Testing minionCardEffect() ***\n");
    printf("**********************************\n");
    
    // setup the game state
    int choice1 = 0;
    int choice2 = 0;
    int handPos = 0;
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
    
    int beforeNumActions = G.numActions; // get num of actions for before call count
    int beforeNumMinions = 0; // count num of minions in hand
    for (i = 0; i < G.handCount[player]; i++) {
        if (G.hand[player][i] == minion) {
            beforeNumMinions++;
        }
    }
 
    printf("\n****************************\n");
    printf("*** Testing choice1 == 1 ***\n");
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
    
    printf("\n\nEnd of minionCardEffect() tests\n\n");
    
    return 0;
}
