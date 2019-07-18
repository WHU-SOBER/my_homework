#include <stdio.h>
#include <stdlib.h>
#include "file.h"
#include <assert.h>
#include <math.h>
void test_create_game()
{
	game_t *game = create_game("simple.txt");
	assert(game->board->rows == 30);
	assert(game->board->cols == 40);
	assert(fabs(game->time_step - 0.2) < 10e-2);
	assert(fabs(game->food_probability - 0.1) < 10e-2);
	assert(game->growth_per_food == 8);
	for(int i = 0; i < game->board->rows; i++)
	{
		for(int j = 0; j < game->board->cols; j++)
		{
			printf("%d", game->board->cells[i * game->board->cols + j]);
		}
		printf("\n");
	}
	destroy_game(game);
}


void test_destroy_game()
{
	game_t *game = create_game("simple.txt");
	destroy_game(game);
	game = NULL;
	assert(game == NULL);
}
int main()
{
	test_create_game();
	test_destroy_game();
	return 0;
}
