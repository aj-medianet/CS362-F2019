//
//  randomtestcard3.c
//  dominion
//
//  Created by Andrew Joseph 
//  Copyright © 2019 Andrew Joseph. All rights reserved.
//

// random test tribute function - 70% statement and branch coverage

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
    //return 2;
    return (rand() % (99 - 10)) + 10;
}

int getHandCount() {
    //return 2;
    return rand() % MAX_PLAYERS;
}

enum CARD getRandomCard() {
    return (enum CARD) (rand() % 27);
}


int main() {
    srand( (unsigned int) time(NULL));
    int i, j, p, fuzz;
    int seed = 1000;
    int numPlayer;
    int player1, player2, p2c1, p2c2;
    enum CARD card;
    int r;
    int k[10];
    
    
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
    
    
    printf("\n\n***************************************\n");
    printf("*** Random Testing tributeCard() ***\n");
    printf("*****************************************\n");
    
    // how many times we want to run the tests
    for (fuzz = 0; fuzz < 5; fuzz++) {
        printf("\n**Fuzz: %d**\n\n", fuzz);
        
        // init k to -1 for a fresh deck
        for (i = 0; i < 10; i++) {
            k[i] = -1;
        }
        
        numPlayer = getNumPlayers();
        
        // get card deck
        i = 0;
        int uniqueFlag;
        int randNum;
        for (i = 0; i < 10; i++) {
            do {
                uniqueFlag = 1;
                card = getRandomCard();
                
                for (j = 0; j < i && uniqueFlag == 1; j++) {
                    if (k[j] == card) {
                        uniqueFlag = 0;
                    }
                }
            } while (uniqueFlag != 1);
            k[i] = card;
        }
        
        
        printf("test print k:\n");
        for (i = 0; i < 10; i++) {
            printf("k[%d] = %d\n", i, k[i]);
        }
        
        // setup the game state
        int tributeRevealedCards[2] = {-1, -1};
        memset(&G, 23, sizeof(struct gameState));   // clear the game state
        r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
        
        // setup all the players hands
        for (p = 0; p < numPlayer; p++) {
            G.handCount[p] = getHandCount();
            
            for (i = 0; i < G.handCount[p]; i++) {
                randNum = rand() % 10;
                //printf("randNUM: %d\n", randNum);
                G.hand[p][i] = k[randNum];
            }
        }
        
        
        //loop through all the players and test them vs the next player
        for (p = 0; p < numPlayer - 1; p++) {
            
            printf("\n\n** Player: %d **\n\n", p);
            
            player1 = p;
            player2 = p + 1;
            
            /*
            printf("\n\nplayer cards:\n");
            for (i = 0; i < G.handCount[player1]; i++) {
                printf("p1 %d\n", G.hand[player1][i]);
                printf("p2 %d\n", G.hand[player2][i]);
            }
             */
            
            
            
      
            G.discardCount[player2] = rand() % MAX_PLAYERS;
            G.deckCount[player2] = rand() % MAX_PLAYERS;
            
            //setup a before count so we can check after the call
            int beforeNumCoins = G.coins; // get num of coins for before call count
            int beforeNumActions = G.numActions;
            int beforeNumCards = G.handCount[player1];
            
            printf("Before num coins: %d\n", beforeNumCoins);
            printf("Before num actions: %d\n", beforeNumActions);
            printf("Before num cards: %d\n", beforeNumCards);
            
            //get player2's top two cards
            p2c1 = G.hand[player2][0];
            p2c2 = G.hand[player2][1];
            
            
            
            //printf("p2c1: %d\n", p2c1);
            //printf("p2c2: %d\n", p2c2);
            
            printf("\n\n Tribute Call\n\n");
            
            tributeCard(&G);
            
            printf("After num coins: %d\n", G.coins);
            printf("After num actions: %d\n", G.numActions);
            printf("After num cards: %d\n", G.handCount[p]);
            
            printf("\n\n");
            
            // check to see if the players top 2 cards are the same or not
            if (p2c1 == p2c2) {
                // if they're the same, only count 1 - find out what the output should be
                if (p2c1 == copper || p2c1 == silver || p2c1 == gold) {
                    beforeNumCoins++;
                } else if (p2c1 == estate || p2c1 == duchy || tributeRevealedCards[i] == province || tributeRevealedCards[i] == gardens || tributeRevealedCards[i] == great_hall) {
                    beforeNumCards++;
                } else {
                    beforeNumActions++;
                }
            } else {
                // if they're different play both
                
                if (p2c1 == copper || p2c1 == silver || p2c1 == gold) {
                    beforeNumCoins++;
                } else if (p2c1 == estate || p2c1 == duchy || p2c1 == province || p2c1 == gardens || p2c1 == great_hall) {
                    beforeNumCards++;
                } else {
                    beforeNumActions++;
                }
                
                // if they're the same, only count 1 - find out what the output should be
                if (p2c2 == copper || p2c2 == silver || p2c2 == gold) {
                    beforeNumCoins++;
                } else if (p2c2 == estate || p2c2 == duchy || p2c2 == province || p2c2 == gardens || p2c2 == great_hall) {
                    beforeNumCards++;
                } else {
                    beforeNumActions++;
                }
            }
            
            //print the results
            if (beforeNumCoins == G.coins) {
                printf("Coins Test Passed\n");
            } else {
                printf("Coins Test Failed\n");
            }
            
            if (beforeNumActions == G.numActions) {
                printf("Actions Test Passed\n");
            } else {
                printf("Actions Test Failed\n");
            }
            
            if (beforeNumCards == G.handCount[player1]) {
                printf("Cards Test Passed\n");
            } else {
                printf("Cards Test Failed\n");
            }
            
            
        }
    }
    
    printf("\n\nEnd of random test for tributeCard()\n\n");
    
    return 0;
}

