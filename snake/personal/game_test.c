#include "game.h"
#include<stdio.h>
#include <assert.h>
#include <stdlib.h>

void test_create_board() {
  	board_t* board = create_board(5, 5);
  	assert(board != NULL);
  	assert(board_cell(board, 0, 0) != NULL);
  	cell_t* cell = board_cell(board, 3, 2);
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			board->cells[i * 5 + j] = CELL_OPEN;
		}
	}
  	assert(cell != NULL && *cell == CELL_OPEN);
  	assert(board_cell(board, -1, 0) == NULL);
  	assert(board_cell(board, 0, 5) == NULL);
  	assert(board_cell(board, 5, 5) == NULL);
  	assert(board_cell(board, 4, 4) != NULL);
  	destroy_board(board);
}

void test_destroy_board(){
	board_t* board = create_board(5, 5);
	assert(board != NULL);
	destroy_board(board);
	assert(board_cell(board, 0, 0) == NULL);
}

void test_create_snake(){
    board_t *board;
    board = create_board(10,10);
    assert(board != NULL);
    assert(board_cell(board, 0, 0) != NULL);
    snake_t *snake;
    snake = create_snake(board, 5, 6, SOUTH);
    assert(snake->head->row == 5);
    assert(snake->head->col == 6);
    assert(snake->tail->row == 5);
    assert(snake->tail->col == 6);
    assert(snake->head->next == NULL);
    assert(snake->tail->next == NULL);
    assert(snake->heading == SOUTH);
	destroy_snake(snake);
    destroy_board(board);

}

void test_board_cell(){
	board_t *board;
    board = create_board(10,10);
	assert(board != NULL);
	assert(board_cell(board, 0, 0) != NULL);
	assert(board_cell(board, 4, 4) != NULL);
	assert(board_cell(board, -1, 0) == NULL);
  	assert(board_cell(board, 0, 10) == NULL);
  	assert(board_cell(board, 10, 10) == NULL);
    destroy_board(board);

}

void test_destroy_snake(){
	board_t *board;
    board = create_board(10,10);
	assert(board != NULL);
	assert(board_cell(board, 0, 0) != NULL);
    snake_t *snake;
    snake = create_snake(board,5,5,SOUTH);
	destroy_snake(snake);
	snake = NULL;
    assert(snake == NULL);
	destroy_board(board);
}

void test_randomly_add_food(){
	float probability = 1;
	board_t *board;
	board = create_board(10,10);
	assert(board != NULL);
	assert(board_cell(board, 0, 0) != NULL);
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			board->cells[i * 10 + j] = CELL_OPEN;
		}
	}
    randomly_add_food(board, probability);
    int flag = 0;
    for(int i = 0;i<board->rows;i++){
        for(int j = 0;j<board->cols;j++){
            if(board->cells[i*board->cols+j] == CELL_FOOD){
                flag = 1;
                break;
            }
  
        }
    }
    assert(flag == 1);
    destroy_board(board);

}

void test_set_direction(){
	snake_t *snake;
	snake = (snake_t*)malloc(sizeof(snake_t));
	snake->heading = NORTH;
	set_direction(snake, SOUTH);
	assert(snake->heading == SOUTH);
	free(snake);
}
void test_update_snake_head(){
	direction_t direction;

	board_t *board;
	board = create_board(10,10);
	assert(board != NULL);
	assert(board_cell(board, 0, 0) != NULL);	
	snake_t *snake;
	snake = create_snake(board,5,5,1);
	snake->growth = 0;
	update_snake_head(snake,board,3);
	assert(snake->head->row == 6 && snake->head->col == 5 );
	destroy_snake(snake);
	destroy_board(board);

}
void test_update_snake_tail(){
    board_t *board;
    board = create_board(10,10);
	assert(board != NULL);
	assert(board_cell(board, 0, 0) != NULL);
    snake_t *snake;
    snake = create_snake(board,5,5,SOUTH);
	snake->growth = 0;
	update_snake_head(snake,board,3);
    update_snake_tail(snake,board);
	assert(snake->tail->row == 6 && snake->tail->col == 5);
	destroy_snake(snake);
    destroy_board(board);

}

void test_next_frame(){
	game_t *cur_game;
	cur_game = (game_t*)malloc(sizeof(game_t));
	cur_game->board = create_board(5,5);
	cur_game->snake = create_snake(cur_game->board,3,3,SOUTH);
	cur_game->food_probability = 1;
	cur_game->growth_per_food = 1;
	cur_game->snake->growth = 0;
	for(int i = 0;i<5;i++){
		for(int j = 0;j<5;j++){
			cur_game->board->cells[i*5+j] = CELL_OPEN;
		}
	}
	next_frame(cur_game);
	//printf("%d",next_frame(cur_game));
    destroy_snake(cur_game->snake);
	destroy_board(cur_game->board);
	free(cur_game);
}

int main() {
  	test_create_board();
	test_destroy_board();
	test_board_cell();
	test_create_snake();
	test_destroy_snake();
	test_randomly_add_food();
	test_set_direction();
	test_update_snake_head();
	test_update_snake_tail();
	test_next_frame();
  	return 0;
}
