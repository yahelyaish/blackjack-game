#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"

int main(void) {
    srand(time(NULL));
    Game* g = calloc(1, sizeof(Game));
    if (!g) {
        fprintf(stderr, "Allocation failed!\n");
        exit(EXIT_FAILURE);
    }

    int choice = 0;
    while (1) {
        puts("Welcome To BlackJack! Choose Your Option!\n");
        puts("1) Start Game");
        puts("2) Exit");

        scanf("%d", &choice);
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF);
        if (choice == 1) {
            GameMenuFunc[PHASE_STARTGAME](g);
        } else if (choice == 2) {
            break;
        } else {
            puts("Invalid choice, try again.");
            continue;
        }
    }

    exitGame(g);
    free(g);

    return 0;
}
