#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
int ret;
int MAX = 0;
int y_dic[4] = {0, 1, 0, -1};
int x_dic[4] = {-1, 0, 1, 0};
char *bfs(game_state_t *map, int goal_x, int goal_y, int start_x, int start_y){
	int path[1024];
	int fi = -1;
	int pre[150][150];
	pre[goal_x][goal_y] = -1;
	int visited[150][150] = {0};
	int *data_x = (int *)malloc(ret * sizeof(int));
	int *data_y = (int *)malloc(ret * sizeof(int));
	int rear = 0, front = -1;
	front++;
	visited[start_x][start_y]--;
	data_x[front] = start_x;
	data_y[front] = start_y;
	int num_se = 0;
	while(rear <= front){	
		int x = data_x[rear];
		int y = data_y[rear];
		rear++;
		if (x == goal_x && y == goal_y){
			break;
		}
		for (int i = 0; i < 4; i++){
			int st_se = 1;
			for (int j = 0; j < map->num_ghosts; j++){
			    if ((y + y_dic[i] == map->ghost_y[j] && x + x_dic[i] == map->ghost_x[j])  || 
			     	(x + x_dic[i] + 1 == map->ghost_x[j] && y + y_dic[i] == map->ghost_y[j]) || 
			     	(x + x_dic[i] - 1 == map->ghost_x[j] && y + y_dic[i] == map->ghost_y[j]) ||
			     	(y + y_dic[i] + 1 == map->ghost_y[j] && x + x_dic[i] == map->ghost_x[j]) || 
			     	(y + y_dic[i] - 1 == map->ghost_y[j] && x + x_dic[i] == map->ghost_x[j])){			       							st_se = 0;
						visited[x + x_dic[i]][y + y_dic[i]]--;
			        	break;
			    	}    
				}
			if (st_se == 1 && num_se == 0 && map->grid[x + x_dic[i]][y + y_dic[i]] == 0){
				num_se++;
				fi = i;
			}
			if (st_se && map->grid[x + x_dic[i]][y + y_dic[i]] == 0
					&& visited[x+x_dic[i]][y+y_dic[i]] == 0 && (y + y_dic[i] != map->ghost_y[i] || x + x_dic[i] != map->ghost_x[i])){
				front++;
				data_x[front] = x + x_dic[i];
				data_y[front] = y + y_dic[i];
				pre[x + x_dic[i]][y + y_dic[i]] = i;
				visited[x + x_dic[i]][y + y_dic[i]]--;
			}
		}
	}  
	char *temp = (char *)malloc(sizeof(char) * (ret + 2));
	int x = goal_x, y = goal_y, i = 0;
	if (pre[goal_x][goal_y] == -1){
		switch(fi){
				case 0:printf("N");return;
				case 1:printf("E");return;
				case 2:printf("S");return;
				case 3:printf("W");return;
		}
		return ;
	}
	while (x != start_x || y != start_y){
		switch(pre[x][y]){
			case 0:x++;path[i] = 0;break;
			case 1:y--;path[i] = 1;break;
			case 2:x--;path[i] = 2;break;
			case 3:y++;path[i] = 3;break;
		}
		i++;
	}
	int j = 0;
	i = i - 1;
	switch(path[i]){
		case 0:temp[j] = 'N';break;
		case 1:temp[j] = 'E';break;
		case 2:temp[j] = 'S';break;
		case 3:temp[j] = 'W';break;
	}
	printf("%c", temp[j]);
	free(temp);
}

void search(game_state_t *map, int *aim_x, int *aim_y, int start_x, int start_y){
	int *data_x = (int *)malloc(ret * sizeof(int));
	int *data_y = (int *)malloc(ret * sizeof(int));
	int rear = 0, front = -1;
	int visited[150][150] = {0};
	front++;
	*aim_x = -1;
	*aim_y = -1;
	data_x[front] = start_x;
	data_y[front] = start_y;
	while(rear <= front){
		int x = data_x[rear];
		int y = data_y[rear];
		rear++;
		for (int i = 0; i < 4; i++){
			if (map->grid[x + x_dic[i]][y + y_dic[i]] == 0 && visited[x + x_dic[i]][y + y_dic[i]] == 0){
				front++;
				data_x[front] = x + x_dic[i];
				data_y[front] = y + y_dic[i];
				visited[x + x_dic[i]][y + y_dic[i]] = 1;
				if (map->food[x + x_dic[i]][y + y_dic[i]] == 1){
					*aim_x = x + x_dic[i];
					*aim_y = y + y_dic[i];
					map->food[x + x_dic[i]][y + y_dic[i]] = 0;
					free(data_x);
					free(data_y);
					return ;	
				}
			}
		}
	}
	free(data_x);
	free(data_y);
}

void greddy(game_state_t *state){
	int aim_x = 0, aim_y = 0;
	int stay_x, stay_y;
	stay_x = state->start_x;
	stay_y = state->start_y;
	search(state, &aim_x, &aim_y, stay_x, stay_y);
	if (aim_x == -1 || aim_y == -1)
		return;
	bfs(state, aim_x, aim_y, stay_x, stay_y);
}

int main() {
  game_state_t state;
  memset(&state, 0, sizeof(state));
  init(&state);
  // write your code here
  srand(time(0));
  greddy(&state); 
  destroy(&state);
  return 0;
}
