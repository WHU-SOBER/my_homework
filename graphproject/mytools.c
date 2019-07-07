#include<stdio.h>
#include<stdlib.h>
#include"mytools.h"
#include<string.h>

/*********************************************************************************/
/*********************************************************************************/
/******************************���ú���ʵ����***************************************/
/*********************************************************************************/
/*********************************************************************************/

//����start->end����ߵ�Ȩ��
int getWeight(int start, int end, NODE *list[])
{
	if (start == end)
		return 0;
	NODE* temp = list[start]->next;
	while (temp != NULL)
	{
		if (temp->num == end)
			return temp->weight;
		temp = temp->next;
	}
	return 0x3f3f3f3f;
}

//��name�ļ��л�ȡͼ�����洢��list�ڽӱ��У�ͬʱ����ͼ�ĵ���
int  creatGraph(char name[], NODE *list[])
{
	FILE *fp = fopen(name, "r");
	if (fp == NULL)
	{
		printf("File open error!\n");
		exit(0);
	}
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
	return n;
}

void initList(NODE *list[])
{
	for (int i = 0; i < MAXSIZE; i++)
	{
		list[i] = (NODE*)malloc(sizeof(NODE));
		list[i]->next = NULL;
	}
}

void drawPicture()
{
	printf("                ----------					\n");
	printf("               /          \\			         \n");
	printf("              |   $    $   |                \n");
	printf("              |            |                \n");
	printf("               \\    --   /                 \n");
	printf("                ----------                  \n");
	printf("                     |                      \n");
	printf("           O------------------O             \n");
	printf("                     |                      \n");
	printf("                     |                      \n");
	printf("               -------------                 \n");
	printf("               |           |                 \n");
	printf("               |           |                 \n");
	printf("               #           #                 \n");
	printf("                                              \n");
	printf("               ����ͷ����ͷ��                  \n");
}

//ͬ��
void showPath(int path[])
{
	for (int i = 0; path[i] >= 0; i++)
	{
		printf("%d", path[i]);
		if (path[i + 1] >= 0)
			printf("->");
	}
	printf("\n");
}

int pow1(int a, int x)
{
	int rem = a;
	for(int i = 0; i < x; i++)
	{
		a *= rem;
	}
	return a;
}

int transNumber(char s[])
{
	int num = strlen(s);
	int result = 0;
	for(int i = 0; i < num; i++)
	{
		result += pow1(10, (num - i - 1)) * (s[i] - '0');
	}
	return result / 10;
}

/*********************************************************************************/
/*********************************************************************************/
/******************************ջ����ʵ����****************************************/
/*********************************************************************************/
/*********************************************************************************/


//ջ��ʼ��������Ϊջָ��s���붯̬�ڴ棬ͬʱ�����бߵ���㡢�յ㡢Ȩ�س�ʼ��Ϊ-1
void initStack(STACK **s)
{
	*s = (STACK*)malloc(sizeof(STACK));
	(*s)->top = -1;
	for (int i = 0; i < MAXSIZE; i++)
	{
		(*s)->data[i] = -1;
	}
}

//�ж�ջ�յĺ�����ջ���򷵻�1�����򷵻�0
int is_emptyStack(STACK *s)
{
	if (s->top == -1)
		return 1;
	else
		return 0;
}

//�ж�ջ���ĺ�����ջ���򷵻�1�����򷵻�0
int is_fullStack(STACK *s)
{
	if (s->top == MAXSIZE - 1)
		return 1;
	else
		return 0;
}

//ѹջ����������EDGE*���͵�����ѹջ����������ֵΪ0�����ջ���򷵻�-1
int push(int n, STACK *s)
{
	if (s->top == MAXSIZE - 1)
		return -1;
	s->top++;
	s->data[s->top] = n;
	return 0;
}

//��ջ��������ջ��Ԫ�رó�����������ֵΪ0�����ջ���򷵻�-1
int pop(STACK *s)
{
	if (s->top == -1)
		return -1;
	s->data[s->top] = -1;
	s->top--;
	return s->data[s->top + 1];
}

//ȡջ��Ԫ�غ��������ǲ���Ӱ��ջ��ָ�롣��������ֵΪ0�����ջ���򷵻�-1
int get(STACK *s)
{
	if (s->top == -1)
		return -1;
	return s->data[s->top];
}

//ջɾ���������ͷ�ջ��ռ�ڴ�����ָ��ſ�
void delStack(STACK *s)
{
	free(s);
	s = NULL;
}

/*********************************************************************************/
/*********************************************************************************/
/******************************���к���ʵ����***************************************/
/*********************************************************************************/
/*********************************************************************************/

//���г�ʼ��������Ϊ����ָ��s���붯̬�ڴ棬ͬʱ�����бߵ���㡢�յ㡢Ȩ�س�ʼ��Ϊ-1
void initQueue(QUEUE *q)
{
	q = (QUEUE*)malloc(sizeof(QUEUE));
	q->front = 0;
	q->rear = 0;
}

//�ж϶ӿպ������ӿ��򷵻�1�����򷵻�0
int is_emptyQueue(QUEUE *q)
{
	if (q->front == q->rear)
		return 1;
	else
		return 0;
};

//�ж϶��������������򷵻�1�����򷵻�0
int is_fullQueue(QUEUE *q)
{
	if (q->front == (q->rear + 1) % MAXSIZE)    //�ƶ�ѭ�������Ƿ�������һ��Ԥ���ռ䲻��
		return 1;
	else
		return 0;
}

//��Ӻ���������int���͵��������β����������ֵΪ0����������򷵻�-1
int enqueue(int n, QUEUE *q)
{
	if (is_fullQueue(q))
		return -1;
	q->data[q->rear] = n;
	q->rear = (q->rear + 1) % MAXSIZE;
	return 0;
}

//���Ӻ����� ����ͷԪ�س��Ӳ�����.��������ֵΪ0������ӿ��򷵻�-1
int dequeue(QUEUE *q)
{
	if (is_emptyQueue(q))
		return -1;
	int result = q->data[q->front];
	q->front = (q->front + 1) % MAXSIZE;
	return result;
}

//����ɾ������,�ͷŶ�����ռ�ڴ�����ָ��ſ�
void delQueue(QUEUE *q)
{
	free(q);
	q = NULL;
}

void add(int u, int v, int w) {
	e[eid].v = v;
	e[eid].w = w;
	e[eid].next = p[u];
	p[u] = eid++;

	ex[exid].v = u;
	ex[exid].w = w;
	ex[exid].next = px[v];
	px[v] = exid++;
}

void edge_init(int n, int m, int des, char name[]) {
	eid = 0;
	exid = 0;
	memset(p, -1, sizeof p);
	memset(px, -1, sizeof p);
	FILE *fp = fopen(name, "r");
	while (m--) {
		int u, v, w;
		fscanf(fp, "%d%d%d", &u, &v, &w);
		add(u, v, w);
	}
	fclose(fp);
}

int min1(int a, int b) {
	return a < b ? a : b;
}

void queue_init(queue *q, int cap) {
	q->data = (int*)malloc(sizeof(int) * cap);
	q->cap = cap;
	q->l = 0;
	q->r = -1;
}

int queue_size(queue *q) {
	return q->r - q->l + 1;
}

void queue_expand(queue *q) {/*{{{*/
	q->cap *= 2;
	int *data = (int*)malloc(sizeof(int) * q->cap);
	for (int i = 0; i < q->r - q->l + 1; i++) {
		data[i] = q->data[i + q->l];
	}
	q->data = data;
	q->r = q->r - q->l;
	q->l = 0;
}

void queue_push(queue *q, int val) {
	if (q->r >= q->cap) {
		queue_expand(q);
	}
	q->data[++q->r] = val;
}

int queue_pop(queue *q) {
	if (queue_size(q) <= 0) {
		printf("queue_pop\n");
		exit(0);
	}
	return q->data[q->l++];
}
int queue_cmp(queue* a, queue* b) {
	int n = min1(queue_size(a), queue_size(b));
	for (int i = 0; i < n; i++) {
		if (a->data[a->l + i] != b->data[b->l + i]) {
			return a->data[a->l + i] < b->data[b->l + i];
		}
	}
	return queue_size(a) < queue_size(b);
}

void queue_print(queue* q, int path[]) {
	int i, j;
	for (i = q->l, j = 0; i < q->r; i++, j++) {
		path[j] = q->data[i];
	}
	path[j] = q->data[q->r];
}

void spfa(int s) {
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
		for (int i = px[u]; ~i; i = ex[i].next) {
			int v = ex[i].v;
			if (h[v] > h[u] + ex[i].w) {
				h[v] = h[u] + ex[i].w;
				if (!vis[v]) {
					vis[v] = 1;
					queue_push(&q, v);
				}
			}
		}
	}
}

void pq_init(priority_queue* q, int cap) {
	q->size = 0;
	q->cap = cap;
	q->data = (node*)malloc(sizeof(node) * cap);
}

void swap(struct node2 *x, struct node2 *y) {
	struct node2 tmp = *x;
	*x = *y;
	*y = tmp;
}

int pq_cmp(node a, node b) {
	if (a.g + a.h != b.g + b.h) {
		return a.g + a.h < b.g + b.h;
	}
	return queue_cmp(&a.path, &b.path);
}

void pq_expand(priority_queue *q) {
	q->cap *= 2;
	node *data = (node*)malloc(sizeof(node) * q->cap);
	for (int i = 0; i <= q->size; i++) {
		data[i] = q->data[i];
	}
	q->data = data;
}

void pq_push(priority_queue *q, node val) {
	if (q->size * 2 >= q->cap) {
		pq_expand(q);
	}
	int p = ++q->size;
	q->data[p] = val;
	while (p > 1 && pq_cmp(q->data[p], q->data[p / 2])) {
		swap(&q->data[p / 2], &q->data[p]);
		p /= 2;
	}
};

node pq_pop(priority_queue *q) {
	if (q->size <= 0) {
		puts("pq_pop");
		exit(0);
	}
	node res = q->data[1];
	q->data[1] = q->data[q->size--];
	int p = 1, t;
	while (p * 2 <= q->size) {
		if (p * 2 + 1 > q->size || pq_cmp(q->data[p * 2], q->data[p * 2 + 1])) {
			t = p * 2;
		}
		else {
			t = p * 2 + 1;
		}
		if (pq_cmp(q->data[t], q->data[p])) {
			swap(&q->data[p], &q->data[t]);
			p = t;
		}
		else {
			break;
		}
	}
	return res;
};

int pq_size(priority_queue *q) {
	return q->size;
}

int ok(queue *q, int v) {
	for (int i = q->l; i <= q->r; i++) {
		if (q->data[i] == v) {
			return 1;
		}
	}
	return 0;
}

void Astar(int src, int des, int k, int path[]) {
	queue q;
	queue_init(&q, N);
	queue_push(&q, src);
	priority_queue pq;
	node tmp = { src, 0, h[src], q };
	pq_init(&pq, N);
	pq_push(&pq, tmp);

	int cnt = 0;
	while (pq_size(&pq)) {
		tmp = pq_pop(&pq);
		if (tmp.v == des) {
			cnt++;
			if (cnt == k) {
				queue_print(&tmp.path, path);
				return;
			}
			continue;
		}
		for (int i = p[tmp.v]; ~i; i = e[i].next) {
			if (ok(&tmp.path, e[i].v)) {
				continue;
			}
			node to;
			queue_init(&to.path, tmp.path.cap);
			to.v = e[i].v;
			to.g = tmp.g + e[i].w;
			to.h = h[e[i].v];
			for (int i = 0; i < tmp.path.cap; i++) {
				to.path.data[i] = tmp.path.data[i];
			}
			to.path.l = tmp.path.l;
			to.path.r = tmp.path.r;
			queue_push(&to.path, e[i].v);
			pq_push(&pq, to);
		}
	}
}
