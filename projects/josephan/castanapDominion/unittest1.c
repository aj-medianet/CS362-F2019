/*
 * author Andrew Joseph
 * 11/3/19
 * unittest1.c 
 * unit test for baronCardEffect()
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
    int k[10] = {baron, estate, council_room, feast, gardens, mine
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
    printf("*********************************\n");
    printf("*** Testing baronCardEffect() ***\n");
    printf("*********************************\n");
    
    printf("\n****************************\n");
    printf("*** Testing choice1 == 0 ***\n");
    printf("****************************\n");
    
    // setup the game state
    int choice1 = 0;
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
    
    int beforeNumBuys = G.numBuys;
    int beforeSupplyCount = G.supplyCount[estate];
    int beforePlayerHandCount = G.handCount[player];
    int beforeEstateCount = 0;
    int afterEstateCount = 0;
    
    for (i = 0; i < G.handCount[player]; i++) {
        if ( G.hand[player][i] == estate) {
            printf("estate card found!!\n\n\n");
            beforeEstateCount++;
        }
    }
    
    // call the function we're unit testing
    baronCardEffect(k[0], choice1, &G, player);
    
    printf("\n*** Testing numBuys increases from %d to %d. ***\n", beforeNumBuys, beforeNumBuys + 1);
    if (assertAequalsB(G.numBuys, beforeNumBuys + 1)) {
        printf("numBuys Test Passed. numBuys: %d\n", G.numBuys);
    } else {
        printf("numBuys Test Failed. numBuys: %d\n", G.numBuys);
    }

   
    
    printf("\n*** Check estate supply count went down from %d to %d: ***\n", beforeSupplyCount, beforeSupplyCount - 1);
    if (assertAequalsB(G.supplyCount[estate], beforeSupplyCount - 1)) {
        printf("Test Passed. Estate Supply Count: %d\n", G.supplyCount[estate]);
    } else {
        printf("Test Failed. Estate Supply Count: %d\n", G.supplyCount[estate]);
    }
    
    printf("\n*** Test players hand count increases by 1 from %d to %d ***\n", beforePlayerHandCount, beforePlayerHandCount + 1);
    if (assertAequalsB(beforePlayerHandCount + 1, G.handCount[player])) {
        printf("Test Passed. Hand count: %d\n", G.handCount[player]);
    } else {
        printf("Test Failed. Hand Count: %d\n", G.handCount[player]);
    }
    

    printf("\n*** Check that the player gained 1 estate card from %d to %d ***\n", beforeEstateCount, beforeEstateCount + 1);
    for (i = 0; i < G.handCount[player]; i ++) {
        if (G.hand[player][i] == estate) {
            afterEstateCount++;
        }
    }
    if (beforeEstateCount + 1 == afterEstateCount) {
        printf("Test Passed. Estate Count: %d\n", afterEstateCount);
    } else {
        printf("Test Failed. Estate Count: %d\n", afterEstateCount);
    }
    
    printf("\n*** Check prov & estate supply of 0 to check game over if statement, should return 1 ***\n");
    G.supplyCount[estate] = 1;
    G.supplyCount[province] = 0;
    int gameOver = baronCardEffect(k[0], choice1, &G, player);
    
    if (gameOver == 1) {
        printf("Test Passed. Game over results: %d\n", gameOver);
    } else {
        printf("Test Failed. Game over results: %d\n", gameOver);
    }
    
    
    
    
    printf("\n************************************************************\n");
    printf("*** Testing choice1 == 1 with estate as first card in hand ***\n");
    printf("**************************************************************\n");
    
    int k2[10] = {estate, baron, council_room, feast, gardens, mine
        , remodel, smithy, village, great_hall};
    
    
    // setup the game state
    choice1 = 1;
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k2, seed, &G); // initialize a new game
    beforeNumBuys = G.numBuys;
    beforeSupplyCount = G.supplyCount[estate];
    beforePlayerHandCount = G.handCount[player];
    beforeEstateCount = 0;
    afterEstateCount = 0;
    int beforeNumCoins = G.coins;
    int beforeHandCount = G.handCount[player];
    
    // get the estate count before function is called
    for (i = 0; i < G.handCount[player]; i ++) {
        if ( G.hand[player][i] == estate) {
            beforeEstateCount++;
        }
    }
    
    // call the function we're unit testing
    baronCardEffect(k[0], choice1, &G, player);

    printf("\n*** Testing numBuys increases from %d to %d. ***\n", beforeNumBuys, beforeNumBuys + 1);
    if (assertAequalsB(G.numBuys, beforeNumBuys + 1)) {
        printf("numBuys Test Passed. numBuys: %d\n", G.numBuys);
    } else {
        printf("numBuys Test Failed. numBuys: %d\n", G.numBuys);
    }
    
    printf("\n*** Check that the player lost 1 estate card from %d to %d ***\n", beforeEstateCount, beforeEstateCount - 1);
    for (i = 0; i < G.handCount[player]; i ++) {
        if (G.hand[player][i] == estate) {
            afterEstateCount++;
        }
    }
    if (beforeEstateCount - 1 == afterEstateCount) {
        printf("Test Passed. Estate Count: %d\n", afterEstateCount);
    } else {
        printf("Test Failed. Estate Count: %d\n", afterEstateCount);
    }
    
    printf("\n*** Check we gained 4 coins from %d to %d\n", beforeNumCoins, beforeNumCoins + 4);
    if (G.coins == beforeNumCoins + 4) {
        printf("Test Passed. Coins: %d\n", G.coins);
    } else {
        printf("Test Failed. Coins: %d\n", G.coins);
    }
    
    printf("\n*** Check we decreased hand count from %d to %d\n", beforeHandCount, beforeHandCount - 1);
    if (G.handCount[player] == beforeHandCount - 1) {
        printf("Test Passed. Player Hand Count: %d\n", G.handCount[player]);
    } else {
        printf("Test Failed. Player Hand Count: %d\n", G.handCount[player]);
    }
    
    
    
    
    
    printf("\n*******************************************\n");
    printf("*** Testing choice1 == 1 without estate ***\n");
    printf("*******************************************\n");
    
    // setup the game state
    int k3[10] = {baron, adventurer, council_room, feast, gardens, mine
        , remodel, smithy, village, great_hall};
    
    choice1 = 1;
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k3, seed, &G); // initialize a new game
    beforeNumBuys = G.numBuys;
    beforeSupplyCount = G.supplyCount[estate];
    beforePlayerHandCount = G.handCount[player];
    beforeEstateCount = 0;
    afterEstateCount = 0;
    beforeNumCoins = G.coins;
    
    // get the estate count before function is called
    for (i = 0; i < G.handCount[player]; i ++) {
        if ( G.hand[player][i] == estate) {
            beforeEstateCount++;
        }
    }
    
    baronCardEffect(k[0], choice1, &G, player);
    
    printf("\n*** Testing numBuys increases from %d to %d. ***\n", beforeNumBuys, beforeNumBuys + 1);
    if (assertAequalsB(G.numBuys, beforeNumBuys + 1)) {
        printf("numBuys Test Passed. numBuys: %d\n", G.numBuys);
    } else {
        printf("numBuys Test Failed. numBuys: %d\n", G.numBuys);
    }
    
    
    
    printf("\n*** Check estate supply count went down from %d to %d: ***\n", beforeSupplyCount, beforeSupplyCount - 1);
    if (assertAequalsB(G.supplyCount[estate], beforeSupplyCount - 1)) {
        printf("Test Passed. Estate Supply Count: %d\n", G.supplyCount[estate]);
    } else {
        printf("Test Failed. Estate Supply Count: %d\n", G.supplyCount[estate]);
    }
    
    printf("\n*** Test players hand count increases by 1 from %d to %d ***\n", beforePlayerHandCount, beforePlayerHandCount + 1);
    if (assertAequalsB(beforePlayerHandCount + 1, G.handCount[player])) {
        printf("Test Passed. Hand count: %d\n", G.handCount[player]);
    } else {
        printf("Test Failed. Hand Count: %d\n", G.handCount[player]);
    }
    
    
    printf("\n*** Check that the player gained 1 estate card from %d to %d ***\n", beforeEstateCount, beforeEstateCount + 1);
    for (i = 0; i < G.handCount[player]; i ++) {
        if (G.hand[player][i] == estate) {
            afterEstateCount++;
        }
    }
    if (beforeEstateCount + 1 == afterEstateCount) {
        printf("Test Passed. Estate Count: %d\n", afterEstateCount);
    } else {
        printf("Test Failed. Estate Count: %d\n", afterEstateCount);
    }
    
    
    printf("\n*** Check we gained 4 coins from %d to %d\n", beforeNumCoins, beforeNumCoins + 4);
    if (G.coins == beforeNumCoins + 4) {
        printf("Test Passed. Coins: %d\n", G.coins);
    } else {
        printf("Test Failed. Coins: %d\n", G.coins);
    }
    
    printf("\n*** Check prov & estate supply of 0 to check game over if statement, should return 1 ***\n");
    G.supplyCount[estate] = 0;
    G.supplyCount[province] = 0;
    gameOver = baronCardEffect(k[0], choice1, &G, player);
    
    if (gameOver == 1) {
        printf("Test Passed. Game over results: %d\n", gameOver);
    } else {
        printf("Test Failed. Game over results: %d\n", gameOver);
    }
 
    
    
    
    
    printf("\n\nEnd of baronCardEffect() tests\n\n");

    return 0;
}
