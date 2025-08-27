//
//  Cards.cpp
//  Cards
//
//  Created by Jonathan Pulsipher on 8/26/25.
//

#include "Cards.h"

void Initialize()
{
    //These are magic numbers, you could make them more intuitive
    //The name of the function could convey more meaning -> "CreateDeck()". Also, shuffling doesn't have to be automatic - that's your assumption but is not necessary.
    for(int i = 1; i <= 13; i++)
    {
        for(int j = 1; j <= 4; j++)
        {
            activeDeck.deck.push_back({i, j}); //NOTE: Card{rank, suit}
        }
    }
    Shuffle();
}

/*
 * Randomly re-orders cards in the deck
 */
void Shuffle(){
    std::vector<Card> shuffledDeck;
    while(activeDeck.deck.size() > 0)
    {
        int randomIndex = rand() % (activeDeck.deck.size() - 1);
        shuffledDeck.push_back(activeDeck.deck[randomIndex]);
        activeDeck.deck.erase(activeDeck.deck.begin() + randomIndex);
    }
    activeDeck.deck = shuffledDeck;
}

/*
 * Moves "top" card (last in the deck Vector) to discard and returns its rank
 *
 * Return:
 *   int representation of card
 */
Card Draw(){
    Card drawnCard = activeDeck.deck[activeDeck.deck.size() - 1];
    activeDeck.deck.pop_back();
    activeDeck.discard.push_back(drawnCard);
    return drawnCard;
}

/*
 * Converts int representation of card into user-friendly string
 *
 * Return:
 *   String letter or number of card
 */
std::string To_StringCard(Card card)
{
    std::string cardStr = std::to_string(card.rank);
    if(card.rank == 1)
        cardStr = "Ace";
    else if (card.rank == 11)
        cardStr += "Jack";
    else if (card.rank == 12)
        cardStr += "Queen";
    else if (card.rank == 13)
        cardStr += "King";
    cardStr += " of ";
    if(card.suit == 1)
        cardStr += "Hearts";
    else if (card.suit == 2)
        cardStr += "Diamonds";
    else if (card.suit == 3)
        cardStr += "Spades";
    else if (card.suit == 4)
        cardStr += "Clubs";
    return cardStr;
}

/*
 * Prints out the deck, starting with drawable cards in order from end to beginning, then discard pile the same way
 *
 * Return:
 *   String with "Cards in Draw Pile", then deck cards in order from top to bottom, then "Cards in Discard Pile:, then
 *   discard cards from top to bottom
 */
std::string To_StringDeck(){
    std::string deckStr = "In Draw Pile:\n";
    for(int i = 0; i < activeDeck.deck.size(); i++)
        deckStr += "\t" + To_StringCard(activeDeck.deck[i]) + '\n';
    deckStr += "In Discard Pile:\n";
    for(int i = 0; i < activeDeck.discard.size(); i++)
        deckStr += "\t" + To_StringCard(activeDeck.discard[i]) + '\n';
    return deckStr;
}
