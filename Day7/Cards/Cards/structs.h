//
//  structs.h
//  Cards
//
//  Created by Alexis Blood on 8/26/25.
//
#ifndef STRUCTS_H
#define STRUCTS_H

#include <vector>
#include <string>

// Creates a data type for a card, where rank is the type of card (1-10, jack, queen, king) and suit is heart, spade, clover, diamond
struct Card {int rank; std::string suit;};

struct Hand {std::vector<Card> cards;};

#endif
