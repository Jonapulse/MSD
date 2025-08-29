//
//  structs.h
//  Cards
//
//  Created by Alexis Blood on 8/26/25.
//
#ifndef STRUCTS_H
#define STRUCTS_H
#include <vector>

// Creates a data type for a card, where rank is the type of card (ace, 2-10, jack, queen, king) and suit is heart, spade, clover, diamond
struct Card {int rank; char suit;};

struct Hand {std::vector<Card> cards;};

#endif
