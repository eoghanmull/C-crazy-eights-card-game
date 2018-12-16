#include "header.h"

/*****************************************************************************
* FILENAME :        main.c            
*
* DESCRIPTION :
*       main file includes game implementation. 
* 
* AUTHORS :    Ciarán O' Mara
*              Eoghan Mulcahy
*
* Last Date of Modification: 25/11/16
******************************************************************************/


int main(int argc, char **argv) {
  system("setterm -bold on"); //turns the bold print on

  //prints out the welcome block
  printf("\n  *-------------------------------------------------------------------------*\n");
  printf("  * Hello! Welcome to our card game       ♦ ♥ ♣ ♠                           *\n");
  printf("  * This game was developed by Ciaran, Eoghan, Joe and Ryan                 *\n");
  printf("  * ------------------------------------------------------------------------*\n\n");

  //displays the cards ascii art from ascii.txt
  display_file("ascii.txt");

  //displays the game rules 
  printf("\n\n  *-------------------------------------------------------------------------*\n");
  printf("  * The rules of the game are as follows:                                   *\n");
  printf("  * 1) The player choses how many decks they would like to play with.       *\n");
  printf("  * 2) 8 cards are dealt to each player.                                    *\n");
  printf("  * 3) The top card of the deck is flipped face up.                         *\n");
  printf("  * 4) Strting with player one the players will try to match the            *\n");
  printf("  *    cards in there hand to the top card by either value or suit.         *\n");
  printf("  * 5) The winner is the player who gets rid of all their cards first.      *\n");
  printf("  *------------------------------------------------------------------------ *\n\n");
  
  //prompts the user to input the amount of decks they want to play with 
  printf("  *--------------------------------------------------------------*\n");
  printf("  *         How many decks would you like to play with?          *\n");
  printf("  *--------------------------------------------------------------*   ⇨   ");


  // logging variable remove for production code.
  int logging = atoi(argv[1]);
  // -- get the number of decks from the user --
  int numDecks = getNumberOfDecks();
  printf("\n");
  // set up all decks
  deck hiddenDeck;
  deck player1;
  deck player2;
  deck playingDeck;

  // set up the game stats struct 
  gameStats thisGamesStats;
  thisGamesStats.reshuffles = 0;
  thisGamesStats.matchesP1 = 0;
  thisGamesStats.matchesP2 = 0;
  thisGamesStats.nomatchP1 = 0;
  thisGamesStats.nomatchP2 = 0;
  thisGamesStats.gameLoops = 0;

 

  // setting a pointer to the hidden all decks which will be used for deck ops  
  deck *pntHidDeck = &hiddenDeck;
  deck *pntPlr1Deck = &player1;
  deck *pntPlr2Deck = &player2;
  deck *pntPlayDeck = &playingDeck;
  
  //allocates memory to the deck addresses
  pntHidDeck=malloc(sizeof(deck));
  pntPlayDeck=malloc(sizeof(deck));
  pntPlr1Deck=malloc(sizeof(deck));
  pntPlr2Deck=malloc(sizeof(deck));

  //initialises the hidden deck with the number of decks requested by the user
  card *hidDeckCards = initializeHiddenDeck(pntHidDeck,numDecks);
  //initialises the played deck
  card *playDeckCards = initialiseEmptyDeck(pntPlayDeck,0);

  //prints of the deck before shuffling if in debug mode
  if (logging)
  {
    printf("Print the deck before shuffling \n");
    printDeckPointer(pntHidDeck);
  }
  
  //shuffles the hidden deck
  shuffle(pntHidDeck);
  
  //prints out the deck after shuffling if in debug mode
  if (logging)
  {
    printf("Print the deck after shuffling \n\n");
    printDeckPointer(pntHidDeck);
  }
  
  //prints staement if in debugging mode
  if (logging)
  {
    printf("Setting up the player hands \n");
  }

  //initialises the player hands
  initialiseEmptyDeck(pntPlr1Deck,HAND_SIZE);
  initialiseEmptyDeck(pntPlr2Deck,HAND_SIZE);

  //prints statement if in debugging mode
  if (logging)
  {
    printf("Dealing out the cards \n");
  }

  //deals 8 cards to each player from the hidden deck
  deal(pntHidDeck,pntPlr1Deck,pntPlr2Deck);
 
  //Game loop loops until there are no cards left in one of the players hands 
  int loopCount = 1;
  while ((pntPlr1Deck->numCards != 0) && (pntPlr2Deck->numCards != 0))
  {
    thisGamesStats.gameLoops += 1;
    //on the first loop draw a card from the hidden deck and add it to the played deck
    if (loopCount == 1)
    {
      card drawnCard = drawPlaycard(pntHidDeck); //take top card from hidden deck
      addCard(pntPlayDeck, drawnCard); //add the card to the played deck
      printf("  ");
      printCard(drawnCard); 
      printf("\n");
    }

    //if after the draw there is no longer any cards in the hidden deck tranfer from played deck
    if (pntHidDeck->numCards == 0)
    {
      thisGamesStats.reshuffles += 1;
      printf("The hidden deck is empty");
      printDeckPointer(pntHidDeck);
      //take the top card from the played deck
      card topCard = drawPlaycard(pntPlayDeck);
      //transfers the remaining cards back to the hidden deck
      for(int i = 0; i < pntPlayDeck->numCards; i++){
      addCard(pntHidDeck,pntPlayDeck->cards[i]);
      }

      //adds the drawn card back to the played deck
      pntPlayDeck->cards = malloc(sizeof(card));
      pntPlayDeck->cards[0] = topCard;
      pntPlayDeck->numCards =1;

      //pntHidDeck->numCards = numCardsInPlay - 1;
      printf("Print deck before shuffle \n");
      printDeckPointer(pntHidDeck);
      //shuffles the hidden deck with cards transfered over 
      shuffle(pntHidDeck);
      //prints the new hidden deck and played deck if in debug mode
      if(logging){
      printf("Print deck before shuffle \n");
      printDeckPointer(pntHidDeck);
      printf("printing the play deck\n");
      printDeckPointer(pntPlayDeck);
      }
      continue;
    } 
    
    //check if any of the cards in player 1's hand match the top card in the played deck
    int isMatch1 = handCheck(pntPlr1Deck, pntPlayDeck, pntPlayDeck->cards[pntPlayDeck->numCards - 1]);
    int isMatch2;
    
    //if there is print the card and check does it match a card in player 2's hand
    if (isMatch1)
    {
      thisGamesStats.matchesP1 += 1;
      printCardPlayed(1,pntPlayDeck);
      isMatch2 = handCheck(pntPlr2Deck, pntPlayDeck, pntPlayDeck->cards[pntPlayDeck->numCards - 1]);
    }
    //if there isnt a match 
    else{
      thisGamesStats.nomatchP1 += 1;
      printNoMatch(1);
      //draw a card for player one from the hidden deck
      card player1Card = drawPlaycard(pntHidDeck);
      //if the hidden deck is empty transfer all the cards from the played deck except the top card
      if (pntHidDeck->numCards == 0)
      {
        thisGamesStats.reshuffles += 1;
        //take the top card from the played deck
        card topCard = drawPlaycard(pntPlayDeck);
        //transfers the remaining cards back to the hidden deck
        for (int i = 0; i < pntPlayDeck->numCards; i++)
        {
          addCard(pntHidDeck, pntPlayDeck->cards[i]);
        }
        pntPlayDeck->cards = malloc(sizeof(card));
        pntPlayDeck->cards[0] = topCard;
        pntPlayDeck->numCards = 1;
        //shuffle the new hidden deck
        shuffle(pntHidDeck);
         //prints the new hidden deck and played deck if in debug mode
        if(logging){
        printf("Print deck before shuffle \n");
        printDeckPointer(pntHidDeck);
        printf("printing the play deck\n");
        printDeckPointer(pntPlayDeck);
        }
        continue;
      }
      //add the card from the hidden deck to player 1's hand
      addCard(pntPlr1Deck,player1Card);
      //checks if there is a match in player 2's hand
      isMatch2 = handCheck(pntPlr2Deck, pntPlayDeck, pntPlayDeck->cards[pntPlayDeck->numCards - 1]);
    }

    //if theres no cards left in player 1's hand stop the game and print winner player 1
    if (pntPlr1Deck->numCards == 0)
    {  
      printWinner(1);
      break;
    }

    if (isMatch2)
    { 
      thisGamesStats.matchesP2 += 1;
      printCardPlayed(2,pntPlayDeck);
    }
    else
    {
      thisGamesStats.nomatchP2 += 1;
      //draw a card for player two
      printNoMatch(2);
      card player2Card = drawPlaycard(pntHidDeck);

      if (pntHidDeck->numCards == 0)
    {
      thisGamesStats.reshuffles += 1;
       printf("The hidden deck is empty");
      //int numCardsInPlay = pntPlayDeck->numCards;
      printDeckPointer(pntHidDeck);
      //shuffle the cards in the playDeck to the hiddenDeck but keeping the topcard
      // storing the top card as this is not beind passed back to the hiddenDeck.
      // this is tempererally removed from the playDeck it will be added back in.
      card topCard = drawPlaycard(pntPlayDeck);
      for(int i = 0; i < pntPlayDeck->numCards; i++){
        addCard(pntHidDeck,pntPlayDeck->cards[i]);
      }

      pntPlayDeck->cards = malloc(sizeof(card));
      pntPlayDeck->cards[0] = topCard;
      pntPlayDeck->numCards =1;

      shuffle(pntHidDeck);
      continue;
    } 
      addCard(pntPlr2Deck,player2Card);
    }

    if (pntPlr2Deck->numCards == 0){
      printWinner(2);
      break;
    }

if(logging){
      printf("\n\n\n\n\n-----------------------------------------------\n");
      printf("LOOP %d \n", loopCount);
      printf("----------------------------------------------\n");
      printf("||||||||||||||||||||||||||||||");
      printf("\nPrint the player hands \n");
      printf("Print player1's hand \n");
      printDeckPointer(pntPlr1Deck);
      printf("Player 2's hand \n");
      printDeckPointer(pntPlr2Deck);
      printf("||||||||||||||||||||||||||||||\n");
      printf("******************************");
      printf("\n the play deck \n");
      printDeckPointer(pntPlayDeck);
      printf("\n******************************\n");
      printf("###############################");
      printf("\n the hid deck \n");
      printDeckPointer(pntHidDeck);
      printf("\n###############################\n");
      printf("-----------------------------------------------\n\n\n\n\n");
}
       loopCount++;
    }

   free(hidDeckCards);
   free(playDeckCards);
 clean(pntHidDeck,pntPlr1Deck,pntPlr2Deck,pntPlayDeck);

  printf("\n  *-------------------------------------------------------------------------*\n");
  printf("  * The game statistics were as follows       ♦ ♥ ♣ ♠                       *\n");
  printf("  * Number of cards matched by player 1:\t%d                          *\n", thisGamesStats.matchesP1);
  printf("  * Number of cards matched by player 2:\t%d                          *\n", thisGamesStats.matchesP2);
  printf("  * Number of no matches by player 1:\t%d                                  *\n", thisGamesStats.nomatchP1);
  printf("  * Number of no matches by player 2:\t%d                                  *\n", thisGamesStats.nomatchP2);
  printf("  * Number reshuffles of the hidden deck:\t%d                           *\n", thisGamesStats.reshuffles);
  printf("  * Number loops that happened in the game:\t%d                          *\n", thisGamesStats.gameLoops);
  printf("  * ------------------------------------------------------------------------*\n\n");

      return 0;

  }

 

 

