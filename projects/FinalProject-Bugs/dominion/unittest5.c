//
//  unittestbug5.c
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
    int player = 0;
    int seed = 1000;
    int numPlayer = 2;
    int r;
    int k[10] = {minion, estate, council_room, feast, gardens, mine
        , remodel, smithy, village, great_hall};
    struct gameState G;

    int estates[MAX_HAND];
    
    for (i = 0; i < MAX_HAND; i++)
    {
        estates[i] = estate;
    }
    
    
    printf("\n\n**************************\n");
    printf("*** Testing scoreFor() ***\n");
    printf("**************************\n\n");
    
    printf("testing: In scoreFor() function, discardCount is being used incorrectly for the deck count for loop\n");
    
    // setup the game state
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
    
    // setup count variables to control how many iterations each for loop goes through
    G.handCount[player] = 5;
    G.discardCount[player] = 5;
    G.deckCount[player] = 10;
    
    memcpy(G.hand[player], estates, sizeof(int) * 5); // set all players hand cards to estates
    
    // set all players discard cards to estate
    for (i = 0; i < 5; i++) {
        G.discard[player][i] = estate;
    }
    
    // set all players deck cards to estate
    for (i = 0; i < 10; i++) {
        G.deck[player][i] = estate;
    }
    
    // call function and set it to score variable
    int score = scoreFor(player, &G);
    
    // score should be 20 as estate is 1 point each time it goes through each loop
    printf("*** Score should equal 20 ***\n");
    
    // print results
    if (score == 20) {
        printf("Test passed. Score: %d\n", score);
    } else {
        printf("Test failed. Score: %d\n", score);
    }
    
    // end test
    printf("\n\n>>>>>> End of scoreFor() tests <<<<<<\n\n");
    
    return 0;
}
