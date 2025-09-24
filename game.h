#ifndef GAME_H
#define GAME_H

#include "card.h"
#include "cardList.h"


#define GAME_STEPS PHASE_COUNT


typedef struct Game {
    CardList* deck;
    CardList* Player;
    CardList* Dealer;
    size_t pot;
    size_t Player_bet;
    size_t Player_cash;
} Game;


typedef enum {
    PHASE_STARTGAME,
    PHASE_BETTING,
    PHASE_DEAL,
    PHASE_BLACKJACKCHECK,
    PHASE_HITORSTAND,
    PHASE_DEALER,
    PHASE_RESULT,
    PHASE_RESET,
    PHASE_EXIT,
    PHASE_COUNT
} GamePhase;


typedef enum {PLAYER_WIN, DEALER_WIN, BLACKJACK, PLAYER_BUST, DEALER_BUST, TIE, RESULT_COUNT } ResultType;



typedef void (*GameFunc)(Game* g);


void startGame(Game* g);
void bettingPhase(Game* g);
void dealPhase(Game* g);
void blackJackCheck(Game* g);
void hitOrStand(Game* g);
void dealerTurn(Game* g);
void resultPhase(Game* g);
void resetGamePhase(Game* g);
void exitGame(Game* g);



void initGame(Game* g);
void applyResult(Game* g, ResultType r);
void printStatus(Game* g);


extern GameFunc GameMenuFunc[];

#endif // GAME_H
