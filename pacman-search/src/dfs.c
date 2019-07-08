#include "util.h"
#include <stdio.h>
#include <string.h>
#define MAXSIZE 1000
char result[MAXSIZE];
int flag[MAXSIZE][MAXSIZE];

void DFS(int start_x, int start_y, int goal_x, int goal_y, game_state_t state)
{
	if (start_x == goal_x && start_y == goal_y)
	{
		int i = -1;
		int x = state.start_x;
		int y = state.start_y;
		while (!(x == goal_x && y == goal_y))
		{
			i++;
			switch (flag[x][y])
			{
			case 0:result[i] = 'N';x--; break;
			case 1:result[i] = 'E';y++; break;
			case 2:result[i] = 'S';x++; break;
			case 3:result[i] = 'W';y--; break;
			}
		}
		i++;
		result[i] = '\0';
		printf("%s\n", result);
	}
	else
	{
		int dir = -1;
		while (dir < 4)
		{
			int l = start_x;
			int r = start_y;
			dir++;
			switch (dir) {
				case 0:l--; break;
				case 1:r++; break;
				case 2:l++; break;
				case 3:r--; break;
			}
			if (state.grid[l][r] == 0 && flag[l][r] == -1)
			{
				flag[start_x][start_y] = dir;
				DFS(l, r, goal_x, goal_y, state);
			}
		}
	}
	flag[start_x][start_y] = -1;
}

int main() {
	game_state_t state;
	memset(&state, 0, sizeof(state));
	init(&state);
	// write your code here
	for (int i = 0; i < MAXSIZE; i++)
	{
		for (int j = 0; j < MAXSIZE; j++)
		{
			flag[i][j] = -1;
		}
	}
	//³õÊ¼»¯Õ»
	DFS(state.start_x, state.start_y, state.goal_x, state.goal_y, state);
	// 
	destroy(&state);
	return 0;
}
