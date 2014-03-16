#define CARDS 52
#define HANDSIZE 11

#ifndef _WIN32
	#define UTF8_DISPLAY
#endif

enum LINE {PH = 0, PP = 10, DH=11, DP = 21, MORE=10, BID};
enum WHO {DEALER, PLAYER_1, PLAYER_2, PLAYER_3, PLAYER_4, PLAYER_5};
#define EMPTY 15
#define BLACKJACK 21

struct bitCard {
	
	unsigned int face: 4;
	unsigned int suit: 2;
	unsigned int color: 1;

};
typedef struct bitCard Card;

typedef struct{
	int points, bid;
	Card hand[HANDSIZE];
}Player;

//function prototypes
void fillDeck(Card * const wDeck);
void shuffleDeck(Card * const wDeck);
void dealDeck(const Card * const wDeck);
void gotoxy(short, short);
char moreGame(void);
char moreCard(void);
int playGame(Card *, Player);
int askBid(Player p);
Card drawCard(Card c[]);
int showPlayerHand(Card ph[]);
int showDealerHand(Card ph[]);
void clearLine(short);
void clearScreen(void);
int rrand(int m);
void displayGameBoard(int nbPlayers);
void displayMiniCard(Card card, int offset, enum WHO who);
void displayPoints(int points, enum WHO who);