#include "util.h"
#include <stdio.h>
#include <string.h>
#define N 10000

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

int x[10000], y[10000];
int cnt = 0;
int ans[N], res = 0x3f3f3f3f;
int vis[N] = { 0 };
int src_x, src_y;
void dfs(int now, int path[], game_state_t state) {
	if (now == cnt) {
		int sum = bfs(src_x, src_y, x[path[0]], y[path[0]], state);
		for (int i = 1; i < cnt; i++) {
			sum += bfs(x[path[i - 1]], y[path[i - 1]], x[path[i]], y[path[i]], state);
			if (sum > res) return;// bfs ¼ÆËã×î¶ÌÂ·
		}
		if (sum < res) {
			for (int i = 0; i < cnt; i++) {
				ans[i] = path[i];
			}
			res = sum;
		}
		return;
	}
	for (int i = 0; i < cnt; i++) {
		if (!vis[i]) {
			vis[i] = 1;
			path[now] = i;
			dfs(now + 1, path, state);
			vis[i] = 0;
		}
	}
	//vis[now] = 0;
}

int main() {
	game_state_t state;
	memset(&state, 0, sizeof(state));
	init(&state);
	// write your code here
	for (int i = 0; i < state.n; i++) {
		for (int j = 0; j < state.m; j++) {
			if (state.food[i][j]) {
				x[cnt] = i;
				y[cnt++] = j;
			}
		}
	}
	int path[N];
	src_x = state.start_x;
	src_y = state.start_y;
	dfs(0, path, state);
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
