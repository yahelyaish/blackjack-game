#include <stdio.h>
#include <stdlib.h>
#include "cardList.h"


CardList* initCardList(void) {
    CardList* list = malloc(sizeof(CardList));
    if (!list) {
        fprintf(stderr, "Error: memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    list->head = NULL;
    list->tail = NULL;
    list->cardCount = 0;
    return list;
}


Card* cardRemoveAt(CardList* list, size_t index) {
    if (!list || index >= list->cardCount) return NULL;

    Card* prev = NULL;
    Card* curr = list->head;

    for (size_t i = 0; i < index; i++) {
        prev = curr;
        curr = curr->next;
    }

    if (!prev) { // removing head
        list->head = curr->next;
    } else {
        prev->next = curr->next;
    }

    if (curr == list->tail) {
        list->tail = prev;
    }

    curr->next = NULL;
    list->cardCount--;
    return curr;
}
/*
Card* popCard(CardList* list) {
    if (!list || !list->head) return NULL;

    Card* c = list->head;
    list->head = c->next;
    if (!list->head) {
        list->tail = NULL;
    }
    c->next = NULL;
    list->cardCount--;
    return c;
}
*/
void fillDeck(CardList* deck) {
    if (!deck) return;

    deck->head = NULL;
    deck->tail = NULL;
    deck->cardCount = 0;

    for (size_t value = 1; value <= 13; value++) {
        for (uint8_t suitMask = 1; suitMask <= 0x8; suitMask <<= 1) {
            Card* c = makeCard(value, (Suit)suitMask);
            addCardToEnd(deck, c);
        }
    }
}


void addCardToEnd(CardList* list, Card* card) {
    if (!list || !card) return;

    if (!list->head) { // empty list
        list->head = card;
        list->tail = card;
    } else {
        list->tail->next = card;
        list->tail = card;
    }
    list->cardCount++;
}

Card* dealCard(CardList* deck, CardList* target) {
    if (!deck || deck->cardCount == 0 || !target) return NULL;

    size_t index = (size_t)(rand() % deck->cardCount);
    Card* c = cardRemoveAt(deck, index);
    addCardToEnd(target, c);
    return c;
}

size_t getHandValue(CardList* list) {
    if (!list) return 0;

    Card* curr = list->head;
    size_t sum = 0;
    size_t aces = 0;

    while (curr) {
        size_t rank = (size_t)getCardValue(curr->encodedCard);
        if (rank == 1) {
            aces++;
            sum += 1;
        } else if (rank >= 10) {
            sum += 10;
        } else {
            sum += rank;
        }
        curr = curr->next;
    }

    if (aces > 0 && sum + 10 <= 21) {
        sum += 10;
    }
    return sum;
}

void freeCardList(CardList* list) {
    if (!list) return;

    Card* curr = list->head;
    while (curr) {
        Card* next = curr->next;
        free(curr);
        curr = next;
    }
    free(list);
}


void printCardList(const CardList* list) {
    if (!list || !list->head) {
        printf("List is empty.\n");
        return;
    }

    Card* curr = list->head;
    while (curr) {
        printCard(curr);
        curr = curr->next;
    }
}


