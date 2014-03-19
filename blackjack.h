#ifndef CARD_FILE_H
#define CARD_FILE_H

#define CARDS 52
#define MAX_PLAYER 5
#define HANDSIZE 11
#define EMPTY 15
#define BLACKJACK 21

/* With non-windows system, we use UTF-8 for the cards symbols */
#ifndef _WIN32
    #define UTF8_DISPLAY
#endif

enum LINE {WM=8, MORE=13, BID};

/* Dealer rules
 if HS17 (Hit Soft 17) is defined
 the dealer will follow the "Hit Soft 17" rule
 
 if not, the dealer use the "Stand on 17"
 */
#define HS17

/*       DATATYPE               */

typedef struct{
	
	unsigned int face: 4;
	unsigned int suit: 2;
	unsigned int color: 1;  // 0 black, 1 red
    
} Card;

typedef struct{
	int points, bid;
	Card hand[HANDSIZE];
} Player;

enum WHO {DEALER, PLAYER_1, PLAYER_2, PLAYER_3, PLAYER_4, PLAYER_5};

/*       FUNCTION PROTOTYPE      */

// User interface

void clearScreen(void);
int askNumberPlayer(void);
char moreGame(void);
void byeMessage(void);
void gotoxy(short, short);
void clearLine(short);
void rebuy(Player listPlayers[]);
void displayGameBoard(int nbPlayers);
char moreCard(enum WHO who);
void showOutOfBound(enum WHO who);
void showBlackJack(enum WHO who);
void showHand(Card hand[], enum WHO who);
void displayMiniCard(Card card, int offset, enum WHO who);
void displayPoints(int points, enum WHO who);
void askBid(enum WHO who, Player *p);
void showWinner(Player listPlayers[], int dealerScore);


// Card Management

void fillDeck(Card * const wDeck);
void shuffleDeck(Card * const wDeck);
void serveCard(Player *player, Card deck[], enum WHO who, int numberOfCards);
int handPoints(Card hand[]);
int soft17HandPoints(Card hand[]);
Card drawCard(Card c[]);


// Players Management

void initPlayersPoints(Player listPlayers[], int numberPlayers);
void getBids(Player listPlayers[]);
void initPlayersHand(Player listPlayers[]);
void initDealerHand(Player *dealer);
void dealerMoves(Player *dealer, Card deck[]);
void givePoints(Player listPlayers[], int dealerPoints);
int specialProfit(Card hand[]);


// Other

void newGame(int numberPlayer, Player listPlayers[], Card deck[]);
int rrand(int m);


#endif
