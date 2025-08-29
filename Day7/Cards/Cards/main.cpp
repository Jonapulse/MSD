//
//  main.cpp
//  Cards
//
//  Created by Alexis Blood on 8/26/25.
// John Pulsipher

#include <iostream>
#include "struct.h"
#include "deckFunction.h"

int main(int argc, const char * argv[]) {
    std::vector<Card> ourDeck = createDeckOfCards();
    shuffle(ourDeck);
    Hand hand = getHand(ourDeck);
    sortHand(hand);
    printHand(hand);

// Testing: changed the values of each cards in accordance with which function needed testing
//    Card c1 = {1, 'D'};
//    Card c2 = {2, 'H'};
//    Card c3 = {2, 'H'};
//    Card c4 = {3, 'H'};
//    Card c5 = {2, 'H'};
//
//    std::vector<Card> deck = {c1, c2, c3, c4, c5};
//    Hand hand = {deck};
//    sortHand(hand);
    
// Outputs
    std::cout << "The hand is flush: " << isFlush(hand) << std::endl;
    std::cout << "The hand is straight: "<< isStraight(hand) << std::endl;
    std::cout << "The hand is a straight flush: "<< isStraightFlush(hand) << std::endl;
    std::cout << "The hand is a royal flush: "<< isRoyalFlush(hand) << std::endl;
    std::cout << "The hand is a full house: "<< isFullHouse(hand) << std::endl;
    
    float flushCount = 0;
    float straightCount = 0;
    float straightFlushCount = 0;
    float royalFlushCount = 0 ;
    float fullHouseCount = 0;
    for(int i = 0; i < 1000; i++){
        std::vector<Card> deck = createDeckOfCards();
        shuffle(deck);
        Hand hand = getHand(deck);
        if(isFlush(hand))
            flushCount++;
        if(isStraight(hand))
            straightCount++;
        if(isStraightFlush(hand))
            straightFlushCount++;
        if(isRoyalFlush(hand))
            royalFlushCount++;
        if(isFullHouse((hand)))
            fullHouseCount++;
    }
    
    std::cout << "Of 1000 hands from 1000 randomly generated decks, we have: " << flushCount << " flushes, "
        << straightCount << " straights, " << straightFlushCount << " straight flushes, "
    << royalFlushCount << " royal flushes, " << fullHouseCount << " full houses" << '\n';
    

    
    return 0;
}
