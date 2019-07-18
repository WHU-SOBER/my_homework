#include<stdio.h>
#include<stdlib.h>
#include"file.h"
#include"game.h"
game_t *create_game(const char *file_name)
{	
	cell_t cell;
	direction_t direction;
	FILE *fp = fopen(file_name, "r");
	game_t *game = (game_t*)malloc(sizeof(game_t));
	int rows,cols;
	fscanf(fp, "%d%d%f%f%d", &rows, &cols, &game->time_step, &game->food_probability, &game->growth_per_food);
	game->board = create_board(rows, cols);
	for(int i = 0; i < rows; i++)
	{
		for(int j = 0; j < cols; j++)
		{
			char c;
			fscanf(fp, "%c", &c);
			if (c == 'X')
				game->board->cells[i * cols + j] = CELL_WALL;
			else if (c == '-')
				game->board->cells[i * cols + j] = CELL_OPEN;
			else if (c != '\n')
			{
				game->board->cells[i * cols + j] = CELL_SNAKE;
				if (c == 'N')
					game->snake = create_snake(game->board, i, j, NORTH);
				else if (c == 'E')
					game->snake = create_snake(game->board, i, j, EAST);
				else if (c == 'S')
					game->snake = create_snake(game->board, i, j, SOUTH);
				else if (c == 'W')
					game->snake = create_snake(game->board, i, j, WEST);
			}
			else
				j--;
		}
	}
	fclose(fp);
	fp = NULL;
	return game;
}

void destroy_game(game_t *game)
{
	destroy_board(game->board);
	destroy_snake(game->snake);
	free(game);
}
