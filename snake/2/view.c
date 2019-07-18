#include "view.h"
#include <stdio.h>
#include <stdlib.h>

const char grid[] = "-+X*";

void display(game_t *game) {
    system("cls");
    board_t *board = game->board;
    int i, j;
    for (i = 0; i < board->rows; i++) {
        for (j = 0; j < board->cols; j++) {
			if (i == game->snake1->head->row && j == game->snake1->head->col)
				printf("H");
			else if (i == game->snake2->head->row && j == game->snake2->head->col)
				printf("h");
			else
            printf("%c", grid[*board_cell(board, i, j)]);
        }
        puts("");
    }
}
