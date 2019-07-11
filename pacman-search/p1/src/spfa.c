#include "util.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define INF 0x3f3f3f
int ret;
int y_dic[4] = {0, 1, 0, -1};
int x_dic[4] = {-1, 0, 1, 0};

char *spfa(game_state_t *map){
	int path[1024];
	int prea[100][100];
	double dis[100][100];
	for (int i = 0; i < 100; i ++){
	    for (int j = 0; j < 100; j++){
	        dis[i][j] = INF;
	    }
	}
	int *data_x = (int *)malloc(3000 * sizeof(int));
	int *data_y = (int *)malloc(3000 * sizeof(int));
	int rear = 0, front = -1;
	front++;
	data_x[front] = map->start_x;
	data_y[front] = map->start_y;
	dis[map->start_x][map->start_y] = 0;
	while(rear <= front){
		int x = data_x[rear];
		int y = data_y[rear];
		rear++;
		map->grid[x][y]--;
/*		if (x == map->goal_x && y == map->goal_y){
			break;
		}*/
		for (int i = 0; i < 4; i++){
			if (map->grid[x + x_dic[i]][y + y_dic[i]] == 0 && (x + x_dic[i] != map->goal_x || y + y_dic[i] != map->goal_y)){
				front++;
				data_x[front] = x + x_dic[i];
				data_y[front] = y + y_dic[i];
				dis[x + x_dic[i]][y + y_dic[i]] = dis[x][y] + map->cost[x + x_dic[i]][y + y_dic[i]];
				prea[x + x_dic[i]][y + y_dic[i]] = i;
			    	map->grid[x + x_dic[i]][y + y_dic[i]]--;
			}		
			else if (map->grid[x + x_dic[i]][y + y_dic[i]] <= 0 && dis[x + x_dic[i]][y + y_dic[i]] > dis[x][y] + map->cost[x + x_dic[i]][y + y_dic[i]]){

				dis[x + x_dic[i]][y + y_dic[i]] = dis[x][y] + map->cost[x + x_dic[i]][y + y_dic[i]];
				prea[x + x_dic[i]][y + y_dic[i]] = i;
//			        printf("%d %d:%lf  i=%d\n",x + x_dic[i], y + y_dic[i], dis[x][y] + dis[x + x_dic[i]][y + y_dic[i]], prea[x + x_dic[i]][y + y_dic[i]] );
				front++;
				data_x[front] = x + x_dic[i];
				data_y[front] = y + y_dic[i];
			}
		}
	}

	char *temp = (char *)malloc(sizeof(char) * (ret + 2));
	int x = map->goal_x, y = map->goal_y, i = 0;
	while (x != map->start_x || y != map->start_y){
		switch(prea[x][y]){
			case 0:x++;path[i] = 0;break;
			case 1:y--;path[i] = 1;break;
			case 2:x--;path[i] = 2;break;
			case 3:y++;path[i] = 3;break;
		}
		i++;
	}
	int j = 0;
	for (i = i - 1; i >= 0; i--){
		switch(path[i]){
			case 0:temp[j] = 'N';break;
			case 1:temp[j] = 'E';break;
			case 2:temp[j] = 'S';break;
			case 3:temp[j] = 'W';break;
		}
		j++;
	}
	temp[j] = '\0';
	for (int i =  0; i < map->n; i++){
	    for (int j = 0; j < map->m; j++){
	        if (map->grid[i][j] == -1){
	               map->grid[i][j] = 0;
	        }
	    }
	}
	return temp;
}

int main() {
  game_state_t state;
  memset(&state, 0, sizeof(state));
  init(&state);
  // write your code here
  char *data = spfa(&state);
  printf("%s\n", data);
  free(data);
  // 
  destroy(&state);
  return 0;
}
