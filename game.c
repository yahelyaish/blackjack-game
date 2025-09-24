#include "game.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

//state machine
GameFunc GameMenuFunc[GAME_STEPS] = {
    startGame,
    bettingPhase,
    dealPhase,
    blackJackCheck,
    hitOrStand,
    dealerTurn,
    resultPhase,
    resetGamePhase,
    exitGame
};



void startGame(Game* g) {
    initGame(g);
    fillDeck(g->deck);
    GameMenuFunc[PHASE_BETTING](g);
}


void bettingPhase(Game* g) {
    if (g->Player_cash < 10 && g->pot == 0) {
        puts("\n*** Out of cash. Game Over. ***\n");
        GameMenuFunc[PHASE_EXIT](g);
        return;
    }

    size_t bet = 0;
    while (1) {
        puts("\n--- Place Your Bet ---");
        printStatus(g);  
        printf("Enter amount (multiples of 10, min 10 if pot empty): ");
        scanf("%zu", &bet);

        if (g->pot == 0 && bet < 10) {
            puts("Bet must be at least 10 when pot is empty");
            continue;
        }
        if (g->pot > 0 && bet == 0) break; 
        if (bet > g->Player_cash) {
            puts("Not enough money");
            continue;
        }
        if (bet % 10 != 0) {
            puts("Bet must be a multiple of 10");
            continue;
        }
        break;
    }

    g->Player_cash -= bet;
    g->pot += bet;

    puts("\n--- Updated Status ---");
    printStatus(g);
    puts("----------------------\n");

    GameMenuFunc[PHASE_DEAL](g);
}


void dealPhase(Game* g) {
    for (size_t i = 0; i < 2; i++) {
        dealCard(g->deck, g->Player);
        dealCard(g->deck, g->Dealer);
    }

    puts("\n--- Initial Deal ---");
    puts("Player's Cards:");
    printCardList(g->Player);
    puts("Dealer shows:");
    printCard(g->Dealer->head); 
    puts("----------------------\n");

    GameMenuFunc[PHASE_BLACKJACKCHECK](g);
}



void blackJackCheck(Game* g) {
    if (getHandValue(g->Player) == 21) {
        applyResult(g, BLACKJACK);
        GameMenuFunc[PHASE_RESET](g);
    } else {
        GameMenuFunc[PHASE_HITORSTAND](g);
    }
}


void hitOrStand(Game* g) {
    puts("\n--- Your Turn ---");
    puts("Do you want to HIT or STAND?");
    puts("1) HIT");
    puts("2) STAND");

    while (1) {
        int answer;
        scanf("%d", &answer);

        if (answer == 1) {
            puts("You Chose To Hit!");
            dealCard(g->deck, g->Player);
            puts("Player's Current Cards Are:");
            printCardList(g->Player);
            printf("Current value: %zu\n", getHandValue(g->Player));
            if (getHandValue(g->Player) > 21) {
                GameMenuFunc[PHASE_RESULT](g);
            } else {
                GameMenuFunc[PHASE_HITORSTAND](g);
            }
            break;
        } else if (answer == 2) {
            puts("You chose to STAND.");
            GameMenuFunc[PHASE_DEALER](g);
            break;
        } else {
            puts("Invalid choice. Try again:");
        }
    }
}



void dealerTurn(Game* g) {
    puts("\n--- Dealer's Turn ---");
    puts("Dealer's Cards:");
    printCardList(g->Dealer);

    while (getHandValue(g->Dealer) < 17) {
        Card* c = dealCard(g->deck, g->Dealer);
        puts("Dealer draws:");
        printCard(c);
    }

    printf("Dealer's final hand value: %zu\n", getHandValue(g->Dealer));
    puts("----------------------\n");

    GameMenuFunc[PHASE_RESULT](g);
}


void resultPhase(Game* g) {
    size_t playerVal = getHandValue(g->Player);
    size_t dealerVal = getHandValue(g->Dealer);

    if (playerVal > 21) {
        applyResult(g, PLAYER_BUST);
    } else if (dealerVal > 21) {
        applyResult(g, DEALER_BUST);
    } else if (playerVal > dealerVal) {
        applyResult(g, PLAYER_WIN);
    } else if (dealerVal > playerVal) {
        applyResult(g, DEALER_WIN);
    } else {
        applyResult(g, TIE);
    }
    printStatus(g);
    puts("Do you want to keep playing?\n1) Yes\n2) No");
    while (1) {
        int answer;
        scanf("%d", &answer);

        if (answer != 1 && answer != 2) {
            puts("Invalid answer! Try again");
            continue;
        }
        if (answer == 1) {
            GameMenuFunc[PHASE_RESET](g);
        } else {
            printf("You Got : %zu Cash Left\nCya Other Time\n",g->Player_cash);
            GameMenuFunc[PHASE_EXIT](g);
        }
        break;
    }
}


void applyResult(Game* g, ResultType r) {
    size_t playerVal = getHandValue(g->Player);
    size_t dealerVal = getHandValue(g->Dealer);

    puts("\n=== Round Result ===");
    printf(" Player's Hand : %zu\n", playerVal);
    printf(" Dealer's Hand : %zu\n", dealerVal);
    switch (r) {
        case BLACKJACK:
            puts(" -> Player has BLACKJACK!");
            g->Player_cash += g->pot + (g->pot * 1.5);
            g->pot = 0;
            break;
        case PLAYER_BUST:
            puts(" -> Player Busts! Dealer Wins.");
            g->pot = 0;
            break;
        case DEALER_BUST:
            puts(" -> Dealer Busts! Player Wins.");
            g->Player_cash += 2 * g->pot;
            g->pot = 0;
            break;
        case PLAYER_WIN:
            puts(" -> Player Wins!");
            g->Player_cash += 2 * g->pot;
            g->pot = 0;
            break;
        case DEALER_WIN:
            puts(" -> Dealer Wins!");
            g->pot = 0;
            break;
        case TIE:
            puts(" -> It's a Tie! Pot carries over.");
            break;
        default:
            puts(" -> Unknown result!");
            break;
    }
    puts("======================\n");
}



void resetGamePhase(Game* g) {
    freeCardList(g->deck);
    freeCardList(g->Player);
    freeCardList(g->Dealer);

    g->deck   = initCardList();
    g->Dealer = initCardList();
    g->Player = initCardList();

    fillDeck(g->deck);

    g->pot = 0;
    g->Player_bet = 0;

    GameMenuFunc[PHASE_BETTING](g);
}


void exitGame(Game* g) {
  if(g->deck)    freeCardList(g->deck);
  if(g->Player)  freeCardList(g->Player);
  if(g->Dealer)  freeCardList(g->Dealer);

    g->deck   = NULL;
    g->Player = NULL;
    g->Dealer = NULL;
}



void printStatus(Game* g) {
    puts("\n============================");
    printf(" Current Pot   : %zu\n", g->pot);
    printf(" Player's Cash : %zu\n", g->Player_cash);
    puts("============================\n");
}

void initGame(Game* g) {
    g->deck   = initCardList();
    g->Player = initCardList();
    g->Dealer = initCardList();

    g->pot = 0;
    g->Player_bet = 0;
    g->Player_cash = 1000;
}