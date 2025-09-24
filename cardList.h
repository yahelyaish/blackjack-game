#ifndef CARDLIST_H
#define CARDLIST_H

#include "card.h"


typedef struct CardList {
    Card* head;
    Card* tail;
    size_t cardCount;
} CardList;



CardList* initCardList(void);          // Allocate and initialize a new empty list
void freeCardList(CardList* list);     // Free all nodes and the list itself



void fillDeck(CardList* deck);                     // Fill list with a standard 52-card deck
Card* cardRemoveAt(CardList* list, size_t index);  // Remove card at index (e.g. for shuffle)
//Card* popCard(CardList* list);                     // Pop card from head


void addCardToEnd(CardList* list, Card* card);     // Add specific card to end of hand
Card* dealCard(CardList* deck, CardList* target);   // Deal card from deck → target (player/dealer)
size_t getHandValue(CardList* list);               // Calculate total hand value (with Aces logic)


void printCardList(const CardList* list);          // Print all cards in the list

#endif // CARDLIST_H
