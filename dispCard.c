#include "card.h"
#include <stdio.h>

#ifdef _WIN32
#include <Windows.h>
#endif

/**
 *  Display a card in one line
 * 
 *  Args: offset => position of the card in the hand (first is 0)
 **/

void displayMiniCard(Card card, int offset, enum WHO who){
#ifdef UTF8_DISPLAY
	const char *cardSymbole[] = {"\u2660", "\u2665", "\u2666", "\u2663"};
#else
	const char *cardSymbole[] = {"\x03", "\x06", "\x04", "\x05"};
#endif
	const char *faceName[]={"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    
    gotoxy(10 + 4*offset, who);
    printf("%s", cardSymbole[card.suit]);
    printf("%s", faceName[card.face]);
}

/**
 *  Display the name of each player (nbPlayers [1,5])
 */
void displayGameBoard(int nbPlayers){
    int i;
    
    clearScreen();
    gotoxy(0, 0);
    printf("Dealer  :");
    gotoxy(35, 0);
    printf("Points:");
    
    for(i=0; i<nbPlayers; ++i){
        gotoxy(0, i+1);
        printf("Player%d :", i+1);
        gotoxy(35, i+1);
        printf("Points:");
    }
    
}

void displayPoints(int points, enum WHO who){
    gotoxy(45, who);
    printf("%d", points);
}

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

void clearLine(short linenum){
	gotoxy(0,linenum);
	printf("%80C", ' ');
	gotoxy(0, linenum);
}
