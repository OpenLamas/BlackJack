#include "card.h"
#include <stdio.h>
#include <stdlib.h>

int main (void) {
	Card deck[CARDS]; //declare an array of of cards
	Player player;
	player.points = 100;	//inatialize the player's point

#ifdef DEBUG
	printf("Symbol of suits: \u2660 \u2665 \u2666 \u2663");
#endif
	
	do{
#ifdef DEBUG
		printf("New Game! \n");
#endif
		clearScreen();
		fillDeck(deck);
		shuffleDeck(deck);
		player.points = playGame(deck, player);
	}while(moreGame()=='y');
	printf("See you next time !\n");
	//deal(deck);
	//makeCardFrame(deck[0]);

	return 0;
}

#ifdef _WIN32
void clearScreen(void){
	system("cls");
}
#else
void clearScreen(void){
	system("clear");
}
#endif

//function definition of the playGame
int playGame(Card dk[], Player p){
	Card dhand[HANDSIZE];
	int i, ppoint, dpoint;

	//ask the player to put a bid
	p.bid = askBid(p);
	
	for(i=0; i<HANDSIZE; ++i){	//empty the hands
		p.hand[i].face = EMPTY;
		dhand[i].face = EMPTY;
	}

	//draw cards (2 for each)
	for(i=0; i<2; ++i){
		p.hand[i] = drawCard(dk);
		dhand[i] = drawCard(dk);
	}
	ppoint = showPlayerHand(p.hand);
	dpoint = showDealerHand(dhand);

	//ask the player for more cards
	while(ppoint < BLACKJACK){
		if( moreCard() == 'y'){	//draw a new card from deck
			p.hand[i++] = drawCard(dk);
			ppoint = showPlayerHand(p.hand);
		}
		else
			break;
	}

	if(ppoint > BLACKJACK) {	//player loses immediately
		gotoxy(0,BID+1); printf("Sorry, you lost. ");
		p.points -= p.bid;
	}

	if(ppoint == BLACKJACK) {	//player gets the blackjack
		gotoxy(0,BID+1); printf("BlackJack !!");
		p.points += p.bid*3;
	}

	if(ppoint < BLACKJACK) {	// player holds
		i=2;
		while(dpoint < ppoint){
			dhand[i++] = drawCard(dk);
			dpoint = showDealerHand(dhand);
		}	//while

		if(dpoint > BLACKJACK){
			gotoxy(0,BID+1); printf("Dealer blowed out !");
			p.points += p.bid;
		}
		else{
			gotoxy(0,BID+1); printf("Sorry, you lost.");
			p.points -= p.bid;
		}	//else
	}	//end of if


	//if the player holds, the dealer has to draw cards
	//until his point is greater or he got bowed
	//calculate for the result (Update player's point)

	return p.points;	//return players point
}
