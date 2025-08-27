//
//  deckFunction.cpp
//  Cards
//
//  Created by Alexis Blood on 8/26/25.
//
#include "deckFunction.h"
#include <vector>

const int HAND_SIZE = 5;

std::vector<Card> deckOfCards()
{

    std::vector<Card> deck;
    for(int i = 1; i <= 13; i++)
    {
        Card cH {i, "Hearts"};
        deck.push_back(cH);
    }
    for(int i = 1; i <= 13; i++)
    {
        Card cS {i, "Spades"};
        deck.push_back(cS);
    }
    for(int i = 1; i <= 13; i++)
    {
        Card cC {i, "Clovers"};
        deck.push_back(cC);
    }
    for(int i = 1; i <= 13; i++)
    {
        Card cD {i, "Diamonds"};
        deck.push_back(cD);
    }
    
    return deck;
}

void printDeck(std::vector<Card> deck)
{    
    for(int i = 0; i < deck.size(); i++)
    {
        if(deck[i].rank == 13)
            std::cout << "King of " << deck[i].suit << std::endl;
        else if (deck[i].rank == 12)
            std::cout << "Queen of " << deck[i].suit << std::endl;
        else if(deck[i].rank == 11)
            std::cout << "Jack of " << deck[i].suit << std::endl;
        else if(deck[i].rank == 1)
            std::cout << "Ace of " << deck[i].suit << std::endl;
        else
            std::cout << deck[i].rank << " of " << deck[i].suit << std::endl;
    }
}

void shuffle(std::vector<Card>& deck){
    for(int i = deck.size() - 1; i >= 0; i--)
    {
        int random_in_range =  std::rand() % deck.size();
        deck[i] = deck[random_in_range];
    }
}

Card drawCard(std::vector<Card>& deck)
{
    Card drawnCard = deck[deck.size() - 1];
    deck.pop_back();
    return drawnCard;
}

Hand getHand(std::vector<Card>& deck)
{
    Hand hand;
    for(int i = 0; i < HAND_SIZE; i++)
        hand.cards.push_back(drawCard(deck));
    return hand;
}

bool isFlush(Hand hand){
    std::string handSuit = hand.cards[0].suit;
    for(int i = 1 ; i < hand.cards.size(); i++)
        if(hand.cards[i].suit != handSuit)
            return false;
    return true;
}

void sortHand(Hand& hand)
{
    std::vector<Card> newCards;
    while(hand.cards.size() > 0)
    {
        int minRankSoFar = hand.cards[0].rank;
        int minIndex = 0;
        for(int i = 0; i < hand.cards.size(); i++)
        {
            if(hand.cards[i].rank < minRankSoFar)
            {
                minRankSoFar = hand.cards[i].rank;
                minIndex = i;
            }
        }
        newCards.push_back(hand.cards[minIndex]);
        hand.cards.erase(hand.cards.begin() + minIndex);
    }
    
    hand.cards = newCards;
}


bool isStraight(Hand hand){
    sortHand(hand);
    for(int i = 0; i < hand.cards.size() - 1; i++)
    {
        //Checking for Ace edge-case
        //
        if(!(hand.cards[i].rank == 1 && hand.cards[i + 1].rank == 11) ||
           hand.cards[i].rank + 1 != hand.cards[i + 1].rank)
            return false;
    }
    return true;
}

bool isStraightFlush(Hand hand){
    return isFlush(hand) && isStraight(hand);
}

bool isRoyalFlush(Hand hand)
{
    sortHand(hand);
    return isFlush(hand) && isStraight(hand) && hand.cards[0].rank == 10;
}

bool isFullHouse(Hand hand){
    std::vector<int> encounteredRanks;
    std::vector<int> encounteredRankCounts;
    for(int i = 0; i < hand.cards.size(); i++)
    {
        if(encounteredRanks.size() == 0)
        {
            encounteredRanks.push_back(hand.cards[i].rank);
            encounteredRankCounts.push_back(1);
        }
        else {
            bool matchFound = false;
            for(int j = 0; j < encounteredRanks.size(); j++)
            {
                if(encounteredRanks[j] == hand.cards[i].rank){
                    matchFound = true;
                    encounteredRankCounts[j] += 1;
                }
            }
            if(!matchFound && encounteredRanks.size() < 2)
            {
                encounteredRanks.push_back(hand.cards[i].rank);
                encounteredRankCounts.push_back(1);
            } else
                return false;
        }
        return ((encounteredRankCounts[0] == 2 && encounteredRankCounts[1] == 3)
                || (encounteredRankCounts[1] == 2 && encounteredRankCounts[0] == 3));
    }
    return true;
}


