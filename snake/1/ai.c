#include "ai.h"
#include"game.h"
#include <stdio.h>
#define max	10000
#define MAX	100


typedef struct unions{
	int position;
	int time;
	int parent;
	int heading;
}unions;

typedef struct queue{
	unions data[10000];
	int front;
	int rear;
}queue;


int trans(int z1, int z2, int size);
void init_dis(snake_t *snake,game_t *game, int dis[]);
int bfs( game_t *game);


direction_t get_action(game_t* game) {
	return bfs(game);
}

int bfs( game_t *game){
	int x = game->snake->head->row;
	int y = game->snake->head->col;

	queue qu;
	int dis[max];
	for(int i = 0;i<max; i++){
		dis[i] = -1;
	}
    init_dis(game->snake,game,dis);
	
	int flag = 0;
	unions p,u,q;
	direction_t path;
	int vis[max][200] = {0};
	int d[] = {-game->board->cols,1,game->board->cols,-1};
	qu.front = -1;
	qu.rear = 0;
	p.position = x*game->board->cols+y;
	p.parent = -1;
	p.time = 0;
	p.heading = game->snake->heading;
	qu.data[qu.rear] = p;
	vis[p.position][0] = 1;
	while(qu.front<qu.rear){
		qu.front++;
		p = qu.data[qu.front];
		if(game->board->cells[p.position] == CELL_FOOD){
			u = p;
			while(u.parent!=-1){
				 q = u;
				 u = qu.data[u.parent];
			}
			flag = 1;
			path = trans(u.position,q.position,game->board->cols);
			return path;
		}
		int dz;
		u = p;
		for(int k = 0; k < 4;k++){
			if(p.heading != (k + 2) % 4){
				dz = p.position + d[k];
				if(dz>=0 && dz<game->board->cols*game->board->rows && (game->board->cells[dz] == CELL_OPEN ||game->board->cells[dz] == CELL_FOOD
					||game->board->cells[dz] == CELL_SNAKE && dis[dz] <= u.time-1) && vis[dz][u.time+1] == 0 ){
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
	if(flag == 0 ){
		int z = x*game->board->cols+y;
		for(int k = 0 ;k<4;k++){
			if(game->board->cells[z+d[k]] == CELL_OPEN ||game->board->cells[z+d[k]] == CELL_FOOD)
				return k;
		}
	}
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

void init_dis(snake_t *snake,game_t *game, int dis[]){
	snake_node_t *p;
	int i = 0;
	p = snake->head;
	while(p!=snake->tail){
		i++;
		p = p->next;
	}
    p = snake->head;
	while(p!=snake->tail){
		dis[p->row *game->board->cols+p->col] = snake->growth + i;
		//printf("%d\n",dis[p->row *game->board->cols+p->col]);
		p = p->next;
		i--;
	}
	dis[p->row *game->board->cols+p->col] = snake->growth;	
}






