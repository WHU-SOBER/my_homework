#include "util.h"
#include <stdio.h>
#include <string.h>
int ret;
int find = 0;
int y_dic[4] = {0, 1, 0, -1};
int x_dic[4] = {-1, 0, 1, 0};

void dfs_tool(game_state_t *map, int x, int y, int path[], int top){
	if (x == map->goal_x && y == map->goal_y){
		find = 1;
		ret = top;
		return ;
	}
	while(find != 1){
		int i = 0;		
//		printf("i = %d\n", i); //debug
//		printf("grid = %d\n", map->grid[x + x_dic[i]][y + y_dic[i]]); //debug
		while(i < 4){
//		printf("1.%d <> %d   %d <> %d\n",x + x_dic[i] , map->n , y + y_dic[i] , map->m);
			if(x + x_dic[i] > map->n || y + y_dic[i] > map->m){
				i++;
//				printf("1.grid = %d\n", map->grid[x + x_dic[i]][y + y_dic[i]]); //debug
			}
			else if (map->grid[x+x_dic[i]][y+y_dic[i]] !=0){
				i++;
//				printf("2.grid = %d\n", map->grid[x + x_dic[i]][y + y_dic[i]]); //debug
			} 
			else{
				break;
			}
		}
//		printf("i = %d\n", i); //debug
		if (i >= 4){
			break;
		}
//		printf("i = %d\n", i); //debug		
		top++;
//		printf("top = %d\n", top); //debug
		path[top] = i;
//		printf("path[top] = %d\n", path[top]); //debug
		map->grid[x + x_dic[i]][y + y_dic[i]]--;
		//printf("grid = %d\n", map->grid[x + x_dic[i]][y + y_dic[i]]); //debug
//		printf("grid = %d\n", map->grid[x + x_dic[i]][y + y_dic[i]]); //debug
		dfs_tool(map, x + x_dic[i], y + y_dic[i], path, top);
		top--;
	}
	return ;
}

char *dfs(game_state_t *map){
	int path[1024];
	dfs_tool(map, map->start_x, map->start_y, path, -1);
	char *temp = (char *)malloc(sizeof(char) * (ret + 2));
	int i;
	for (i = 0; i <= ret; i++){
		switch(path[i]){
			case 0:temp[i] = 'N';break;
			case 1:temp[i] = 'E';break;
			case 2:temp[i] = 'S';break;
			case 3:temp[i] = 'W';break;
		}
	}
	temp[i] = '\0';
	return temp;
}

int main() {
  game_state_t state;
  memset(&state, 0, sizeof(state));
  init(&state);
  // write your code here
  char *data = dfs(&state);
  printf("%s\n", data);
  free(data);
  // 
  destroy(&state);
  return 0;
}
