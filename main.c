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
	int i, ppoint, dpoint, j, number_of_card = 0, double_hand = 15, h;

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

	for (i = 0, j = 0; i < HANDSIZE; i++){							//Loop for defining the number of card "7" and also to count the number of card used.
		if (dhand[i].face == 7)
			j++;
		for (h = 0; h < HANDSIZE; h++)
		{
			if (dhand[i].face = dhand[j].face){
				double_hand++;
				if (double_hand == 2) break;
			}
		}

		number_of_card++;
	
	}
	if (number_of_card == 5 && ppoint == 21 ){						//Case if the player has five card with 21 points, points *10
		p.points += p.bid * 10;
	}

	if (number_of_card == 5 && ppoint < 21){
		p.points += p.bid * 4;
	}

	if (j == 3)							//Case if the player has three card 7 in his game, points *10
		p.points += p.bid * 10;

	if (double_hand == 2 && ppoint == 21)
		p.points += p.bid * 6;
	
	//if the player holds, the dealer has to draw cards
	//until his point is greater or he got bowed
	//calculate for the result (Update player's point)

	return p.points;	//return players point
}
