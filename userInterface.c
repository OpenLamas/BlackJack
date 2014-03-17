#include "card.h"
#include <stdio.h>


//this function asks the user to answer either 'y' or 'n'
//for continuing the game
char moreGame(void){
	char c;
	do{
		gotoxy(0, MORE);
		clearLine(MORE);
		fflush(stdin);
		printf("More game ? (y/n): ");
		scanf("%c", &c);
	}while(c!='y' && c!='n');
	return c;
}//function

char moreCard(void){
	char c;
	do{
		gotoxy(0,MORE);
		clearLine(MORE);
		printf("More Card? (y/n): ");
		scanf("%c", &c);
	}while(c!='y' && c!='n' && c!='c');
	return c;
}

//function askBid() return a number that the player
//wants to bid for the next game

int askBid(Player p){
	int bid;
	do{
		gotoxy(0,BID);
		printf("You have your points: %d. Your bid(5 to 25): ",p.points);
		scanf("%d", &bid);
	}while((bid<5 || bid>25) && bid < p.points);
	return bid;
}

int showHand(Card hand[], enum WHO who){
    int i, j = 0, ace = 0, points = 0;
    
    // For each card in the hand
    for(i=0; i<HANDSIZE; ++i){
        if(hand[i].face != EMPTY){              /* If there is actualy a card in the slot */
            displayMiniCard(hand[i], i-j, who);   /* We display the card */
            
            if (hand[i].face == 0)              /* If the card is an ace, we store if for later*/
                ace++;
            else if (hand[i].face < 10 && hand[i].face != 0) /* If the card is between 2 and 10, points = value */
                points += hand[i].face + 1;
            else                                /* If it is faces cards, points = 10 */
                points += 10;
        } else {
            j++;                                /* If we have an empty card, we decrease the offset of the display */
        }
    }
    
    if(ace > 0 && (points + 11) <= 21){                       /* If +11 isn't to much*/
        points += 11;
        ace--;
    }
    
    points += ace;                              /* every other ace = 1*/
    
    displayPoints(points, who);
    
    return points;
}