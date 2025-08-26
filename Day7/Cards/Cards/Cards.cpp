//
//  Cards.cpp
//  Cards
//
//  Created by Jonathan Pulsipher on 8/26/25.
//

#include "Cards.h"

/*
 * Representation of card
 *
 * Properties:
 *   rank: int 1-13 where Ace = 1, Jack = 11, Queen = 12, King = 13
 *   suit: int 1-4 where Hearts = 1, Diamonds = 2, Clubs = 3, and Spades = 4
 */
struct Card{
    int rank = 0;
    int suit = 0;
};

/*
 * Representation of 52-card deck
 * The "top" of deck and discard is the final element in each vector
 *
 * Properties:
 *   deck: Vector<int> representation draw pile
 *   discard: Vector<int> representation of discard pile
 */
struct Deck{
    std::vector<Card> deck;
    std::vector<Card> discard;
};

Deck activeDeck;
//TODO: how do we initialize Deck? Wait until access?

/*
 * Adds discard back into the deck, then shuffles.
 */
void Reset(){
    
}

/*
 * Randomly re-orders cards in the deck
 */
void Shuffle(){
    //TODO: implement
}

/*
 * Moves "top" card (last in the deck Vector) to discard and returns its rank
 *
 * Return:
 *   int representation of card
 */
Card Draw(){
    //TODO: implement
    return {0, 0}; //Null card of rank 0 and suit 0
}

/*
 * Converts int representation of card into user-friendly string
 *
 * Return:
 *   String letter or number of card
 */
std::string To_StringCard(int card)
{
    //TODO: implement
    return "";
}

/*
 * Prints out the deck, starting with drawable cards in order from end to beginning, then discard pile the same way
 *
 * Return:
 *   String with "Cards in Draw Pile", then deck cards in order from top to bottom, then "Cards in Discard Pile:, then
 *   discard cards from top to bottom
 */
std::string To_StringDeck(){
    //TODO: implement
    return "";
}
