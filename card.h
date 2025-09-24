#ifndef CARD_H
#define CARD_H

#include <stdint.h>


typedef enum {SPADES = 0x1, HEARTS = 0x2, DIAMONDS = 0x4, CLUBS  = 0x8 } Suit;

typedef enum { Ace=1,TWO,THREE,FOUR,FIVE,SIX,SEVEN,EIGHT,NINE,TEN,JACK,QUEEN,KING, CARD_COUNT } CardValue;

extern const char* CardValueArr[CARD_COUNT];


typedef struct Card {
    uint8_t encodedCard;
    struct Card* next;
} Card;


Card* makeCard(uint8_t value, Suit suit);   // Create a new card
CardValue getCardValue(uint8_t encodedCard);  // Extract value (1–13)
Suit getSuit(uint8_t encodedCard);          // Extract suit
const char* getSuitName(Suit suit);         // Get suit name as string
void printCard(const Card* c);              // Print single card
void printBits(const Card* c);              // Debug: print raw bits

#endif // CARD_H
