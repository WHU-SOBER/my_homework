#include "util.h"
#include <stdio.h>
#include <string.h>
#define MAXSIZE 1000
char result[MAXSIZE];
int flag[MAXSIZE][MAXSIZE];
//栈结构体定义
typedef struct stack {
	int data[MAXSIZE];
	int top;
}STACK;

//求栈中点连线的权重和
int sumStack(STACK *s, NODE *list[])
{
	int sum = 0;
	for (int i = 0; i < s->top; i++)
	{
		sum += getWeight(s->data[i], s->data[i + 1], list);
	}
	return sum;
}

//将栈中所有点写入path数组
void wtritePath(STACK *s, int path[])
{
	int i;
	for (i = 0; i <= s->top; i++)
	{
		path[i] = s->data[i];
	}
	path[i] = -1;
}

//属于DFS的私有全局变量
int private_minWeight = 0x3f3f3f3f;
int private_flag[MAXSIZE];
void funcDFS(int u, int v, NODE* list[], int path[], STACK *s)
{
	push(u, s);
	private_flag[u] = 1;
	if (u == v)
	{
		if (private_minWeight > sumStack(s, list))
		{
			wtritePath(s, path);
			private_minWeight = sumStack(s, list);
		}
	}
	else
	{
		NODE *temp = list[u]->next;
		while (temp != NULL)
		{
			if (private_flag[temp->num] == 0)
			{
				funcDFS(temp->num, v, list, path, s);
			}
			temp = temp->next;
		}
	}
	pop(s);
	private_flag[u] = 0;
}
/*
int DFS(int u, int v, char name[], int path[])
{
	if (u == v)
	{
		path[0] = -1;
		return;
	}
	//初始化邻接表
	NODE *list[MAXSIZE];
	initList(list);
	//把图存入邻接表
	int n = creatGraph(name, list);
	//初始化栈，用于暂存路径
	STACK *s = NULL;
	initStack(&s);
	//标志数组flag用于记录该点有无被探索过
	for (int i = 0; i < MAXSIZE; i++)
	{
		private_flag[i] = 0;
	}
	int min = 0x3f3f3f3f;
	funcDFS(u, v, list, path, s);
	//printf("cost: %d\n", private_minWeight);
	return private_minWeight;
}
*/
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
		printf("%s", result);
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
	DFS(state.start_x, state.start_y, state.goal_x, state.goal_y, state);
	// 
	destroy(&state);
	return 0;
}
