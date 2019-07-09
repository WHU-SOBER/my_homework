#include "util.h"
#include <stdio.h>
#include <string.h>
#define INF 0x3f3f3f3f


//define box struct
typedef struct {
	int x;
	int y;
	int parent;
	double g;
	double h;
}Box;

void swap(Box *a, Box *b) {
	Box temp = *a;
	*a = *b;
	*b = temp;
	return;
}

char judgef(int nx, int ny, int px, int py){
	if (px - nx == 1 && py == ny) {
		return 'N';
	} else if (px - nx == -1 && py == ny) {
		return 'S';
	} else if (px == nx && py - ny == 1) {
		return 'W';
	} else if (px == nx && py - ny == -1) {
		return 'E';
	} else {
		return '0';
	}
}

int d[5][2] = {{-1, 0},{0, 1},{1, 0},{0, -1}, {-1, -1}};

void astar(game_state_t mp) {
	//define vertices
	int n = mp.n;
	int m = mp.m;
	int **InOpl = (int **)malloc(n * sizeof(int *));
	Box *OpenList = (Box *)malloc(n * m * sizeof(Box));
	for(int i = 0; i < n; i++) {
		InOpl[i] = (int *)malloc(m * sizeof(int));
		for(int j = 0; j < m; j++) {
			InOpl[i][j] = 0;
		} 
	}

	//operations 
	int sonnodes = 0;
	Box temp;
	temp.x = mp.start_x;
	temp.y = mp.start_y;
	temp.parent = -1;
	temp.g = 0;
	temp.h = abs(temp.x - mp.goal_x) + abs(temp.y - mp.goal_y);
	int front = 0, rear = 0;
	InOpl[temp.x][temp.y] = 1;
	OpenList[rear] = temp;
	rear++;
	while(front != rear) {
		temp = OpenList[front];
		Box step;
		for (int i = 0; i < 4; i++) {
			int xi = temp.x + d[i][0];
			int yi = temp.y + d[i][1];
			step.x = xi;
			step.y = yi;
			step.parent = front;
			step.g = temp.g + mp.cost[temp.x][temp.y];
			step.h = abs(step.x - mp.goal_x) + abs(step.y - mp.goal_y);
			
			if(xi == mp.goal_x && yi == mp.goal_y) {
				char *path = (char *)malloc(n * m * sizeof(char));
				int j = 0;
				while(step.parent != -1) {
					Box parent = OpenList[step.parent];
					path[j] = judgef(step.x, step.y, parent.x, parent.y);
					j++;
					step = parent;
				}
				for(int k = j - 1; k >= 0 ; k--) {
					printf("%c", path[k]);
				}
				free(OpenList);
				for(int k = 0; k < n; k++) {
					free(InOpl[k]);
				}
				free(InOpl);
				return;
			} 	
			if (0 <= xi && xi < n && 0 <= yi && yi < m) {
				if(mp.grid[xi][yi] == 0 && InOpl[xi][yi] == 0) {
					InOpl[xi][yi] = 1;
					OpenList[rear] = step;
					rear++;
				} 
			}
		}
		double minf = INF;
		int minpos = -1;
		front++;
		for(int j = front; j < rear; j++) {
			if(OpenList[j].g + OpenList[j].h < minf) {
				minf = OpenList[j].g + OpenList[j].h;
				minpos = j;
			}
		}

		int ik = 0;
		for(int l = 0; l < 100; l++)
			ik+=l;
		swap(&OpenList[minpos], &OpenList[front]);


	}


}

int main() {
  game_state_t state;
  memset(&state, 0, sizeof(state));
  init(&state);
  // write your code here
  astar(state);
  // 
  destroy(&state);
  return 0;
}

