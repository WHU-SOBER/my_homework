#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 1000
typedef struct point {
	int l, r;
}point;
typedef struct queue {
	point *data[MAXSIZE];
	int front, rear;
}queue;

int is_emptyQueue(queue *q)
{
	if (q->front == q->rear)
		return 1;
	else
		return 0;
};

//�ж϶��������������򷵻�1�����򷵻�0
int is_fullQueue(queue *q)
{
	if (q->front == (q->rear + 1) % MAXSIZE)    //�ƶ�ѭ�������Ƿ�������һ��Ԥ���ռ䲻��
		return 1;
	else
		return 0;
}

//��Ӻ���������int���͵��������β����������ֵΪ0����������򷵻�-1
int enqueue(point p, queue *q)
{
	if (is_fullQueue(q))
		return -1;
	*(q->data[q->rear]) = p;
	q->rear = (q->rear + 1) % MAXSIZE;
	return 0;
}

//���Ӻ����� ����ͷԪ�س��Ӳ�����.��������ֵΪ0������ӿ��򷵻�-1
point dequeue(queue *q)
{
	/*if (is_emptyQueue(q))
		return -1;*/
	point result = *(q->data[q->front]);
	q->front = (q->front + 1) % MAXSIZE;
	return result;
}


char result[MAXSIZE];
int flag[MAXSIZE][MAXSIZE];

int main() {
	game_state_t state;
	memset(&state, 0, sizeof(state));
	init(&state);
	// write your code here
	//���г�ʼ��
	for(int i = 0; i < MAXSIZE; i++)
	{
		for(int j = 0; j < MAXSIZE; j++)
		{
			flag[i][j] = -1;
		}
	}
	queue *q = (queue*)malloc(sizeof(queue));
	for (int i = 0; i < MAXSIZE; i++)
	{
		q->data[i] = (point*)malloc(sizeof(point));
	}
	q->front = 0;
	q->rear = 0;
	point p = { state.start_x, state.start_y };
	enqueue(p, q);
	while (!is_emptyQueue)
	{
		p = dequeue(q);
		if (p.l == state.goal_x && p.r == state.goal_y)
		{
			int i = -1;
			int x = state.start_x;
			int y = state.start_y;
			while (!(x == state.goal_x && y == state.goal_y))
			{
				i++;
				switch (flag[x][y])
				{
				case 0:result[i] = 'N'; x--; break;
				case 1:result[i] = 'E'; y++; break;
				case 2:result[i] = 'S'; x++; break;
				case 3:result[i] = 'W'; y--; break;
				}
			}
			i++;
			result[i] = '\0';
			printf("%s\n", result);
			destroy(&state);
			return 0;
		}
		int dir = -1;
		while (dir < 3)
		{
			dir++;
			int l = p.l;
			int r = p.r;
			switch (dir) {
			case 0:l--; break;
			case 1:r++; break;
			case 2:l++; break;
			case 3:r--; break;
			}
			if (flag[l][r] == -1)
			{
				flag[p.l][p.r] = dir;
				point temp = {l, r};
				enqueue(temp, q);
			}
		}
	}
	// 
	return 0;
}
