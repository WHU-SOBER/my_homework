#include "util.h"
#include <stdio.h>
#include <string.h>
int ret;
int y_dic[4] = {0, 1, 0, -1};
int x_dic[4] = {-1, 0, 1, 0};

char *bfs(game_state_t *map){
	int path[1024];
	int pre[1024][1024];
	int *data_x = (int *)malloc(ret * sizeof(int));
	int *data_y = (int *)malloc(ret * sizeof(int));
	int rear = 0, front = -1;
//printf("%d<>%d", rear, front);
	front++;
	data_x[front] = map->start_x;
	data_y[front] = map->start_y;
//printf("%d<>%d", rear, front);
	while(rear <= front){
		int x = data_x[rear];
		int y = data_y[rear];
//printf("%d<>%d", rear, front);
		rear++;
		if (x == map->goal_x && y == map->goal_y){
			break;
		}
		for (int i = 0; i < 4; i++){
			if (map->grid[x + x_dic[i]][y + y_dic[i]] == 0){
				front++;
				data_x[front] = x + x_dic[i];
				data_y[front] = y + y_dic[i];
				pre[x + x_dic[i]][y + y_dic[i]] = i;
				map->grid[x + x_dic[i]][y + y_dic[i]]--;
			}
		}
	}

	char *temp = (char *)malloc(sizeof(char) * (ret + 2));
	int x = map->goal_x, y = map->goal_y, i = 0;
	while (x != map->start_x || y != map->start_y){
		switch(pre[x][y]){
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
	return temp;
}

int main() {
  game_state_t state;
  memset(&state, 0, sizeof(state));
  init(&state);
  // write your code here
  char *data = bfs(&state);
  printf("%s\n", data);
  free(data);
  // 
  destroy(&state);
  return 0;
}
