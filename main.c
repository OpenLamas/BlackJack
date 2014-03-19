#include "card.h"
#include <stdio.h>
#include <stdlib.h>

int main (void) {
	Card deck[CARDS]; //declare an array of of cards
	Player player;
	player.points = 100;	//inatialize the player's point
    int numberPlayers = 0;
    Player listPlayers[MAX_PLAYER];

	do{
		clearScreen();                                  /* We start by clearing the screen */
		fillDeck(deck);                                 /* We fill the deck with the cards */
		shuffleDeck(deck);                              /* We shuffle the deck */
        if(numberPlayers == 0){                       /* If the number of players is not yet defined */
          numberPlayers = askNumberPlayer();          /* We ask for the number of player */
          initPlayersPoints(listPlayers, numberPlayers);    /* We initialize the array of player */
        } else {
          rebuy(listPlayers);                         /* Check if (a|some) player(s) need more chips */
        }
		newGame(numberPlayers, listPlayers, deck);    /* We run a new game */
	} while(moreGame()=='y');
	byeMessage();

	return 0;
}

/**
 *	Make a rand [0, m)
 */
int rrand(int m){
	return (int)((double)m * ( rand() / (RAND_MAX+1.0) ));
}

/**
 *      Run a full single game
 */
void newGame(int numberPlayer, Player listPlayers[], Card deck[]){
    int i;
    Player dealer;
    
    getBids(listPlayers);                                           /* We get bids for all the players              */
    displayGameBoard(numberPlayer);
    initPlayersHand(listPlayers);
    
    initDealerHand(&dealer);
    serveCard(&dealer, deck, DEALER, 2);
    
    for(i=0; i<numberPlayer; ++i){                                  /* For each player                              */
        serveCard(&listPlayers[i], deck, i, 2);                     /* We get 2 cards                               */
        
        
        while (handPoints(listPlayers[i].hand) < BLACKJACK){        /* While the player has less than a blackjack   */
            if(moreCard() == 'y')                                   /* If he want another card                      */
                serveCard(&listPlayers[i], deck, i, 1);
            else                                                    /* If not, stop                                 */
                break;
        }
        
        if(handPoints(listPlayers[i].hand) > BLACKJACK)             /* If the player has more than 21 points        */
            showOutOfBound(i);                                      /* We can already tell him he lost              */
        else if(handPoints(listPlayers[i].hand) == BLACKJACK)       /* Else if the player has a BlackJack           */
            showBlackJack(i);                                       /* We can tell him now too                      */
    }
    
    dealerMoves(&dealer, deck);                                     /* It's time the the dealer to play             */
    
    givePoints(listPlayers, handPoints(dealer.hand));               /* We calculate win/lose chips and              */
                                                                    /* show it to the players                       */
}
