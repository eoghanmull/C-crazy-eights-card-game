#ifndef _HEADER_H_
#define _HEADER_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


#define N_SUITS 4
#define N_VALS 13
#define HAND_SIZE 8
#define RESET   "\033[0m"
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */

/*****************************************************************************
* FILENAME :        header.h            
*
* DESCRIPTION :
*       Includes the datastructures for card and deck. 
* 
* AUTHORS :    Ciarán O' Mara
*              Eoghan Mulcahy
*              Ryan Jennings
*              Joe Buckley
*
* Last Date of Modification: 25/11/16
******************************************************************************/


enum suit {
    CLUBS,
    HEARTS,
    SPADES,
    DIAMONDS
} suit;

enum val {
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING,
    ACE
} val;

typedef struct card {
    enum suit cardSuit;
    enum val cardVal;
} card;

typedef struct player{
  int id;
  card *hand;
} player;


typedef struct deck {
    int init;
    int numCards;
    int isEmpty;
    card *cards;
} deck;

typedef struct gameDecks{
    deck hiddenDeck;
    deck emptyDeck;
} gameDecks;

typedef struct playerHands{
    deck player1;
    deck player2;
} playerHands;

typedef struct gameStats {
    int matchesP1;
    int matchesP2;
    int gameLoops;
    int nomatchP1;
    int nomatchP2;
    int reshuffles;
} gameStats;

typedef enum {ok, invalidSize, invalidInput} error;

int getRand(int n);
void printCard(card ref);
void printCardPointer(card *cardToPrint);
void printDeck(deck deckToPrint);
void printDeckPointer(deck *deckToPrint);
void testPointerInput(deck *hiddenDeck);
int getNumberOfDecks();
card* initialiseEmptyDeck(deck *deckToInit, int numberOfCards);
card* initializeHiddenDeck(deck *hiddenDeck, int numberOfDecks);
void reallocDec(deck *hiddenDeck);
void reallocInc(deck *hiddenDeck);
void removeCardAt(deck *hiddenDeck, int index);
void shuffle(deck *hiddenDeck);
void add(deck *hiddenDeck, deck emptyDeck); //void type create gameDecks in main
card draw(deck hiddenDeck); //void 
int checkMatch(deck *deckToCheck, card cardDrawn);
int handCheck(deck *plyDeck, deck *playDeck, card cardToCheck);
deck initializeHand(int handSize); //void 
void deal(deck *deckToDealFrom, deck *player1, deck *player2);
void shift(deck *hiddenDeck, int index);
void addCard(deck *hiddenDeck, card addCard);
void clean(deck *pntHidDeck,deck *pntPlr1Deck,deck *pntPlr2Deck,deck *pntPlayDeck);
void verify(error type);
void display_file(const char *file_name);
card drawPlaycard(deck *hiddenDeck);
void printCardPlayed(int playerId, deck *playDeck);
void printNoMatch(int playerId);
void printWinner(int playerId);
void printHand(deck *deckToPrint);
//void clearAll(deck *pntHidDeck,deck *pntPlr1Deck,deck *pntPlr2Deck,card *pntHoldingCard);
#endif /* _HEADER_H_ */
