#include "blackjack.h"
#include "stdio.h"  // printf(), fflush(), scanf()
#include "stdlib.h" // system()

#ifdef _WIN32
#include <Windows.h> // gotoxy()...
#endif


#ifdef _WIN32
void clearScreen(void){
	system("cls");
}
#else
void clearScreen(void){
	system("clear");
}
#endif

/**
 *      Get the number of player from the user [1, MAX_PLAYER]
 *
 *  Return: the number of players
 */
int askNumberPlayer(void){
    int numberPlayer;
    
    do{
        gotoxy(0, MORE);
        printf("How many player will play? (1 to 5): ");
        fflush(stdin);
        scanf("%d", &numberPlayer);
    } while (numberPlayer<1 || numberPlayer>MAX_PLAYER);
    return numberPlayer;
}

/**
 *      Ask the user for a new game
 *
 *  Return: (y|n) choice of the user
 */
char moreGame(void){
	char c;
	do{
		gotoxy(0, MORE);
		clearLine(MORE);
		fflush(stdin);
		printf("More game ? (y/n): ");
		scanf("%c", &c);
	} while(c!='y' && c!='n');
	return c;
}

/**
 *      Print the bye message for the user
 *
 *          (It's here to remove all interaction with the screen
 *          outside of the userInterface.c)
 */
void byeMessage(void){
    printf("See you next time !\n");
}

/**
 *      Move the cursor to a given place (Origin: top-left corner (0,0) )
 */
#ifdef _WIN32
void gotoxy(short x, short y){
	HANDLE hStdout;
	COORD position;
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	position.X = x; position.Y = y;
	SetConsoleCursorPosition(hStdout, position);
}
#else
void gotoxy(short x, short y){
    printf("\033[%d;%dH", y+1, x+1);
}
#endif

/**
 *      Clear the given line
 *          It fill the line with 80 spaces
 */
void clearLine(short linenum){
	gotoxy(0,linenum);
	printf("%80C", ' ');
	gotoxy(0, linenum);
}

/**
 *      Ask the player if he want more chips to play again
 *      
 *      If the player can't (and doesn't want) to play anymore
 *      points = -1 (out of the game)
 */
void rebuy(Player listPlayers[]){
    int i;
    char c;
    
    for(i=0; i<MAX_PLAYER; ++i){
        if (listPlayers[i].points != -1 && listPlayers[i].points < 20) {
            do {
                gotoxy(0, BID);
                printf("Player%d, need more chips? (y/n): ", i+1);
                fflush(stdin);
                scanf("%c", &c);
            } while(c != 'y' || c != 'n');
            
            if (c == 'y')
                listPlayers[i].points += 100;
            else if(listPlayers[i].points < 5)
                listPlayers[i].points = -1;
        }
    }
}

/**
 *  Display the name of each player (nbPlayers [1,5]) and the dealer
 */
void displayGameBoard(int nbPlayers){
    int i;
    
    clearScreen();
    gotoxy(0, 0);
    printf("Dealer  :");
    gotoxy(35, 0);
    printf("Points:");
    
    for(i=1; i<=nbPlayers; ++i){
        gotoxy(0, i);
        printf("Player%d :", i);
        gotoxy(35, i);
        printf("Points:");
    }
    
}

/**
 *      Ask the Player if we want one more card
 *
 *  Return: (y|n) choice of the user
 */
char moreCard(enum WHO who){
	char c;
	do{
		clearLine(MORE);
        gotoxy(0,MORE);
		printf("Player%d, More Card? (y/n): ", who);
		scanf("%c", &c);
	} while(c != 'y' && c != 'n');
	return c;
}

/**
 *  Tell to the player he is above 21 points
 */
void showOutOfBound(enum WHO who){
    gotoxy(48, who);
    printf("OUT!");
}

/**
 *  Tell to the player he did a BlackJack
 */
void showBlackJack(enum WHO who){
    gotoxy(48, who);
    printf("BLACKJACK!");
}

/**
 *  Show his hand to the user
 */
void showHand(Card hand[], enum WHO who){
    int i, j = 0;
    
    for(i=0; i<HANDSIZE; ++i){                      /* For each card in the hand                                        */
        if(hand[i].face != EMPTY)                   /* If there is actualy a card in the slot                           */
            displayMiniCard(hand[i], i-j, who);     /* We display the card                                              */
        else
            j++;                                    /* If we have an empty card, we decrease the offset for the display */
    }
    
    displayPoints(handPoints(hand), who);           /* We display the points of the hand                                */
}

/**
 *      Display a card in one line
 *
 *  Args: offset => position of the card in the hand (first is 0)
 **/

void displayMiniCard(Card card, int offset, enum WHO who){
#ifdef UTF8_DISPLAY
	const char *cardSymbole[] = {"\u2660", "\u2665", "\u2663", "\u2666"};
#else
	const char *cardSymbole[] = {"\x03", "\x06",  "\x05", "\x04"};
#endif
	const char *faceName[]={"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    
    gotoxy(10 + 4*offset, who);
    printf("%s", cardSymbole[card.suit]);
    printf("%s", faceName[card.face]);
}

/**
 *      Display the points of the player
 */
void displayPoints(int points, enum WHO who){
    gotoxy(45, who);
    printf("%d", points);
}

/**
 *      Ask for a specific player, how much he want to bet
 */
void askBid(enum WHO who, Player *p){
	do{
        clearLine(BID);
		gotoxy(0,BID);
		printf("Player%d have your points: %d. Your bid(5 to 25): ", who, p->points);
		scanf("%d", &p->bid);
	}while((p->bid<5 || p->bid>25) && p->bid < p->points);
}

/**
 *      Print the name(s) of the winner(s)
 */
void showWinner(Player listPlayers[], int dealerScore){
    int i;
    int winnerCounter=0;
    
    for(i=0; i<MAX_PLAYER; ++i){
        if (handPoints(listPlayers[i].hand) <= BLACKJACK && (handPoints(listPlayers[i].hand) > dealerScore || dealerScore > BLACKJACK)){
            gotoxy(9*winnerCounter, WM);
            printf("Player%d,", i+1);
            winnerCounter++;
        }
    }
    
    if(winnerCounter == 0){
        gotoxy(0, WM);
        printf("The Dealer Win !");
    } else {
        gotoxy(9*(winnerCounter)-2, WM);
        printf(" WIN !");
    }
    
    
    
}
