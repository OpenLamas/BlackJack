#include "blackjack.h"

/**
 *  Initialize the array of player with 100 points for real player
 *  and -1 for non-player
 */
void initPlayersPoints(Player listPlayers[], int numberPlayers){
    int i;
    
    for(i=0; i<MAX_PLAYER; ++i){
        if (i < numberPlayers)
            listPlayers[i].points = 100;
        else
            listPlayers[i].points = -1;
    }
}

/**
 *      Get bids for all players
 */
void getBids(Player listPlayers[]){
    int i;
    
    for(i=0; i<MAX_PLAYER; ++i)
        if(listPlayers[i].points != -1)
            askBid(i+1, &listPlayers[i]);
}

/**
 *      Initialize the hand of all Players
 */
void initPlayersHand(Player listPlayers[]){
    int i,j;
    
    for(i=0; i<MAX_PLAYER; ++i)
        for(j=0; j<HANDSIZE; ++j)
            listPlayers[i].hand[j].face = EMPTY;
}

/**
 *      Initialize the hand of the dealer
 */

void initDealerHand(Player *dealer){
    int j;
    
    for(j=0; j<HANDSIZE; ++j)
        dealer->hand[j].face = EMPTY;
}

/**
 *      AI of the Dealer  (Following Hit Soft 17 or Stand Soft 17 see card.h)
 */
void dealerMoves(Player *dealer, Card deck[]){
#ifndef HS17
    while (handPoints(dealer->hand) < 17){
        serveCard(dealer, deck, DEALER, 1);
    }
#else
    while (soft17HandPoints(dealer->hand) < 17){
        serveCard(dealer, deck, DEALER, 1);
    }
#endif
}

/**
 *      Add or Remove chips from the players
 */
void givePoints(Player listPlayers[], int dealerPoints){
    int i;
    
    for (i=0; i<MAX_PLAYER; ++i) {
        if(listPlayers[i].points != -1){
            if(handPoints(listPlayers[i].hand) > BLACKJACK || (dealerPoints <= BLACKJACK && handPoints(listPlayers[i].hand) < dealerPoints)){
                listPlayers[i].points -= listPlayers[i].bid;
            } else {
                listPlayers[i].points += listPlayers[i].bid * specialProfit(listPlayers[i].hand);
            }
        }
    }
}

/**
 *      Calculate the coefficient of winning
 */
int specialProfit(Card hand[]){
    int winningCoef = 2, i, j;
    
    int redCard=0, blackCard=0, seven=0, nbCard=0;
    
    unsigned char htStore[HANDSIZE];
    unsigned char htKey[HANDSIZE];
    
    for(i=0; i<HANDSIZE; ++i){                          /* We init the hashtable */
        htKey[i] = EMPTY;
        htStore[i] = 0;
    }
    
    for (i=0; i<HANDSIZE; ++i){                         /* For each card in the hand */
        if(hand[i].face != EMPTY){
            nbCard++;
            
            if(hand[i].color == 0 && hand[i].face < 10)
                blackCard++;
            else if(hand[i].color == 1 && hand[i].face < 10)
                redCard++;
            
            if(hand[i].face == 6)
                seven++;
            
            for(j=0; j<HANDSIZE; ++j){
                if(htKey[j] != EMPTY && htKey[j] == hand[i].face){
                    htStore[j]++;
                    break;
                } else if(htKey[j] == EMPTY){
                    htKey[j] = hand[i].face;
                    htStore[j]++;
                }
            }
        }
    }
    
    if(seven == 3){
        winningCoef = 10;
    } else if(handPoints(hand) == 21){
        if(nbCard > 4) {
            winningCoef = 10;
        } else {
            for(j=0; j<HANDSIZE; ++j){
                if(htStore[j] > 1){
                    winningCoef = 6;
                    break;
                }
            }
        }
        
        if(winningCoef == 2 && (redCard == nbCard || blackCard == nbCard))
            winningCoef = 4;
    } else if(nbCard > 4){
        winningCoef = 4;
    }
    
    return winningCoef;
}
