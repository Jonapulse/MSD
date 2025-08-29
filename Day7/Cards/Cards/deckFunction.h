//
//  deckFunction.h
//  Cards
//
//  Created by Alexis Blood on 8/26/25.
//
#include "structs.h"
#include <iostream>
#include <cstdlib>

// Creates a deck of cards and returns it as a vector of cards
std::vector<Card> createDeckOfCards();

// Prints out all the cards in the deck
void printDeck(std::vector<Card>& deck);

// Prints out all the cards in the player's hand
void printHand(Hand hand);

// Shuffles the cards in the deck
void shuffle(std::vector<Card>& deck);

// Draws a card from the deck
Card drawCard(std::vector<Card>& deck);

// Gives the player a hand of five cards
Hand getHand(std::vector<Card>& deck);

// Sorts the hand into ascending order
void sortHand(Hand& hand);


// Returns if the hand is any of these types:

bool isFlush(Hand hand);

bool isStraight(Hand hand);

bool isStraightFlush(Hand hand);

bool isRoyalFlush(Hand hand);

bool isFullHouse(Hand hand);
