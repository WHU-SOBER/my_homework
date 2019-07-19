#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include <time.h>




board_t *create_board(int rows, int cols){
	board_t *board_new;
	board_new = (board_t*)malloc(sizeof(board_t));
    board_new->rows = rows;
	board_new->cols = cols;
	board_new->cells = (cell_t*)malloc(rows*cols*sizeof(cell_t));
	return board_new;
}



void destroy_board(board_t  *board){	
	free(board->cells);
	board->cells  = NULL;
	if(board!=NULL){
		free(board);
	}
}



cell_t *board_cell(board_t *board, int row, int col){
	if(row >= board->rows || col >= board->cols || row < 0 ||col < 0){
		return NULL;
	}
	return &(board->cells[row*board->cols+col]);
}



snake_t *create_snake(board_t *board, int row, int col, direction_t heading){
	board->cells[row * (board->cols) + col] = CELL_SNAKE;
	snake_t *snake_new;
	snake_new = (snake_t*)malloc(sizeof(snake_t));
    	snake_new->head = (snake_node_t *)malloc(sizeof(snake_node_t));
	snake_new->head->row = row;
	snake_new->head->col = col;
	snake_new->head->next = NULL;
	snake_new->tail = snake_new->head;
	snake_new->heading = heading;
	return snake_new;
}




void destroy_snake(snake_t *snake)
{
	snake_node_t *temp = snake->head;
	while (snake->head != NULL)
	{
		temp = snake->head;
		snake->head = snake->head->next;
		free(temp);
	}
	snake->head = NULL;
	snake->tail = NULL;
	free(snake);
}




void randomly_add_food(board_t *board, float probability)
{
	static int a = 1;
	if (a == 1)
	{
		srand((unsigned)time(NULL));
		a = 0;
	}
	int open_cells[10000];
	int count = 0;
	cell_t cell;
	for (int i = 0; i < board->rows; i++)
	{
		for (int j = 0; j < board->rows; j++)
		{
			if (board->cells[i * board->cols + j] == CELL_OPEN)
			{
				open_cells[count] = i * board->cols + j;
				count++;
			}
		}
	}
	if ((float)rand() / RAND_MAX <= probability)
		board->cells[open_cells[rand() % count]] = CELL_FOOD;
}


void set_direction(snake_t *snake, direction_t d){
	snake->heading = d;
}



void update_snake_head(snake_t *snake,board_t *board, int growth_per_food){	
	if(snake->head == NULL)
		return;	
	snake_node_t *p;
	p = (snake_node_t*)malloc(sizeof(snake_node_t));
	p->row = snake->head->row;
	p->col = snake->head->col;
	switch(snake->heading){
		case EAST:p->col++;		break;
		case SOUTH:p->row++;		break;
		case WEST:p->col--;		break;
		case NORTH:p->row--;	
	}
	p->next = snake->head;
	snake->head = p;
	if(board->cells[p->row*board->cols+p->col] == CELL_FOOD)
		snake->growth += growth_per_food;
	if(snake->growth>0)
		snake->growth--;
	
}



void update_snake_tail(snake_t *snake,board_t *board){
	if(snake->growth == 0){
		snake_node_t *p;
		p = snake->head;
		while(p->next != snake->tail){
			p = p->next;
		}
		board->cells[snake->tail->row*board->cols+snake->tail->col] = CELL_OPEN;
		free(snake->tail);
		snake->tail = p;
		p->next = NULL;
		
	}
}



int next_frame(game_t *cur_game){
	randomly_add_food(cur_game->board,cur_game->food_probability);
	update_snake_head(cur_game->snake,cur_game->board,cur_game->growth_per_food);
	update_snake_tail(cur_game->snake,cur_game->board);
	if(cur_game->board->cells[cur_game->snake->head->row*cur_game->board->cols+cur_game->snake->head->col] == CELL_WALL 
	||cur_game->board->cells[cur_game->snake->head->row*cur_game->board->cols+cur_game->snake->head->col] == CELL_SNAKE)
    		return 1;
	cur_game->board->cells[cur_game->snake->head->row*cur_game->board->cols+cur_game->snake->head->col] = CELL_SNAKE;
	return 0;
	
}




