#include <stdio.h>
#include <stdlib.h>
#include "card.h"

// CardValueArr[0] = "Invalid", 1..13 = Ace..King
const char* CardValueArr[CARD_COUNT]={"Invalid","A","2","3","4","5","6","7","8","9","10","J","Q","K"};

const char* getSuitName(Suit s) {
    switch (s) {
        case SPADES:   return "SPADES";
        case HEARTS:   return "HEARTS";
        case DIAMONDS: return "DIAMONDS";
        case CLUBS:    return "CLUBS";
        default:       return "INVALID SUIT";
    }
}

Card* makeCard(uint8_t value, Suit suit) {
    Card* newCard = malloc(sizeof(Card));
    if (!newCard) {
        fprintf(stderr, "Error: memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    newCard->encodedCard = ((value & 0xF) << 4) | (suit & 0xF);
    newCard->next = NULL;
    return newCard;
}


CardValue getCardValue(uint8_t encodedCard) {
    return (CardValue)((encodedCard >> 4) & 0xF); 
}

Suit getSuit(uint8_t encodedCard) {
    return (Suit)(encodedCard & 0xF);
}

void printCard(const Card* c) {
    if (!c) {
        printf("NULL card\n");
        return;
    } //getCardValue returns 4 high bits, getSuit returns 4  lower bits SuitName, getSuitName transport it to HEARTS/SPADES etc..
    printf("Card: %s of %s\n", CardValueArr[getCardValue(c->encodedCard)],getSuitName(getSuit(c->encodedCard)));
}

/*
void printBits(const Card* c) {
    if (!c) {
        printf("NULL card\n");
        return;
    }
    for (uint8_t mask = 1 << 7; mask; mask >>= 1) {
        printf("%d", (c->encodedCard & mask) ? 1 : 0);
        if (mask == (1 << 4)) printf(" "); // separate value/suit
    }
    puts("");
}
*/