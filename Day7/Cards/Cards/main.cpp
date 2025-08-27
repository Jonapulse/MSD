//
//  main.cpp
//  Cards
//
//  Created by Alexis Blood on 8/26/25.
//  Working with Jon Pulsipher
//

#include <iostream>
#include "struct.h"
#include "deckFunction.h"

int main(int argc, const char * argv[]) {
    std::vector<Card> ourDeck = deckOfCards();
    
    // Testing shuffle
    //
//    printDeck(ourDeck);
//    shuffle(ourDeck);
//    printDeck(ourDeck);
    
    // Testing draw
    //
//    printDeck(ourDeck);
//    Card card = drawCard(ourDeck);
//    std::cout << "Rank: " << card.rank << ", suit: " + card.suit << '\n';
//    printDeck(ourDeck);
    
    // Testing Hand
    //
//    Hand hand = getHand(ourDeck);
//    for(int i = 0; i < hand.cards.size(); i++)
//        std::cout << "Rank: " << hand.cards[i].rank << ", suit: " +  hand.cards[i].suit << '\n';
//    return 0;
    
    // Testing Scoring Hands
    //
    std::vector<Card> straightTest = {{2, "Clubs"},{5, "Clubs"},{6, "Clubs"},{3, "Clubs"},{4, "Clubs"}};;
    Hand hand;
    hand.cards = straightTest;
    bool isStraight = isFlush(hand);
    
    std::cout << "This is a straight: " << isStraight << '\n';
}
