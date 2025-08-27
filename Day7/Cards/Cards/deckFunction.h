//
//  deckFunction.h
//  Cards
//
//  Created by Alexis Blood on 8/26/25.
//

#ifndef DECKFUNCTION_H
#define DECKFUNCTION_H

#include "structs.h"
#include <vector>
#include <iostream>
#include <vector>
#include <cstdlib>

std::vector<Card> deckOfCards();

void printDeck(std::vector<Card>);

void shuffle(std::vector<Card>& deck);

Card drawCard(std::vector<Card>& deck);

Hand getHand(std::vector<Card>& deck);

bool isFlush(Hand hand);

bool isStraight(Hand hand);

bool isStraightFlush(Hand hand);

bool isRoyalFlush(Hand hand);

bool isFullHouse(Hand hand);

#endif
