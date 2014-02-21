#include "card.h"
#include <stdio.h>

#ifdef _WIN32
#include <Windows.h>
#endif

#define VSIZE 10
#define HSIZE 11

void makeCardFrame(Card c, int offset, enum WHO who){
	size_t i, k;
	int XStart = (HSIZE*offset) + offset;
	int YStart = ((who == PLAYER) ? PH : DH);
	
	// Top of the card
#ifdef _WIN32
	gotoxy(XStart+1, YStart+1);
#else
	gotoxy(XStart+1, YStart);
#endif
	for(i=0; i<HSIZE-2; ++i) printf("%c", HL); // horizontal line

	// Body of the card
	for(k=0; k<VSIZE-2; ++k) {
		
		// Left Side
		gotoxy(XStart, YStart+k+1);
		putchar(k == 0 ? TL : VL); // Top corner or vertical line
		
		// Right Side
		gotoxy(XStart+HSIZE-1, YStart+k+1);
		putchar(k == 0 ? TR : VL); // Top corner or vertical line
		
		putchar('\n'); // make a new line
	}
	
	// Bottom of the card
	gotoxy(XStart, YStart+VSIZE-1);
	putchar (BL); // Left corner
	for(i=0; i<HSIZE-2; ++i) putchar (HL); // Line
	putchar(BR); // Right corner
	putchar('\n'); //make a new line
	
	//Show card's name & symbol, the first thing is to move
	printSymboles(c, XStart, YStart);

}

void printSymboles(Card c, int XStart, int YStart){
#ifdef UTF8_DISPLAY
	const char *cardSymbole[] = {"\u2660", "\u2665", "\u2666", "\u2663"};
#else
	const char *cardSymbole[] = {"\x03", "\x06", "\x04", "\x05"};
#endif
	const char *faceName[]={"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
	const char *symbole = cardSymbole[c.suit];
	
	int i;
	
	// Print card number in Top left and bottom right
	gotoxy (XStart+1, YStart+2);
	printf("%s", faceName[c.face]);
	
	if(c.face == 9)
		gotoxy (XStart+HSIZE-3, YStart+VSIZE-2);
	else
		gotoxy (XStart+HSIZE-2, YStart+VSIZE-2);
	
	printf("%s", faceName[c.face]);
	if(c.face == 0) { // If As
		if (c.suit == 0) {
			gotoxy (XStart+HSIZE/2, YStart+3);
			printf("%s", ",");
			gotoxy (XStart+HSIZE/2-1, YStart+4);
			printf("%s", "/ \\");
			gotoxy (XStart+HSIZE/2-2, YStart+5);
			printf("%s", "(_ _)");
			gotoxy (XStart+HSIZE/2-1, YStart+6);
			printf("%s", "/_\\");
		} else if (c.suit == 1) {
			gotoxy (XStart+HSIZE/2-1, YStart+3);
			printf("%s", "_ _");
			gotoxy (XStart+HSIZE/2-2, YStart+4);
			printf("%s", "/ v \\");
			gotoxy (XStart+HSIZE/2-2, YStart+5);
			printf("%s", "\\   /");
			gotoxy (XStart+HSIZE/2-1, YStart+6);
			printf("%s", "\\ /");
			gotoxy (XStart+HSIZE/2, YStart+7);
			printf("%s", "'");
		} else if(c.suit == 2) {
			gotoxy (XStart+HSIZE/2, YStart+3);
			printf("%s", ".");
			gotoxy (XStart+HSIZE/2-1, YStart+4);
			printf("%s", "/ \\");
			gotoxy (XStart+HSIZE/2-2, YStart+5);
			printf("%s", "/   \\");
			gotoxy (XStart+HSIZE/2-2, YStart+6);
			printf("%s", "\\   /");
			gotoxy (XStart+HSIZE/2-1, YStart+7);
			printf("%s", "\\ /");
			gotoxy (XStart+HSIZE/2, YStart+8);
			printf("%s", "'");
		} else if (c.suit == 3) {
			gotoxy (XStart+HSIZE/2, YStart+3);
			printf("%s", "_");
			gotoxy (XStart+HSIZE/2-1, YStart+4);
			printf("%s", "(_)");
			gotoxy (XStart+HSIZE/2-2, YStart+5);
			printf("%s", "(_)_)");
			gotoxy (XStart+HSIZE/2-1, YStart+6);
			printf("%s", "/_\\");
		}
	} else if (c.face > 9) { // If figure
		if(c.face == 10) { // If Jack
			gotoxy(XStart+HSIZE/2, YStart+3);
			printf("%s%s%s%s", symbole, symbole, symbole, symbole);
			gotoxy(XStart+HSIZE/2+2, YStart+4);
			printf("%s", symbole);
			gotoxy(XStart+HSIZE/2+2, YStart+5);
			printf("%s", symbole);
			gotoxy(XStart+HSIZE/2-2, YStart+6);
			printf("%s   %s", symbole, symbole);
			gotoxy(XStart+HSIZE/2-2, YStart+7);
			printf("%s%s%s%s", symbole, symbole, symbole, symbole);
		} else if(c.face == 11) { // If Queen
			gotoxy(XStart+HSIZE/2-2, YStart+3);
			printf("%s%s%s%s", symbole, symbole, symbole, symbole);
			gotoxy(XStart+HSIZE/2-2, YStart+4);
			printf("%s  %s", symbole, symbole);
			gotoxy(XStart+HSIZE/2-2, YStart+5);
			printf("%s  %s", symbole, symbole);
			gotoxy(XStart+HSIZE/2-2, YStart+6);
			printf("%s%s%s%s", symbole, symbole, symbole, symbole);
			gotoxy(XStart+HSIZE/2, YStart+7);
			printf("%s", symbole);
			gotoxy(XStart+HSIZE/2+1, YStart+8);
			printf("%s", symbole);
		} else if(c.face == 12) { // Then King
			gotoxy(XStart+HSIZE/2-2, YStart+3);
			printf("%s  %s", symbole, symbole);
			gotoxy(XStart+HSIZE/2-2, YStart+4);
			printf("%s %s", symbole, symbole);
			gotoxy(XStart+HSIZE/2-2, YStart+5);
			printf("%s", symbole);
			gotoxy(XStart+HSIZE/2-2, YStart+6);
			printf("%s %s", symbole, symbole);
			gotoxy(XStart+HSIZE/2-2, YStart+7);
			printf("%s  %s", symbole, symbole);
		}
	}
	else { // If the face is in [2-10]
		// For each possible place, we check if we should print there
		
		/**
		 * There might be a shorter way with some math than those if
		 * (we were able to see some pattern before the "optimisation")
		 * I tried to optimise them, that's why it's not writen in a naif way
		 */
		
		for (i = 0; i < 3; ++i) {
			if ((c.face+1 == 9 || c.face+1 == 10) ||
			    (c.face+1 == 8 && (i==1 || i==2)) ||
			    (c.face+1 == 7 && i==1)) {
				gotoxy(XStart+HSIZE/2, YStart+2+2*i);
				printf("%s", symbole);
			}
			
			if ( (c.face+1 >= 6 && c.face+1 <= 10) ||
			     ((c.face+1 == 4 || c.face+1 == 5) && (i==0 || i==2)) ) {
				gotoxy(XStart+HSIZE/2-2, YStart+3+2*i);
				printf("%s", symbole);
				
				gotoxy(XStart+HSIZE/2+2, YStart+3+2*i);
				printf("%s", symbole);
			}
			
			if ((c.face+1 == 3) ||
			    (c.face+1 == 2 && (i==0 || i==2)) ||
			    (c.face+1 == 5 && i==1)) {
			gotoxy(XStart+HSIZE/2, YStart+3+2*i);
			printf("%s", symbole);
			}
		}
		
		if (c.face+1 == 10){
			gotoxy(XStart+HSIZE/2, YStart+8);
			printf("%s", symbole);
		}
		
	}
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
