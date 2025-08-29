//
//  deckFunction.cpp
//  Cards
//
//  Created by Alexis Blood on 8/26/25.
//
#include "deckFunction.h"

// Creates a deck of cards
std::vector<Card> createDeckOfCards()
{
    std::vector<Card> deck;
    
    int ace = 14;
    
    for(int i = 2; i <= ace; i++)
    {
        Card cH {i, 'H'};
        deck.push_back(cH);
    }
    for(int i = 2; i <= ace; i++)
    {
        Card cS {i, 'S'};
        deck.push_back(cS);
    }
    for(int i = 2; i <= ace; i++)
    {
        Card cC {i, 'C'};
        deck.push_back(cC);
    }
    for(int i = 2; i <= ace; i++)
    {
        Card cD {i, 'D'};
        deck.push_back(cD);
    }
    
    return deck;
}

// Prints the deck
void printDeck(std::vector<Card>& deck)
{
    
    for(int i = 0; i < deck.size(); i++)
    {
        if(deck[i].rank == 13)
            std::cout << "K of " << deck[i].suit << std::endl;
        
        else if (deck[i].rank == 12)
            std::cout << "Q of " << deck[i].suit << std::endl;
        
        else if(deck[i].rank == 11)
            std::cout << "J of " << deck[i].suit << std::endl;
        
        else if(deck[i].rank == 14)
            std::cout << "A of " << deck[i].suit << std::endl;
        
        else
            std::cout << deck[i].rank << " of " << deck[i].suit << std::endl;
    }
}

// Prints the player's hand
void printHand(Hand hand)
{
    
    for(int i = 0; i < hand.cards.size(); i++)
    {
        if(hand.cards[i].rank == 13)
            std::cout << "K of " << hand.cards[i].suit << std::endl;
        
        else if (hand.cards[i].rank == 12)
            std::cout << "Q of " << hand.cards[i].suit << std::endl;
        
        else if(hand.cards[i].rank == 11)
            std::cout << "J of " << hand.cards[i].suit << std::endl;
        
        else if(hand.cards[i].rank == 14)
            std::cout << "A of " << hand.cards[i].suit << std::endl;
        
        else
            std::cout << hand.cards[i].rank << " of " << hand.cards[i].suit << std::endl;
    }
}

// Shuffles the deck
void shuffle(std::vector<Card>& deck)
{

    for(int i = deck.size()-1; i >= 0; i--)
    {
        int random_in_range = (std::rand() % deck.size());
        deck[i] = deck[random_in_range];
    }
}


Card drawCard(std::vector<Card>& deck)
{
    Card drawnCard = deck[deck.size()-1];
    deck.pop_back();
    return drawnCard;
}


Hand getHand(std::vector<Card>& deck)
{
    Hand hand;
    for(int i = 0; i < 5; i++)
    {
        hand.cards.push_back(drawCard(deck));
    }
    return hand;
}


void sortHand(Hand& hand)
{
    std::vector<Card> newCards;
    while(hand.cards.size() > 0)
    {
        int currentMin = hand.cards[0].rank;
        int minIndex = 0;
        for(int i = 0; i < hand.cards.size(); i++)
        {
            if(hand.cards[i].rank < currentMin)
            {
                currentMin = hand.cards[i].rank;
                minIndex = i;
            }
        }
        newCards.push_back(hand.cards[minIndex]);
        hand.cards.erase(hand.cards.begin() + minIndex);
    }
    
    hand.cards = newCards;
}


bool isFlush(Hand hand)
{
    char handSuit = hand.cards[0].suit;
    for(int i = 0; i < hand.cards.size(); i++)
        if (hand.cards[i].suit != handSuit)
            return false;
    return true;
}


bool isStraight(Hand hand)
{
    sortHand(hand);
    for(int i = 1; i < hand.cards.size(); i++)
    {
        if (hand.cards[i].rank < hand.cards[i-1].rank)
            return false;
    }
    return true;
}


bool isStraightFlush(Hand hand)
{
    if(isFlush(hand) == true && isStraight(hand) == true)
        return true;
    else
        return false;
}


bool isRoyalFlush(Hand hand)
{
    sortHand(hand);
    return isStraightFlush(hand) && hand.cards[0].rank == 10;
}


bool isFullHouse(Hand hand)
{
    if(hand.cards[0].rank == hand.cards[1].rank)
    {
        if(hand.cards[0].rank == hand.cards[2].rank)
        {
            if(hand.cards[3].rank == hand.cards[4].rank)
                return true;
        }
        if(hand.cards[0].rank != hand.cards[2].rank)
        {
            if(hand.cards[2].rank == hand.cards[3].rank && hand.cards[2].rank == hand.cards[4].rank)
                return true;
        }
    }
    
    return false;

}
