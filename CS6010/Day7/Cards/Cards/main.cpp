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
    std::srand(std::time(0));
    
    std::vector<Card> ourDeck = createDeckOfCards();
//    shuffle(ourDeck);
//    Hand hand = getHand(ourDeck);
//    sortHand(hand);
//    printHand(hand);

 //Testing: changed the values of each cards in accordance with which function needed testing
//    Card c1 = {10, 'S'};
//    Card c2 = {10, 'D'};
//    Card c3 = {10, 'C'};
//    Card c4 = {10, 'D'};
//    Card c5 = {11, 'S'};
//
//    std::vector<Card> deck = {c1, c2, c3, c4, c5};
//    Hand hand;
//    hand.cards = deck;
//    
// Outputs
//    std::cout << "The hand is flush: " << isFlush(hand) << std::endl;
//    std::cout << "The hand is straight: "<< isStraight(hand) << std::endl;
//    std::cout << "The hand is a straight flush: "<< isStraightFlush(hand) << std::endl;
//    std::cout << "The hand is a royal flush: "<< isRoyalFlush(hand) << std::endl;
//    std::cout << "The hand is a full house: "<< isFullHouse(hand) << std::endl;
//    
    float flushCount = 0;
    float straightCount = 0;
    float straightFlushCount = 0;
    float royalFlushCount = 0 ;
    float fullHouseCount = 0;
    int runCount = 1000000;
    for(int i = 0; i < runCount; i++){
        std::vector<Card> deck = createDeckOfCards();
        shuffle(deck);
        Hand hand = getHand(deck);
//        for(Card card : hand.cards)
//            std::cout<< "Rank: " << card.rank << " and Suit: " << card.suit;
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
    
    std::cout << "Of " << runCount << " hands from " << runCount << " randomly generated decks, we have: " << (flushCount / (double) runCount) << "% flushes, "
        << (straightCount / (double) runCount) << "% straights, " << (straightFlushCount / (double) runCount) << "% straight flushes, "
    << (royalFlushCount / (double) runCount) << "% royal flushes, and " << (fullHouseCount / (double) runCount) << "% full houses" << '\n';
    

    
    return 0;
}
