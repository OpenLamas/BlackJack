#include "card.h"
#include <stdio.h>
#include <stdlib.h> //for rand() and srand
#include <time.h>

void fillDeck(Card * const wDeck){
	 // address pointer (name of the array is constant)
	size_t i;
	for(i=0; i<CARDS; i++){
		wDeck[i].face = i%(CARDS/4);
		wDeck[i].suit = (unsigned int)i/(CARDS/4);
		wDeck[i].color = (unsigned int)i/(CARDS/2);
	} // for
} // function

/****
 *	Make a rand [0, m)
 ****/
int rrand(int m){
	return (int)((double)m * ( rand() / (RAND_MAX+1.0) ));
}

/**
 * Shuffle the deck with the Knuth Shuffle
 */
void shuffleDeck(Card * const wDeck){
	int n = 52;
    Card swappingCard;
    unsigned int randomCardIndex;
    
    srand((unsigned int)time(NULL));
    
	while(n > 1){
        randomCardIndex = rrand(n--);
        swappingCard = wDeck[randomCardIndex];
        wDeck[randomCardIndex] = wDeck[n];
        wDeck[n] = swappingCard;
    }
}	//function

Card drawCard(Card dk[]){
	//search for the firs non-empty place in the deck
	//copy the card and return it, meanwhile fill the
	//face value to be EMPTY
	Card temp;
	int i;
	
	for(i=0; i<CARDS; i++){
		if(dk[i].face != EMPTY) break;
	}	//for
	temp = dk[i];
	dk[i].face = EMPTY;
	return temp;
}
