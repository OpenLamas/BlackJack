#include "blackjack.h"

/**
 *  Fill the deck with CARDS cards
 */

void fillDeck(Card * const wDeck){
	int i;
	for(i=0; i<CARDS; i++){
		wDeck[i].face = i%(CARDS/4);
		wDeck[i].suit = (unsigned int)i/(CARDS/4);
		wDeck[i].color = (unsigned int)i/(CARDS/2);
	}
}

/**
 * Shuffle the deck with the Knuth Shuffle
 */
void shuffleDeck(Card * const wDeck){
	int n = CARDS;
    Card swappingCard;
    unsigned int randomCardIndex;
    
	while(n > 1){
        randomCardIndex = rrand(n--);
        swappingCard = wDeck[randomCardIndex];
        wDeck[randomCardIndex] = wDeck[n];
        wDeck[n] = swappingCard;
    }
}

/**
 *      Pick the given number of card from the top of the deck
 */
void serveCard(Player *player, Card deck[], enum WHO who, int numberOfCards){
    int i;
    
    for(i=0; i<HANDSIZE; ++i){
        if(numberOfCards == 0)
            break;
        
        if(player->hand[i].face != EMPTY){
            player->hand[i] = drawCard(deck);
            numberOfCards--;
        }
    }
    
    showHand(player->hand, who);
}

/**
 *      Calculate the number of point of the given hand
 *
 *  Return: Points
 */

int handPoints(Card hand[]){
    int points=0, i, ace=0;
    
    for(i=0; i<HANDSIZE; ++i){
        if(hand[i].face != EMPTY){
            if (hand[i].face == 0)                       /* If the card is an ace, we store if for later            */
                ace++;
            else if (hand[i].face < 10)                  /* If the card is between 2 and 10, points = facial value  */
                points += hand[i].face + 1;
            else                                         /* If it is a face card, points = 10                       */
                points += 10;
        }
    }
    
    if(ace > 0 && (points + 11) <= 21){                  /* If +11 isn't to much                                    */
        points += 11;
        ace--;
    }
    
    points += ace;                                       /* every other ace = 1                                     */
    return points;
}

/**
 *      Calculate the number of point of the given hand
 *      (if the hand is 17 with a ace worth 11, we return 7)
 *
 *  Return: Points
 */

int soft17HandPoints(Card hand[]){
    int points=0, i, ace=0;
    
    for(i=0; i<HANDSIZE; ++i){
        if(hand[i].face != EMPTY){
            if (hand[i].face == 0)                       /* If the card is an ace, we store if for later            */
                ace++;
            else if (hand[i].face < 10)                  /* If the card is between 2 and 10, points = facial value  */
                points += hand[i].face + 1;
            else                                         /* If it is a face card, points = 10                       */
                points += 10;
        }
    }
    
    if(ace > 0 && (points + 11) <= 21 && (points + 11) != 11){  /* If +11 isn't to much                             */
        points += 11;
        ace--;
    }
    
    points += ace;                                       /* every other ace = 1                                     */
    return points;
}


/**
 *      Take the card at the top of the deck
 */
Card drawCard(Card dk[]){
	Card temp;
	int i;
	
	for(i=0; i<CARDS; i++)
		if(dk[i].face != EMPTY)
            break;
        
	temp = dk[i];
	dk[i].face = EMPTY;
	return temp;
}
