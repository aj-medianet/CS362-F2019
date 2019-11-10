/*
 * author Andrew Joseph
 * 11/3/19
 * unittest4.c
 * unit test for tributeCardEffect()
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
    printf("\n\n**********************************\n");
    printf("*** Testing tributeCardEffect() ***\n");
    printf("***********************************\n");
    
    // setup the game state
    int tributeRevealedCards[2] = {-1, -1};
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
    G.handCount[player1] = 5;
    G.handCount[1] = 5;
    memcpy(G.hand[player1], minions, sizeof(int) * 5); // set all p1's cards to minions
    
    
    printf("\n*** Player 2 has all treasure cards (coppers) ***\n");
    memcpy(G.hand[player2], coppers, sizeof(int) * 5); // set all p2's cards to coppers
    
    int beforeNumCoins = G.coins; // get num of actions for before call count
    
    tributeCardEffect(&G, player1, player2, tributeRevealedCards);
    
    
    printf("*** Check number of coins. Should go from %d to %d \n", beforeNumCoins, beforeNumCoins+2);
    if (beforeNumCoins + 2 == G.coins) {
        printf("Test Passed. Number of coins: %d\n", G.coins);
    } else {
        printf("Test Failed. Number of coins: %d\n", G.coins);
    }
    
    
    printf("\n*** Player 2 has all action cards (ambassadors) ***\n");
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
    G.handCount[player1] = 5;
    G.handCount[1] = 5;
    memcpy(G.hand[player2], ambassadors, sizeof(int) * 5); // set all p2's cards to ambassadors (action)
    
    int beforeNumActions = G.numActions;
    int tributeRevealedCards1[2] = {-1, -1};
    
    tributeCardEffect(&G, player1, player2, tributeRevealedCards1);
    
    printf("*** Check number of actions. Should go from %d to %d \n", beforeNumActions, beforeNumActions+2);
    if (beforeNumActions + 2 == G.numActions) {
        printf("Test Passed. Number of actions: %d\n", G.numActions);
    } else {
        printf("Test Failed. Number of actions: %d\n", G.numActions);
    }
    
    
    
    printf("\n*** Player 2 has all victory cards (estates) ***\n");
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
    G.handCount[player1] = 5;
    G.handCount[1] = 5;
    memcpy(G.hand[player2], estates, sizeof(int) * 5); // set all p2's cards to estates (victory)
    
    int beforeNumCards = G.handCount[player1];
    int tributeRevealedCards2[2] = {-1, -1};
    
    tributeCardEffect(&G, player1, player2, tributeRevealedCards2);
    
    printf("*** Check number of cards. Should go from %d to %d \n", beforeNumCards, beforeNumCards+2);
    if (beforeNumCards + 2 == G.handCount[player1]) {
        printf("Test Passed. Number of cards: %d\n", G.handCount[player1]);
    } else {
        printf("Test Failed. Number of cards: %d\n", G.handCount[player1]);
    }
    
    
    
    
    
    
    printf("\n\nEnd of tributeCardEffect() tests\n\n");
    
    return 0;
}
