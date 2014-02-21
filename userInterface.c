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

int showPlayerHand(Card ph[]){
	int i, j, playerPoint = 0;
	gotoxy(0,PH);	// the first row for player's hand
	for(i=0, j=0; i<HANDSIZE; ++i, ++j){
		if(ph[i].face != EMPTY){	//not empty entry, display the card
			makeCardFrame(ph[i], i, PLAYER);
			if (ph[i].face < 10)
				playerPoint += (ph[i].face+1);
			else
				playerPoint += 10;
		} else{
			j--;
		}
	}
	gotoxy(0,PP);	// the second row for second Player's point
	printf("Players point: %d", playerPoint);
	return playerPoint;
}	//end function

int showDealerHand(Card ph[]){	
	int i, j, point = 0;
	gotoxy(0,DH);	// the fourth row for dealer's hand
	for(i=0, j=0; i<HANDSIZE; ++i,++j){
		if(ph[i].face != EMPTY){	//not empty entry, display the card
			makeCardFrame(ph[i], j, DEALER);
			if (ph[i].face < 10)
				point += (ph[i].face+1);
			else
				point += 10;
		} else {
			j--;
		}
	}
	gotoxy(0,DP);	// the fifth row for dealer's point
	printf("Dealer's point: %d", point);
	return point;
}