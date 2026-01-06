//
//  Cards.h
//  Cards
//
//  Created by Jonathan Pulsipher on 8/26/25.
//

#ifndef CARDS_H
#define CARDS_H

#include <string>
#include <vector>

/*
 * Representation of card
 *
 * Properties:
 *   rank: int 1-13 where Ace = 1, Jack = 11, Queen = 12, King = 13
 *   suit: int 1-4 where Hearts = 1, Diamonds = 2, Clubs = 3, and Spades = 4
 */
struct Card{
    int rank;
    int suit;
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

/*
 * Adds discard back into the deck, then shuffles.
 */
void InitializeDeck();

/*
 * Randomly re-orders cards in the deck
 */
void Shuffle();

/*
 * Moves "top" card (last in the deck Vector) to discard and returns its rank
 *
 * Return:
 *   Card struct
 */
Card Draw();

/*
 * Converts into user-friendly string
 *
 * Return:
 *   String <rank> of <suit> as in "Ace of Spades" or "2 of Clubs"
 */
std::string To_StringCard(Card card);

/*
 * Prints out the deck, starting with drawable cards in order from end to beginning, then discard pile the same way
 *
 * Return:
 *   String with "Cards in Draw Pile", then deck cards in order from top to bottom, then "Cards in Discard Pile:, then
 *   discard cards from top to bottom
 */
std::string To_StringDeck();

#endif
