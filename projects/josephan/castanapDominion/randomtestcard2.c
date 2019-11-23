//
//  randomtestcard2.c
//  dominion
//
//  Created by Andrew Joseph
//  Copyright © 2019 Andrew Joseph. All rights reserved.
//

// random test minion function 70% statement and branch coverage

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <time.h>
#include <stdlib.h>

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

// assert a == to b
int assertAequalsB(int a, int b) {
    if (a == b) {
        return 1;
    }
    return 0;
}

int getNumPlayers() {
    return (rand() % (999 - 10)) + 10;
}

int getHandCount() {
    return rand() % MAX_PLAYERS;
}

int main() {
    srand( (unsigned int) time(NULL));
    int i, p, fuzz, c1, c2;
    //int player = 0;
    int seed = 1000;
    int numPlayer;
    int player1 = 0;
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
    
    int choice1;
    int choice2;
    int handPos = 0;
    
    printf("\n\n***************************************\n");
    printf("*** Random Testing minionCardEffect() ***\n");
    printf("*****************************************\n");
    
    // how many times we want to run the tests
    for (fuzz = 0; fuzz < 1000; fuzz++) {
        
        printf("\n**Fuzz: %d**\n\n", fuzz);
        
        
        //loop through each choice and run the tests
        for (c1 = 0; c1 < 2; c1++) {
            for (c2 = 0; c2 < 2; c2++) {
                choice1 = c1;
                choice2 = c2;
                numPlayer = getNumPlayers();
                
                
                printf("\n\n *** Testing Choice1: %d, Choice2: %d\n", choice1, choice2);
                
                //set up players hands with random hand counts
                for (p = 0; p < numPlayer; p++) {
                    G.handCount[p] = getHandCount();
                }
                
                memset(&G, 23, sizeof(struct gameState));   // clear the game state
                r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
                memcpy(G.hand[player1], minions, sizeof(int) * G.handCount[player1]); // set all p1's cards to minions
                
                //set rest of players hands to coppers
                for (p = 1; p < numPlayer; p++) {
                    memcpy(G.hand[p], coppers, sizeof(int) * G.handCount[p]);
                }
                
                int beforeNumActions = G.numActions; // get num of actions for before call count
                int beforeNumMinions = 0; // count num of minions in hand
                for (i = 0; i < G.handCount[player1]; i++) {
                    if (G.hand[player1][i] == minion) {
                        beforeNumMinions++;
                    }
                }
                
                int beforeNumCoins = G.coins;
                int afterNumCoins;
                
                // call the function we're unit testing
                minionCardEffect(choice1, choice2, &G, handPos, player1);
                
                printf("\n*** Check numActions increases by 1 from %d to %d ***\n", beforeNumActions, beforeNumActions + 1);
                if (beforeNumActions + 1 == G.numActions) {
                    printf("Test Passed. numActions: %d\n", G.numActions);
                } else {
                    printf("Test Failed. numActions: %d\n", G.numActions);
                }
                
                printf("*** Check discard our card from %d to %d ***\n", beforeNumMinions, beforeNumMinions - 1);
                int afterNumMinions = 0;
                for (i = 0; i < G.handCount[player1]; i++) {
                    if (G.hand[player1][i] == minion) {
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
                
                
                /*
                printf("*** Check number of coppers in each players hand against their hand count ***\n");
                for (p = 1; p < numPlayer; p++) {
                    int curPlayerCopperCount = 0;
                    for (i = 0; i < G.handCount[p]; i++) {
                        if (G.hand[p][i] == copper) {
                            curPlayerCopperCount++;
                        }
                    }
                    if (curPlayerCopperCount != G.handCount[p]) {
                        printf("Player Count Test Passed\n");
                    } else {
                        printf("Player Count Test Failed\n");
                    }
                }
                 */
                
                
                
            }
        }
    }
    
    printf("\n\nEnd of random test for minionCardEffect()\n\n");
    
    return 0;
}
