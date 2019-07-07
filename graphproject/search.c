#include<stdio.h>
#include<stdlib.h>
#include"mytools.h"
#include"stats.h"
#include"search.h"

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

//属于funcDFS的私有全局变量
int private_minWeight = 0x3f3f3f3f;
int private_flag[MAXSIZE];
//DFS功能递归函数
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

void funcBFS(int u, int v, AdjGraph *G, char name[], int *path)
{
	int w, i;
	NODE *p;
	QUERE qu[10000];
	int front = -1;
	int rear = -1;
	int k = 0;
	int visited[10000];
	for (int i = 0; i < 100; i++) {
		visited[i] = 0;
	}
	rear++;
	qu[rear].data = u;
	qu[rear].parent = -1;
	visited[u] = 1;
	while (front != rear) {
		front++;
		w = qu[front].data;
		if (w == v) {
			i = front;
			while (qu[i].parent != -1) {
				path[k++] = qu[i].data;
				i = qu[i].parent;
			}
			if (qu[i].parent == -1)
				path[k] = qu[i].data;
			return;
		}
		p = G->list[w]->next;
		while (p != NULL) {
			if (visited[p->num] == 0) {
				visited[p->num] = 1;
				rear++;
				qu[rear].data = p->num;
				qu[rear].parent = front;
			}
			p = p->next;
		}
	}
}

void BFS(int u, int v, char name[], int path[])
{
	AdjGraph *G;
	NODE *lists[MAXSIZE];
	G = (AdjGraph *)malloc(sizeof(AdjGraph));
	initList(lists);
	creatGraph(name, lists);
	for (int i = 0; i < MAXSIZE; i++)
	{
		G->list[i] = lists[i];
	}
	int temp = u;
	u = v;
	v = temp;
	funcBFS(u, v, G, name, path);
}

int Dijkstra(int u, int v, char name[], int p[])
{
	if (u == v)
	{
		p[0] = -1;
		return;
	}
	//初始化邻接表
	NODE *list[MAXSIZE];
	initList(list);
	//把图存入邻接表
	int n = creatGraph(name, list);
	int dist[MAXSIZE];
	int path[MAXSIZE];
	int s[MAXSIZE];
	int mindis = 0x3f3f3f3f, i, j, temp = -1;
	for (i = 0; i < n; i++)
	{
		dist[i] = getWeight(u, i, list);
		s[i] = 0;
		if (getWeight(u, i, list) < 0x3f3f3f3f)
			path[i] = u;
		else
			path[i] = -1;
	}
	s[u] = 1;
	for (i = 0; i < n; i++)
	{
		mindis = 0x3f3f3f3f;
		for (j = 0; j < n; j++)
			if (s[j] == 0 && dist[j] < mindis)
			{
				temp = j;
				mindis = dist[j];
			}
		if (temp < 0)
		{
			p[0] = -1;
			return;
		}
		s[temp] = 1;
		for (j = 0; j < n; j++)
			if (s[j] == 0)
				if (getWeight(temp, j, list) < 0x3f3f3f3f && dist[temp] + getWeight(temp, j, list) < dist[j])
				{
					dist[j] = dist[temp] + getWeight(temp, j, list);
					path[j] = temp;
				}
	}
	i = 1;
	int now = v;
	p[0] = v;
	while (path[now] != u)
	{
		p[i] = path[now];
		now = path[now];
		if (now < 0)
		{
			p[0] = -1;
			return;
		}
		i++;
	}
	p[i] = u;
	int *t = (int*)malloc((i + 1) * sizeof(int));
	for (int j = 0; j <= i; j++)
	{
		t[j] = p[i - j];
	}
	for (int j = 0; j <= i; j++)
	{
		p[j] = t[j];
	}
	free(t);
	t = NULL;
	p[i + 1] = -1;
	int sumweight = 0;
	for (int x = 0; x < i; x++)
	{
		sumweight += getWeight(p[x], p[x + 1], list);
	}
	return sumweight;
}

void SPFA(int u1, int v1, char name[], int path[])
{
	if (u1 == v1)
	{
		path[0] = -1;
		return;
	}
	int n, m, s;
	n = numberOfVertices(name);
	m = numberOfEdges(name);
	s = u1;
	edge_init(n, m, s, name);
	int temp_p[MAXSIZE];
	for (int i = 0; i < MAXSIZE; i++)
	{
		temp_p[i] = -1;
	}
	memset(h, 0x3f, sizeof h);
	h[s] = 0;
	memset(vis, 0, sizeof vis);
	vis[s] = 1;
	queue q;
	queue_init(&q, N);
	queue_push(&q, s);
	while (queue_size(&q)) {
		int u = queue_pop(&q);
		vis[u] = 0;
		for (int i = p[u]; ~i; i = e[i].next) {
			int v = e[i].v;
			if (h[v] > h[u] + e[i].w) {
				h[v] = h[u] + e[i].w;
				if (!vis[v]) {
					vis[v] = 1;
					queue_push(&q, v);
				}
				temp_p[v] = u;
			}
		}
	}
	int i = 1;
	int now = v1;
	path[0] = v1;
	while (temp_p[now] != u1)
	{
		if (now < 0)
		{
			path[0] = -1;
			return;
		}
		path[i] = temp_p[now];
		now = temp_p[now];
		if (now < 0)
		{
			path[0] = -1;
			return;
		}
		i++;
	}
	path[i] = u1;
	int *t = (int*)malloc((i + 1) * sizeof(int));
	for (int j = 0; j <= i; j++)
	{
		t[j] = path[i - j];
	}
	for (int j = 0; j <= i; j++)
	{
		path[j] = t[j];
	}
	free(t);
	t = NULL;
}

void A(int u, int v, char name[], int path[])
{
	if (u == v)
	{
		path[0] = -1;
		return;
	}
	int n, m, src, des;
	n = numberOfVertices(name);
	m = numberOfEdges(name);
	src = u;
	des = v;
	edge_init(n, m, des, name);
	spfa(des);
	Astar(src, des, 1, path);
	return 0;
}

int* shortestPath(int u, int v, char algorithm[], char name[])
{
	//初始化数组p
	int *p = (int*)malloc(MAXSIZE*sizeof(int));
	for (int i = 0; i < MAXSIZE; i++)
	{
		p[i] = -1;
	}
	if (strcmp(algorithm, "DFS") == 0)
		DFS(u, v, name, p);
	else if (strcmp(algorithm, "BFS") == 0)
		BFS(u, v, name, p);
	else if (strcmp(algorithm, "Dijkstra") == 0)
		Dijkstra(u, v, name, p);
	else if (strcmp(algorithm, "SPFA") == 0)
		SPFA(u, v, name, p);
	else if (strcmp(algorithm, "Astar") == 0)
		A(u, v, name, p);
	return p;
}
