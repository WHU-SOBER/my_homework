#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include"util.h"
#include"mytools.h"
#include"stats.h"
#include"search.h"
//将迷宫转化为有向图邻接表
int dx[] = { -1,0,1,0 };
int dy[] = { 0,1,0,-1 };
void  creatGraph1(game_state_t *state, NODE *list[])
{
	NODE *p, *new1;
	int x, y;
	for (int i = 1; i < state->n - 1; i++) {
		for (int j = 1; j < state->m - 1; j++) {
			if (state->grid[i][j] == 0)
			{
				for (int k = 0; k < 4; k++) {
					x = i + dx[k];
					y = j + dy[k];
					if (state->grid[x][y] == 0) {
						p = list[i*state->m + j];
						new1 = (NODE*)malloc(sizeof(NODE));
						new1->num = x * state->m + y;	//该点的编号
						new1->weight = state->cost[x][y];
						new1->next = p->next;
						p->next = new1;
					}
				}
			}
		}
	}
}
//将有向图路径path转化为坐标路径并返回（需要使用point*变量接收）
char* transPath(int path[], game_state_t s)
{
	int num = 0;
	for (int i = 0; i < MAXSIZE; i++)
	{
		if (path[i] < 0)
		{
			num = i;
			break;
		}
	}
	int point[MAXSIZE][2];
	for (int i = 0; i < num; i++)
	{
		point[i][0] = path[i] / s.m;
		point[i][1] = path[i] % s.n;
	}
	char *re = (char*)malloc(sizeof(char));
	int i = 0;
	while (i != num)
	{
		if (point[i + 1][0] == point[i][0])
		{
			if (point[i + 1][1] - point[i][1] == 1)
				re[i] = 'E';
			else
				re[i] = 'W';
		}
		else
		{
			if (point[i + 1][0] - point[i][0] == 1)
				re[i] = 'S';
			else
				re[i] = 'N';
		}
	}
	return re;
}

void fileName(NODE *list[])
{
	FILE *fp = fopen("tempf.txt", "a");
	for (int i = 0; list[i]->num >= 0; i++)
	{
		NODE *temp = list[i]->next;
		while (temp != NULL)
		{
			fprintf(fp, "%d %d %lf\n", list[i]->num, temp->num, temp->weight);
		}
	}
	fclose(fp);
}

int main() {
	game_state_t state;
	init(&state);
	/*创建并初始化邻接表*/
	NODE *list[MAXSIZE];
	for (int i = 0; i < state.m * state.n; i++) {
		list[i] = (NODE*)malloc(sizeof(NODE));
		list[i]->num = i;
		list[i]->weight = state.cost[i / state.m][i % state.n];
		list[i]->next = NULL;
	}
	creatGraph1(&state, list);
	int path[MAXSIZE];
	for (int i = 0; i < MAXSIZE; i++)
	{
		path[i] = -1;
	}
	fileName(list);
	char name[15] = "tempf.txt";
	A(state.start_x, state.start_y, name, path);
	char *answer;
	answer = transPath(path, state);
	return 0;
}