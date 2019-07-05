#include<stdio.h>
#include<stdlib.h>
#include"mytools.h"
#include"stats.h"
#include"search.h"

//��name�ļ��л�ȡͼ�����洢��list�ڽӱ��У�ͬʱ����ͼ�ĵ���
int  creatGraph(char name[], NODE *list[])
{
	FILE *fp = fopen(name, "r");
	int start, end, weight;
	NODE *temp = NULL;
	int n = 0;
	while (fscanf(fp, "%d%d%d", &start, &end, &weight) != EOF)
	{
		if (list[start]->next == NULL)
			n++;
		temp = (NODE*)malloc(sizeof(NODE));
		temp->num = end;
		temp->weight = weight;
		temp->next = list[start]->next;
		list[start]->next = temp;
	}
	fclose(fp);
}

void initList(NODE *list[])
{
	for (int i = 0; i < MAXSIZE; i++)
	{
		list[i] = (NODE*)malloc(sizeof(NODE));
		list[i]->next = NULL;
	}
}

//��ջ�е����ߵ�Ȩ�غ�
int sumStack(STACK *s, NODE *list[])
{
	int sum = 0;
	for (int i = 0; i < s->top; i++)
	{
		sum += getWeight(s->data[i], s->data[i + 1], list);
	}
	return sum;
}

//��ջ�����е�д��path����
void wtritePath(STACK *s, int path[])
{
	int i;
	for (i = 0; i <= s->top; i++)
	{
		path[i] = s->data[i];
	}
	path[i] = -1;
}


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

void DFS(int u, int v, char name[], int path[])
{
	//��ʼ���ڽӱ�
	NODE *list[MAXSIZE];
	initList(list);
	//��ͼ�����ڽӱ�
	int n = creatGraph(name, list);
	//��ʼ��ջ�������ݴ�·��
	STACK *s = NULL;
	initStack(&s);
	//��־����flag���ڼ�¼�õ����ޱ�̽����
	for (int i = 0; i < MAXSIZE; i++)
	{
		private_flag[i] = 0;
	}
	int min = 0x3f3f3f3f;
	funcDFS(u, v, list, path, s);
	printf("cost: %d\n", private_minWeight);
}

void BFS(int u, int v, char name[], int path[])
{

}

void Dijkstra(int u, int v, char name[], int path[]);

void SPFA(int u, int v, char name[], int path[]);

void A(int u, int v, char name[], int path[]);

int* shortestPath(int u, int v, char algorithm[])
{
	
}
