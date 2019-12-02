//
//  unittestbug6.c
//  dominion
//
//  Created by Andrew Joseph on 12/1/19.
//  Copyright © 2019 Andrew Joseph. All rights reserved.
//

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
    int player = 0, bonus = 0;
    int seed = 1000;
    int numPlayer = 2;
    int r;
    int k[10] = {minion, estate, council_room, feast, gardens, mine
        , remodel, smithy, village, great_hall};
    struct gameState G;

    int feasts[MAX_HAND];
    
    for (i = 0; i < MAX_HAND; i++) {
        feasts[i] = feast;
    }
    
    
    printf("\n\n***************************************\n");
    printf("*** Testing cardEffect() case feast ***\n");
    printf("***************************************\n\n");
    
    // setup the game state
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
    memcpy(G.hand[player], feasts, sizeof(int) * 5); // set all players hand cards to feasts
    int choice2 = 0, choice3 = 0;
    
    // setup supply to have the cards we want
    G.supplyCount[adventurer] = 5;
    int beforeAdvCount = 0, afterAdvCount = 0;
    
    for (i = 0; i < G.handCount[player]; i++) {
        if (G.hand[player][i] == adventurer) {
            beforeAdvCount++;
        }
    }
    
    
    // test for valid input, mine card which costs 5
    int choice1 = 11;
    cardEffect(9, choice1, choice2, choice3, &G, 1, &bonus);
    
    for (i = 0; i < G.handCount[player]; i++) {
        if (G.hand[player][i] == adventurer) {
            afterAdvCount++;
        }
    }
    
    // after adventure card count should be 1 more than before adventure card count
    printf("*** After adventure count should be 1 more than before adventure count ***\n");
    if (afterAdvCount == beforeAdvCount + 1) {
        printf("Test passed. Before adventure count: %d, After adventure count: %d\n", beforeAdvCount, afterAdvCount);
    } else {
        printf("Test failed. Before adventure count: %d, After adventure count: %d\n", beforeAdvCount, afterAdvCount);
    }
    
    // set choice 1 to adventurer, which costs 6
    // this wil lbe used as invalid input
    choice1 = 7;
    
    printf("\n\n*** Testing for invalid input infinite loop ***\n");
    printf("*** Put a count in while loop so we only allow to run 50 times before we break out of infinite loop ***\n\n");
    printf("If we get 50 print statements, we know we've hit an infinite loop:\n\n");
    // invalid input should set us into an infinite loop
    int infiniteLoop = cardEffect(9, choice1, choice2, choice3, &G, 1, &bonus);
    
    if (infiniteLoop == 0) {
        printf("\n\n*** Test passed. No infinite loop ***\n");
    } else {
        printf("\n\n*** Test failed. We had an infinite loop ***\n");
    }

    
    // end test
    printf("\n\nEnd of cardEffect() case feast tests\n\n");
    
    return 0;
}
