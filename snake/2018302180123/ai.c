#include "game.h"
#define MAX	100
#include<stdio.h>

int ans_x[MAX], ans_y[MAX], cnt = 0;
int vis[MAX][MAX] = {0};


int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

void dfs(int sx, int sy, int *path_x, int *path_y,
         int top, int vis[][MAX], int a[][MAX],game_t *game);

int get_path(int a[][MAX], int sx, int sy, game_t *game);

int trans(int z1, int z2, int size);


void dfs(int sx, int sy, int *path_x, int *path_y,
         int top, int vis[][MAX], int a[][MAX],game_t *game) {
  if (top > cnt) {
    cnt = top;
    for (int i = 0; i < cnt; i++) {
      ans_x[i] = path_x[i];
      ans_y[i] = path_y[i];
    }
  }
  
  for (int i = 0; i < 4; i++) {
    int tx = sx + dx[i], ty = sy + dy[i];
    if (tx >= 0 && tx < game->board->rows && ty >= 0 && ty < game->board->cols && vis[tx][ty] == 0
        && a[tx][ty] == 0) {
      vis[tx][ty] = 1;
      path_x[top] = tx, path_y[top] = ty;
      dfs(tx, ty, path_x, path_y, top + 1, vis, a,game);
      vis[tx][ty] = 0;
    }
  }
}

int get_path(int a[][MAX], int sx, int sy,game_t *game) {
 
  vis[sx][sy] = 1;
  int path_x[1000] = {0}, path_y[1000]={0};
  path_x[0] = sx;
  path_y[0] = sy;
  dfs(sx, sy, path_x, path_y, 1, vis, a, game);
  int u = ans_x[0]*game->board->cols+ans_y[0];
  if(path_x[1] == 0 && path_y[1] == 0){
	  for(int i = 0;i<game->board->rows;i++){
		  for(int j = 0;j<game->board->cols;j++){
			  vis[i][j] = 0;
		  }
	  }
  }
  int v = ans_x[1]*game->board->cols+ans_y[1];
  return trans(u,v,game->board->cols);
}

int get_action(game_t *game) {
  int a[MAX][MAX];
  for(int i = 0 ; i < game->board->cols*game->board->rows;i++){
	  if(game->board->cells[i] == CELL_WALL || game->board->cells[i] == CELL_SNAKE /*&& game->snake->tail->row*game->board->cols+game->snake->tail->col != i*/)
		  a[i/game->board->cols][i%game->board->cols] = 1;
	  else
		  a[i/game->board->cols][i%game->board->cols] = 0;
  }
  cnt = 0;
  int sx = game->snake->head->row, sy = game->snake->head->col; 
  return get_path(a, sx, sy, game);
}

int trans(int z1, int z2, int size){
	if(z1 - z2 == size)
		return 0;
	else if(z1 -z2 == -size)
		return 2;
	else if(z1 - z2 == -1)
		return 1;
	else if(z1 - z2 == 1)
		return 3;
}
