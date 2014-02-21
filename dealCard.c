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

void shuffleDeck(Card * const wDeck){
	size_t i, p1, p2;	//two random position in the deck
	Card temp;
	srand((unsigned int)time(NULL));	//randomise the seed
	for(i=0; i<200; ++i){
		p1 = rand()%CARDS;
		do{	//a loop make sure that two different cards are selected
			p2 = rand()%CARDS;
		}while (p2 == p1);
		temp = wDeck[p1];
		wDeck[p1] = wDeck[p2];
		wDeck[p2] = temp;
	}	//for
}	//function

/*void dealDeck(const Card * const wDeck){
	size_t k1, k2;
	printf("\n\n\n");
	for(k1=0, k2=k1+26; k1<CARDS/2; ++k1, ++k2) {
		printf("Card:%3d %c Color:%2d    ",
			wDeck[k1].face, wDeck[k1].suit+HEART, wDeck[k1].color);
		printf("Card:%3d %c Color:%2d\n ",
			wDeck[k2].face, wDeck[k2].suit+HEART, wDeck[k2].color);
	}	//for
}*/	//function

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
