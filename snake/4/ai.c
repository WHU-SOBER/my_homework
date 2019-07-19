
#include "ai.h"
#include"game.h"
#include <stdio.h>
#include<math.h>
#define max	10000
#define MAX	100

// 存路径
int ans_x[111], ans_y[111], cnt = 0;

const static int dx[] = { 0, 1, 0, -1 };
const static int dy[] = { 1, 0, -1, 0 };

typedef struct unions {
	int position;
	int time;
	int parent;
	int heading;
}unions;

typedef struct queue {
	unions data[10000];
	int front;
	int rear;
}queue;


int trans(int z1, int z2, int size);
void init_dis(snake_t *snake, game_t *game, int dis[]);
int bfs(game_t *game, int goal_x, int goal_y);
int develop(int sx, int sy, game_t *game);
int judge(snake_t *snake1, snake_t *snake2);

int bfs(game_t *game, int goal_x, int goal_y) {
	int x = game->snake1->head->row;
	int y = game->snake1->head->col;

	queue qu;
	int dis[max];
	for (int i = 0; i < max; i++) {
		dis[i] = -1;
	}

	init_dis(game->snake1, game, dis);
	init_dis(game->snake2, game, dis);

	int flag = 0;
	unions p, u, q;
	direction_t path;
	int vis[max][200] = { 0 };
	//int d[] = { -game->board->cols,1,game->board->cols,-1 };
	int d[] = { 1,game->board->cols,-1,-game->board->cols };
	qu.front = -1;
	qu.rear = 0;
	p.position = x * game->board->cols + y;
	p.parent = -1;
	p.time = 0;
	p.heading = game->snake1->heading;
	qu.data[qu.rear] = p;
	vis[p.position][0] = 1;
	while (qu.front < qu.rear) {
		qu.front++;
		p = qu.data[qu.front];
		if (p.position == goal_x * game->board->cols + goal_y) {
			u = p;
			//printf("yes\n");
			while (u.parent != -1) {
				q = u;
				u = qu.data[u.parent];
			}
			flag = 1;
			path = trans(u.position, q.position, game->board->cols);
			return path;
		}
		int dz;
		u = p;
		int ddf = 0;
		for (int k = 0; k < 4; k++) {
			if (p.heading != (k + 2) % 4) {
				dz = p.position + d[k];
				if (dz >= 0 && dz < game->board->cols*game->board->rows && (game->board->cells[dz] == CELL_OPEN|| game->board->cells[dz] == CELL_FOOD
					|| game->board->cells[dz] == CELL_SNAKE && dis[dz] <= u.time ) && vis[dz][u.time + 1] == 0) {
					qu.rear++;
					u.position = dz;
					u.time++;
					ddf = 1;
					u.parent = qu.front;
					u.heading = k;
					qu.data[qu.rear] = u;
					vis[u.position][u.time] = 1;
				}
			}
		}

		if(ddf == 0){
			for(int k = 0; k<4;k++){
				if(p.heading != (k + 2) % 4){
					dz = p.position + d[k];
					if(game->board->cells[dz] == CELL_FOOD){
						qu.rear++;
						u.position = dz;
						u.time++;
						
						u.parent = qu.front;
						u.heading = k;
						qu.data[qu.rear] = u;
						vis[u.position][u.time] = 1;
					}
				}
			}
		}

	}
	if (flag == 0) {
		int z = x * game->board->cols + y;
		for (int k = 0; k < 4; k++) {
			if (game->board->cells[z + d[k]] == CELL_OPEN || game->board->cells[z + d[k]] == CELL_FOOD) {
				//printf("%d\n", k);
				return k;
			}
		}
	}
}


int trans(int z1, int z2, int size) {
	if (z1 - z2 == size)
		return 3;
	else if (z1 - z2 == -size)
		return 1;
	else if (z1 - z2 == -1)
		return 0;
	else if (z1 - z2 == 1)
		return 2;
}


int develop(int sx, int sy, game_t *game){
	for(int k = 0; k < 4; k++){
		int di = sx + 2*dx[k];
		int dj = sy + 2*dy[k];
		if(game->board->cells[di*game->board->cols+dj] == CELL_WALL){
			return 1;
		}
	}
	return 0;
}


int judge(snake_t *snake1, snake_t *snake2){
	int d = fabs(snake1->head->row-snake2->head->row)+fabs(snake1->head->col-snake2->head->col);
	if(d%2 == 0)
		return 1;
	else
		return 0;
}

void init_dis(snake_t *snake, game_t *game, int dis[]) {
	snake_node_t *p;
	int i = 0;
	p = snake->head;
	while (p != snake->tail) {
		i++;
		p = p->next;
	}
	p = snake->head;
	while (p != snake->tail) {
		dis[p->row *game->board->cols + p->col] = snake->growth + i;
		//printf("%d\n",dis[p->row *game->board->cols+p->col]);
		p = p->next;
		i--;
	}
	dis[p->row *game->board->cols + p->col] = snake->growth;
}
/*
// sx, sy: 源点
// path_x, path_y, top: 已走过的路径
// vis: 被访问过的路径
// a: 地图
// passed: 有没有经过food
// zx, zy: 终点
void dfs(int sx, int sy, int *path_x, int *path_y,
	int top, int vis[][10], int a[][10], int passed,
	int zx, int zy) {
	// 更新答案
	if (passed && top > cnt && sx == zx && sy == zy) {
		cnt = top;
		for (int i = 0; i < cnt; i++) {
			ans_x[i] = path_x[i];
			ans_y[i] = path_y[i];
		}
	}

	for (int i = 0; i < 4; i++) {
		int tx = sx + dx[i], ty = sy + dy[i];
		if (tx >= 0 && tx < 8 && ty >= 0 && ty < 8 && !vis[tx][ty]
			&& (a[tx][ty] != 1||(tx == sx && ty == sy))) {
			vis[tx][ty] = 1;
			path_x[top] = tx, path_y[top] = ty;
			dfs(tx, ty, path_x, path_y, top + 1, vis, a,
				passed | (a[tx][ty] == 2), zx, zy);
			vis[tx][ty] = 0;
		}
	}
}

void get_path(int a[][10], int sx, int sy, int zx, int zy) {
	cnt = 0;
	int vis[10][10] = { 0 };
	vis[sx][sy] = 1;
	int path_x[111] = { sx }, path_y[111] = { sy };
	dfs(sx, sy, path_x, path_y, 1, vis, a, 0, zx, zy);
	for (int i = 0; i < cnt; i++) {
		printf("%d, %d\n", ans_x[i], ans_y[i]);
	}
}

int trans(int z1, int z2, int size) {
	if (z1 - z2 == size)
		return 0;
	else if (z1 - z2 == -size)
		return 2;
	else if (z1 - z2 == -1)
		return 1;
	else if (z1 - z2 == 1)
		return 3;
}*/
direction_t get_action1(game_t *game) {
	/*int a[10][10];
	for (int i = 0; i < game->board->rows; i++)
	{
		for (int j = 0; j < game->board->cols; j++)
		{
			a[i][j] = game->board->cells[i * game->board->cols + j];
			if (a[i][j] == CELL_FOOD)
				a[i][j] = 2;
			else if (a[i][j] == CELL_OPEN)
				a[i][j] = 0;
			else
				a[i][j] = 1;
		}
	}
	int sx = game->snake1->head->row, sy = game->snake1->head->col;
	get_path(a, sx, sy, game->snake1->tail->row, game->snake1->tail->row);
	return trans(ans_x[0] * game->board->cols + ans_y[0], ans_x[1] * game->board->cols + ans_y[1], game->board->cols);*/
	if(judge(game->snake1,game->snake2) == 1)
		return bfs(game,game->snake2->head->row,game->snake2->head->col);
	
	else{
		
		int sx = game->snake1->head->row;
		int sy = game->snake1->head->col;
		for(int k = 0;k < 4;k++){
			int di = sx + dx[k];
			int dj = sy + dy[k];
			if(game->board->cells[di*game->board->cols+dj] == CELL_OPEN){
				//printf("%d--%d\n",game->board->cells[di*game->board->cols+dj],k);
				return k;
			}
		}
		for(int k = 0;k < 4;k++){
			int di = sx + dx[k];
			int dj = sy + dy[k];
			if(game->board->cells[di*game->board->cols+dj] == CELL_FOOD){
				//printf("%d--%d\n",game->board->cells[di*game->board->cols+dj],k);
				return k;
			}
		}
	}
}
