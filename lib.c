#include "header.h"

/*****************************************************************************
* FILENAME :        lib.c            
*
* DESCRIPTION :
*       Includes all deck functions for cardGame. 
* 
* AUTHORS :    Ciarán O' Mara
*              Eoghan Mulcahy
*
* Last Date of Modification: 25/11/16
******************************************************************************/

 // FUNCTIONS 

 /*
 * --------------------------------------------------------------------------|
 * Function:  draw play card                                                 | 
 * --------------------------------------------------------------------------|
 * INPUTS                                                                    |
 *   deck playDeck : the deck which is used to match the player cards.       |
 *   deck hiddenDeck : the hiddenDeck where the card is drawn from           |
 * --------------------------------------------------------------------------|
 * OPERATION                                                                 |
 *   Draws one card from the top of the hiddenDeck and puts it in play.      |
 * --------------------------------------------------------------------------|
 * OUTPUTS                                                                   |
 *   VOID                                                                    |
 * --------------------------------------------------------------------------|
 *
 */

 card drawPlaycard(deck *hiddenDeck){
        card topCard = hiddenDeck->cards[hiddenDeck->numCards - 1];
        removeCardAt(hiddenDeck,hiddenDeck->numCards-1);
        return topCard;
 }


/*
 * --------------------------------------------------------------------------|
 * Function:  deal                                                           | 
 * --------------------------------------------------------------------------|
 * INPUTS                                                                    |
 *   deck hiddenDeck : the original deck of packsize n specified by the user.|
 * --------------------------------------------------------------------------|
 * OPERATION                                                                 |
 *   Shuffles the deck randomly                                              |
 * --------------------------------------------------------------------------|
 * OUTPUTS                                                                   |
 *   A shuffled deck                                                         |
 * --------------------------------------------------------------------------|
 *
 */


 void deal(deck *deckToDealFrom, deck *player1, deck *player2){
     //take the number from the top of the deckToDeal from and give it to player1
     int numCardsInDealDeck = deckToDealFrom->numCards;
     int indexOfHand1 = 0;
     int indexOfHand2 = 0;
     for(int i = numCardsInDealDeck - 1; i > (numCardsInDealDeck - 1) - (HAND_SIZE * 2); i--){
         card drawnCard = deckToDealFrom->cards[i];
         if(!(i%2 == 0)){
            player1->cards[indexOfHand1] = drawnCard;
             indexOfHand1++;
         } else {
             player2->cards[indexOfHand1] = drawnCard;
             indexOfHand2++;
         }
         removeCardAt(deckToDealFrom,i);
     }
     player1->isEmpty = 0;
     player2->isEmpty = 0;
 } 

/*
 * --------------------------------------------------------------------------|
 * Delerations:  constant arrays representing the suits and vals             |
 * --------------------------------------------------------------------------|
 * INPUTS                                                                    |
 *   NONE                                                                    |
 * --------------------------------------------------------------------------|
 * OPERATION                                                                 |
 *  Allows us to allocate string values to our enums.                        |
 * --------------------------------------------------------------------------|
 * OUTPUTS                                                                   |
 *   NONE                                                                    |
 * --------------------------------------------------------------------------|
 *
 */

const char *suits[N_SUITS] = {
  "♣", "♥", "♠", "♦"    
};

const char *vals[N_VALS] = {
  "2", "3", "4", "5", "6", "7", "8", "9", "10",
  "jack", "queen", "king", "ace"
};

/*
 * --------------------------------------------------------------------------|
 * Function:  getRand();                                                     | 
 * --------------------------------------------------------------------------|
 * INPUTS                                                                    |
 *   int n the highest numbe the generator can be                            | 
 * --------------------------------------------------------------------------|
 * OPERATION                                                                 |
 *   genetrates a random number between 0 and n                              |
 * --------------------------------------------------------------------------|
 * OUTPUTS                                                                   |
 *   return a random number between 0 and n                                  |
 * --------------------------------------------------------------------------|
 *
 */

int getRand(int n){
    if(n==1){
        return 0;
    }
    else{
    time_t t;
    srand ((unsigned) time(&t));
    return (rand() % (n)); 
    }
    
} 

/*
 * --------------------------------------------------------------------------|
 * Function:  cardToString();                                                | 
 * --------------------------------------------------------------------------|
 * INPUTS                                                                    |
 *   The index of the card                                                   | 
 * --------------------------------------------------------------------------|
 * OPERATION                                                                 |
 *   prints card                                                             |
 * --------------------------------------------------------------------------|
 * OUTPUTS                                                                   |
 *   return void, prints card                                                |
 * --------------------------------------------------------------------------|
 *
 */
 void display_file(const char *file_name)
{
    FILE *f = fopen(file_name, "r");      // open the specified file
    if (f != NULL)
    {
        int c;

        while ((c = fgetc(f)) != EOF)     // read character from file until EOF
        {
            putchar(c);                   // output character
        }
        fclose(f);
    }
} 

 void printCard(card ref){
     system("setterm -bold on");
     if(ref.cardSuit==0||ref.cardSuit==2){
    printf(" %s \t of \t  %s\n", vals[ref.cardVal],suits[ref.cardSuit]);
     }
     else{
          printf(BOLDRED" %s \t of \t  %s\n"RESET, vals[ref.cardVal],suits[ref.cardSuit]);
     }
 }

 void printCardPointer(card *cardToPrint){
    printf("%s \t of \t  %s\n\n", vals[cardToPrint->cardVal],suits[cardToPrint->cardSuit]);
 }

/*
 * --------------------------------------------------------------------------|
 * Function (UTILITY):  printDeck();                                         | 
 * --------------------------------------------------------------------------|
 * INPUTS                                                                    |
 *   The deck you wish to print                                              | 
 * Function (UTILITY):  printDeck();                                         |
 * --------------------------------------------------------------------------|
 * INPUTS                                                                    |
 *   The deck you wish to print                                              |
 * --------------------------------------------------------------------------|
 * OPERATION                                                                 |
 *   Prints the decks cards to the console                                   |
 * --------------------------------------------------------------------------|
 * OUTPUTS                                                                   |
 *   void                                                                    |
 * --------------------------------------------------------------------------|
 *
 */

void printDeck(deck deckToPrint){
    for (int i = 0; i < deckToPrint.numCards; i++){
        if (i % 13 == 0){
            printf("\n");
        }
        //printf("cardVal %d", deckToPrint.cards[i].cardVal);
        printf("%s \t of \t ", vals[deckToPrint.cards[i].cardVal]);
        printf(" %s \n", suits[deckToPrint.cards[i].cardSuit]);
      
    }
}

void printDeckPointer(deck *deckToPrint){
    printf(" \n num cards in the deck %d", deckToPrint->numCards);
    
    for (int i = 0; i < deckToPrint->numCards; i++){
        if (i % 13 == 0){
            printf("\n");
        }
        //printf("cardVal %d", deckToPrint.cards[i].cardVal);
        if(deckToPrint->cards[i].cardSuit==0||deckToPrint->cards[i].cardSuit==2){
        printf("%s \t of \t ", vals[deckToPrint->cards[i].cardVal]);
        printf(" %s \n", suits[deckToPrint->cards[i].cardSuit]);
    }
    else{
        printf(BOLDRED"%s \t of \t "RESET, vals[deckToPrint->cards[i].cardVal]);
        printf(BOLDRED" %s \n"RESET, suits[deckToPrint->cards[i].cardSuit]);
    }
    }
}


void printHand(deck *deckToPrint){
 printf(" \n  Players Hand (%d cards)   ", deckToPrint->numCards);
    
    for (int i = 0; i < deckToPrint->numCards; i++){
        if(deckToPrint->cards[i].cardSuit==0||deckToPrint->cards[i].cardSuit==2){
            if(i==0&&i!=deckToPrint->numCards-1){
                printf("| %s", vals[deckToPrint->cards[i].cardVal]);
                printf("%s   ", suits[deckToPrint->cards[i].cardSuit]);
            }
            else if(i==deckToPrint->numCards-1){
                          if(i==0){
                printf("| ");
            }
                printf("%s", vals[deckToPrint->cards[i].cardVal]);
                printf("%s  |", suits[deckToPrint->cards[i].cardSuit]);
                printf("\n\n");
            }
            else{
                printf("%s", vals[deckToPrint->cards[i].cardVal]);
                printf("%s   ", suits[deckToPrint->cards[i].cardSuit]);
        
            }
    }
    else{
        if(i==0&&i!=deckToPrint->numCards-1){
                printf("|");
                printf(BOLDRED" %s"RESET, vals[deckToPrint->cards[i].cardVal]);
                printf(BOLDRED"%s   "RESET, suits[deckToPrint->cards[i].cardSuit]);
            }
            else if(i==deckToPrint->numCards-1){
                        if(i==0){
                printf("| ");
            }
                printf(BOLDRED"%s"RESET, vals[deckToPrint->cards[i].cardVal]);
                printf(BOLDRED"%s "RESET, suits[deckToPrint->cards[i].cardSuit]);
                printf(" |");
                printf("\n\n");
            }
            else{
                printf(BOLDRED"%s"RESET, vals[deckToPrint->cards[i].cardVal]);
                printf(BOLDRED"%s   "RESET, suits[deckToPrint->cards[i].cardSuit]);
        
            }
    }
    }

}


/*
 * --------------------------------------------------------------------------|
 * Function:  getNumberOfDecks                                               |
 * --------------------------------------------------------------------------|
 * INPUTS                                                                    |
 *   NONE                                                                    |
 * --------------------------------------------------------------------------|
 * OPERATION                                                                 |
 *   Requests the number of decks to play with from the user.                |
 * --------------------------------------------------------------------------|
 * OUTPUTS                                                                   |
 *   The number of decks the user has requested                              |
 * --------------------------------------------------------------------------|
 *
 */

int getNumberOfDecks(){
    int numDecks = -1;
    char term;
      if(scanf("%d%c", &numDecks, &term) != 2|| term != '\n'){
          verify(invalidInput); 
      }
       return numDecks;
}

/*
 * --------------------------------------------------------------------------|
 * Function:  initialiseEmptyDeck                                            |
 * --------------------------------------------------------------------------|
 * INPUTS                                                                    |
 *   Number of cards                                                         |
 * --------------------------------------------------------------------------|
 * OPERATION                                                                 |
 *   Takes the size of the hidden deck and creates an empty deck of same     |
 *   memory allocation                                                       |
 * --------------------------------------------------------------------------|
 * OUTPUTS                                                                   |
 *   An empty deck                                                           |
 *                                                                           |
 * --------------------------------------------------------------------------|
 *
 */

card* initialiseEmptyDeck(deck *deckToInit, int numberOfCards){
    if(numberOfCards == 0){
         deckToInit->cards = malloc((numberOfCards + 1) * sizeof(card));
         deckToInit->numCards=numberOfCards;
         deckToInit->init=0;
    } else {
        deckToInit->cards = malloc(numberOfCards * sizeof(card));
        deckToInit->numCards=numberOfCards;
        deckToInit->init=0;
    }

    deckToInit->isEmpty = 1;

    return deckToInit->cards;
}

/*
 * --------------------------------------------------------------------------|
 * Function:  initializeHiddenDeck                                           |
 * --------------------------------------------------------------------------|
 * INPUTS                                                                    |
 *   Number of decks as specified by the user                                |
 * --------------------------------------------------------------------------|
 * OPERATION                                                                 |
 *   Takes the number of decks from the user and initializes a dynamic array |
 *   of cards in the hiddenDeck.                                             |   
 *   It then loops on the suits and vals of each card adding each in turn to | 
 *   the array of cards.                                                     |
 * --------------------------------------------------------------------------|
 * OUTPUTS                                                                   |
 *   A full deck containing N packs of cards                                 |
 * --------------------------------------------------------------------------|
 *
 */


card* initializeHiddenDeck(deck *hiddenDeck, int numberOfDecks){

    hiddenDeck->cards = malloc(numberOfDecks * 52 * sizeof(card));
    int index = 0;
    for(int k = 0; k < numberOfDecks; k++){
        for(int i = CLUBS; i <= DIAMONDS; i++){
            for(int j = TWO; j <= ACE; j++){
                card myCard;
                myCard.cardSuit = i;
                myCard.cardVal = j;
                hiddenDeck->cards[index] = myCard;
                index++;
            }
        }
    }
    hiddenDeck->numCards = index;
    hiddenDeck->isEmpty = 0;
    return hiddenDeck->cards;
}

/*
 * --------------------------------------------------------------------------|
 * Function:  removeCard                                                     |
 * --------------------------------------------------------------------------|
 * INPUTS                                                                    |
 *   deck hiddenDeck : the original deck of packsize n specified by the user.|
 *   int n: the index of the card to be removed                              |               
 *   deck emptyDeck: the empty deck on the in play                           |
 * --------------------------------------------------------------------------|
 * OPERATION                                                                 |
 *   removes the nth card from the hidden deck                               |
 * --------------------------------------------------------------------------|
 * OUTPUTS                                                                   |
 *   returns the deck with the nth card removed                              |                                                                    |
 * --------------------------------------------------------------------------|
 *
 */

void shift(deck *hiddenDeck, int index)
{
    if (!(hiddenDeck->isEmpty) || !(index == hiddenDeck->numCards - 1)|| !(hiddenDeck->numCards == 0))
    {
        for (int k = index; k <= hiddenDeck->numCards; k++)
        {
            hiddenDeck->cards[k] = hiddenDeck->cards[k + 1];
        }
        hiddenDeck->numCards = hiddenDeck->numCards - 1;
    }
    else
    {
        printf("The shift never happened because the flags were not resolved!!!!");
    }
}

void removeCardAt(deck *hiddenDeck, int index){
    deck *deckDec;
     
     deckDec = (deck *)malloc(sizeof(deck));
     
     deckDec->cards = (card *)malloc((hiddenDeck->numCards-1)*sizeof(card));
     deckDec->numCards = hiddenDeck->numCards-1;
     
     shift(hiddenDeck, index);

     hiddenDeck = deckDec;
    //hiddenDeck->numCards=hiddenDeck->numCards-1;
     if(hiddenDeck->numCards == 0) {
       hiddenDeck->isEmpty = 1;
     }

    }



  
void addCard(deck *playDeck, card addCard){

  card *upDatedArray = (card *) malloc(sizeof(card) * playDeck->numCards+1);
 
  //printf("Deck deck numcards %d", deckDec->numCards);
  for(int i=0; i < playDeck->numCards; i++)
  {
      upDatedArray[i]=playDeck->cards[i];
  }
  
  upDatedArray[playDeck->numCards]=addCard;
  playDeck->cards = upDatedArray;
  playDeck->numCards += 1;

}

/*
 * --------------------------------------------------------------------------|
 * Function:  shuffle //problem creating an extra card                       | 
 * --------------------------------------------------------------------------|
 * INPUTS                                                                    |
 *   deck hiddenDeck : the original deck of packsize n specified by the user.|
 * --------------------------------------------------------------------------|
 * OPERATION                                                                 |
 *   Shuffles the deck randomly                                              |
 * --------------------------------------------------------------------------|
 * OUTPUTS                                                                   |
 *   A shuffled deck                                                         |
 * --------------------------------------------------------------------------|
 *
 */

void shuffle(deck *hiddenDeck){

  int numCards = hiddenDeck->numCards, r, i=0;
  deck temp;
  int constSize = hiddenDeck->numCards;
  // setting a pointer to the hidden all decks which will be used for deck ops  

  initialiseEmptyDeck(&temp, numCards);
  
  for(; numCards >=1; numCards--, i++){
    r = getRand(hiddenDeck->numCards);
   
        temp.cards[i] = hiddenDeck->cards[r];
        shift(hiddenDeck, r);
}
 
 temp.isEmpty = 0;
 hiddenDeck->numCards=constSize;
*hiddenDeck=temp;

}


/* --------------------------------------------------------------------------|
 * Function:  draw                                                           |
 * --------------------------------------------------------------------------|
 * INPUTS                                                                    |
 *   deck hiddenDeck : the original deck of packsize n specified by the user.|
 * --------------------------------------------------------------------------|
 * OPERATION                                                                 |
 *   gets the top card of the hiddenDeck                                     |
 * --------------------------------------------------------------------------|
 * OUTPUTS                                                                   |
 *   returns the top card of the hiddenDeck                                  |
 * --------------------------------------------------------------------------|
 *
 */
card draw(deck hiddenDeck){
        return hiddenDeck.cards[hiddenDeck.numCards-1];
}


/*
 * --------------------------------------------------------------------------|
 * Function:  check match                                                    | 
 * --------------------------------------------------------------------------|
 * INPUTS                                                                    |
 *   deck deckToCheck : The deck of which the top card has to be removed from |                            
 *   card cardDrawn : The card we are checking against the deck              |
 * --------------------------------------------------------------------------|
 * OPERATION                                                                 |
 *   checks if there is a card of the same suit or value in the deck         |
 * --------------------------------------------------------------------------|
 * OUTPUTS                                                                   |
 *   returns 1 if a match of suit or value is found, 0 otherwise             |
 * --------------------------------------------------------------------------|
 *
 */


 int handCheck(deck *plrDeck, deck *playDeck, card cardToCheck){
   int pos = checkMatch(plrDeck, cardToCheck);
   if(pos!=-1){
       printHand(plrDeck);
       addCard(playDeck, plrDeck->cards[pos]);
       removeCardAt(plrDeck, pos);
       return 1;
   }
   else{
     //printf("Player has no cards to match\n");
     return 0/*-1*/;
   }
 }

 int checkMatch(deck *deckToCheck, card cardDrawn) {
   int i, returnValue = -1;
   for(i = 0; i < deckToCheck->numCards; i++) {
     if((deckToCheck->cards[i].cardSuit == cardDrawn.cardSuit) || (deckToCheck->cards[i].cardVal == cardDrawn.cardVal)) {
       returnValue = i;
     }
    }
 return returnValue;
}

void clean(deck *pntHidDeck,deck *pntPlr1Deck, deck *pntPlr2Deck ,deck *pntPlayDeck){
   // free(pntHidDeck->cards);
    free(pntHidDeck);
  //  free(pntPlr1Deck->cards);
    free(pntPlr1Deck);      
   // free(pntPlr2Deck->cards);
    free(pntPlr2Deck);
   // free(pntPlayDeck->cards);
    free(pntPlayDeck);
  
}

void printCardPlayed(int playerId, deck *pntPlayDeck)
{   system("setterm -bold on");
    printf("  *-------------------------------------*\n");
    printf("  * Player %d had a match and played the *  ⇨   ", playerId);
    printCard(pntPlayDeck->cards[pntPlayDeck->numCards - 1]);
    printf("  *-------------------------------------*\n\n");
}

void printNoMatch(int playerId)
{   system("setterm -bold on");
    printf("  *---------------------------------------*\n");
    printf("  * No Match! drawing a card for player %d *\n", playerId);
    printf("  *---------------------------------------* \n\n");
}

void printWinner(int playerId)
{   system("setterm -bold on");
    printf("  *------------------*\n");
    printf("  * PLAYER %d WINS !!!*\n", playerId);
    printf("  *------------------*\n\n");
}

void verify(error type){
  switch(type){
  
  case ok:
    //Everythging worked as expected.
    break;
  case invalidSize: //error from the delete function. trying to delete a poly already deleted
    printf("Warning: Deck was resized incorrectly.\n");
    break;
  case invalidInput: //error caused by user not inoutting a number
    printf("Warning: Invalid input type.\n");
    break;
  default: //for when the user tries modifies the .
    printf("Error: Something went horribly wrong.\n"); 
    break;
  }  
}
