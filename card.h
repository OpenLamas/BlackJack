#define CARDS 52
#define HANDSIZE 11

#ifndef _WIN32
	#define UTF8_DISPLAY
#endif

//enum CARDNAME {Ace, One, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Joker, Queen, King};

#ifdef _WIN32
	enum BORDERS {VL = 179, TR = 191, BL, HL = 196, BR = 217, TL};
#else
	enum BORDERS {VL = '|', TR = '\\', BL = '\\', HL = '_', BR = '/', TL = '/'};
#endif

enum LINE {PH = 0, PP = 10, DH=11, DP = 21, MORE=23, BID};
enum WHO {PLAYER, DEALER};
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
void makeCardFrame(Card, int, enum WHO);
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
void printSymboles(Card c, int XStart, int YStart);
