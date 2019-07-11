#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define N 10000

int cnt = 0;
int x[N], y[N];
int ans[N];

int bfs(int s_x, int s_y, int e_x, int e_y, game_state_t state)
{
	int dx[] = { -1, 0, 1, 0 };
	int dy[] = { 0, 1, 0, -1 };
	int pre[100][100];
	int mp[100][100];
	for (int i = 0; i < state.n; i++)
	{
		for (int j = 0; j < state.m; j++)
		{
			mp[i][j] = state.grid[i][j];
		}
	}
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			pre[i][j] = -1;
		}
	}
	int queue[10240][2];
	int rear = 0, front = -1;
	front++;
	queue[front][0] = s_x;
	queue[front][1] = s_y;
	while (rear <= front)
	{
		int x = queue[rear][0];
		int y = queue[rear][1];
		rear++;
		if (x == e_x && y == e_y)
		{
			break;
		}
		for (int i = 0; i < 4; i++)
		{
			if (mp[x + dx[i]][y + dy[i]] == 0)
			{
				front++;
				queue[front][0] = x + dx[i];
				queue[front][1] = y + dy[i];
				pre[x + dx[i]][y + dy[i]] = i;
				mp[x + dx[i]][y + dy[i]] = -1;
			}
		}
	}
	int result = 0;
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			if (pre[i][j] >= 0)
				result++;
		}
	}
	return result;
}

void greedy(game_state_t state)
{
	int min = 0x3f3f3f3f;
	int now = 0;
	int n_x = state.start_x, n_y = state.start_y;
	int rem;
	int flag[N] = { 0 };
	for (int j = 0; j < cnt; j++)
	{
		for (int i = 0; i < cnt; i++)
		{
			if (flag[i] == 1)
				continue;
			now = bfs(n_x, n_y, x[i], y[i], state);
			if (now < min)
			{
				rem = i;
				min = now;
			}
		}
		n_x = x[rem];
		n_y = y[rem];
		flag[rem] = 1;
		ans[j] = rem;
		min = 0x3f3f3f3f;
	}
}

char* bfsShowPath(game_state_t state, int s_x, int s_y, int e_x, int e_y)
{
	int dx[] = { -1, 0, 1, 0 };
	int dy[] = { 0, 1, 0, -1 };
	int pre[100][100];
	int mp[100][100];
	for (int i = 0; i < state.n; i++)
	{
		for (int j = 0; j < state.m; j++)
		{
			mp[i][j] = state.grid[i][j];
		}
	}
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			pre[i][j] = -1;
		}
	}
	int queue[10240][2];
	int rear = 0, front = -1;
	front++;
	queue[front][0] = s_x;
	queue[front][1] = s_y;
	while (rear <= front)
	{
		int x = queue[rear][0];
		int y = queue[rear][1];
		rear++;
		if (x == e_x && y == e_y)
		{
			break;
		}
		for (int i = 0; i < 4; i++)
		{
			if (mp[x + dx[i]][y + dy[i]] == 0)
			{
				front++;
				queue[front][0] = x + dx[i];
				queue[front][1] = y + dy[i];
				pre[x + dx[i]][y + dy[i]] = i;
				mp[x + dx[i]][y + dy[i]] = -1;
			}
		}
	}

	int path[N];
	char *temp = (char *)malloc(sizeof(char) * N);
	int x = e_x, y = e_y, i = 0;
	while (x != s_x || y != s_y) {
		switch (pre[x][y]) {
		case 0:x++; path[i] = 0; break;
		case 1:y--; path[i] = 1; break;
		case 2:x--; path[i] = 2; break;
		case 3:y++; path[i] = 3; break;
		}
		i++;
	}

	int j = 0;
	for (i = i - 1; i >= 0; i--) {
		switch (path[i]) {
		case 0:temp[j] = 'N'; break;
		case 1:temp[j] = 'E'; break;
		case 2:temp[j] = 'S'; break;
		case 3:temp[j] = 'W'; break;
		}
		j++;
	}
	temp[j] = '\0';
	return temp;
}

int sumAns(int path[], game_state_t state)
{
	int sum = bfs(state.start_x, state.start_y, x[path[0]], y[path[0]], state);
	for (int i = 1; i < cnt; i++)
	{
		sum += bfs(x[path[i - 1]], y[path[i - 1]], x[path[i]], y[path[i]], state);
	}
	return sum;
}

double func(int s, int s_new, double T)
{
	return exp((s - s_new) / T);
}

int main() {
	game_state_t state;
	memset(&state, 0, sizeof(state));
	init(&state);
	// write your code here
	//初始化
	for (int i = 0; i < state.n; i++) {
		for (int j = 0; j < state.m; j++) {
			if (state.food[i][j]) {
				x[cnt] = i;
				y[cnt] = j;
				//ans[cnt] = cnt;
				cnt++;
			}
		}
	}
	greedy(state);
	//开始2-opt
	srand((unsigned)time(NULL));
	int n = 0;
	int m;
	int tempAns[N];
	int seed = 0;
	int k = 0;
	int k_max = 1000;
	double T;
	while (k < k_max)
	{
		T = k_max / (k + 1);
		k++;
		seed++;
		srand((unsigned)(time(NULL) + seed));
		while (n == 0)
		{
			n = rand() % cnt;
		}
		m = rand() % n;
		for (int i = 0; i < m; i++)
		{
			tempAns[i] = ans[i];
		}
		for (int i = m, j = n; i <= n; i++, j--)
		{
			tempAns[i] = ans[j];
		}
		for (int i = n + 1; i < cnt; i++)
		{
			tempAns[i] = ans[i];
		}
		if (func(sumAns(ans, state), sumAns(tempAns, state), T) >= rand()*1.0 / RAND_MAX)
		{
			for (int i = 0; i < cnt; i++)
			{
				ans[i] = tempAns[i];
			}
		}
	}
	char * re = bfsShowPath(state, state.start_x, state.start_y, x[ans[0]], y[ans[0]]);
	printf("%s", re);
	free(re);
	for (int i = 1; i < cnt; i++)
	{
		re = bfsShowPath(state, x[ans[i - 1]], y[ans[i - 1]], x[ans[i]], y[ans[i]]);
		printf("%s", re);
		free(re);
	}
	// 
	destroy(&state);
	return 0;
}
