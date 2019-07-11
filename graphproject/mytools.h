#ifndef _MYTOOLS_H_
#define _MYTOOLS_H_

//����һЩ����
#define MAXSIZE 1000
#define N 55

/*********************************************************************************/
/*********************************************************************************/
/******************************�ṹ�嶨����****************************************/
/*********************************************************************************/
/*********************************************************************************/

//ջ�ṹ�壬������������Ϊ EDGE* ���� ����ָ�롱����
typedef struct stack {
	int data[MAXSIZE];
	int top;
}STACK;

//�ڽӱ�ڵ�ṹ��
typedef struct node1 {
	int num;
	struct node *next;
	int weight;
}NODE;

//���нṹ�壬������������Ϊ EDGE* ���� ����ָ�롱����
typedef struct queue1 {
	int data[MAXSIZE];
	int front;
	int rear;
}QUEUE;

typedef struct queue2 {
	//int data[100];
	int *data;
	int l, r, cap;
} queue;

//��һ���ڽӱ�ڵ�ṹ��
typedef struct node2 { 
	int v, g, h;      
	queue path;       
} node;


typedef struct priority_queue {
	node *data;
	int size;
	int cap;
} priority_queue;

typedef struct {
	int data;
	int parent;
}QUERE;	//�ǻ��ζ�������

//ͼ�ṹ��
typedef struct {
	NODE *list[MAXSIZE];		//�ڽӱ��ͷ�������
	int n, e;	//ͼ�еĶ�����n�ͱ���e
}AdjGraph;

//�߽ṹ��
typedef struct edge1 {
	int start;
	int end;
	int weight;
}EDGE;

typedef struct edge2 { // �ߵĶ��� /*{{{*/
	int v, w, next;   // v:���� w:u->v  next:�¸����λ��
} edge;/*}}}*/


/*********************************************************************************/
/*********************************************************************************/
/******************************���ú���������***************************************/
/*********************************************************************************/
/*********************************************************************************/

//����start->end����ߵ�Ȩ��
int getWeight(int start, int end, NODE *list[]);

int  creatGraph(char name[], NODE *list[]);

void initList(NODE *list[]);

//ͬ��
void showPath(int path[]);

void drawPicture();

int pow1(int a, int x);

int transNumber(char s[]);

/*********************************************************************************/
/*********************************************************************************/
/******************************ջ����������****************************************/
/*********************************************************************************/
/*********************************************************************************/


//ջ��ʼ��������Ϊջָ��s���붯̬�ڴ棬ͬʱ�����бߵ���㡢�յ㡢Ȩ�س�ʼ��Ϊ-1
void initStack(STACK **s);

//�ж�ջ�յĺ�����ջ���򷵻�1�����򷵻�0
int is_emptyStack(STACK *s);

//�ж�ջ���ĺ�����ջ���򷵻�1�����򷵻�0
int is_fullStack(STACK *s);

//ѹջ����������EDGE*���͵�����ѹջ����������ֵΪ0�����ջ���򷵻�-1
int push(int n, STACK *s);

//��ջ��������ջ��Ԫ�رó�����ֵ��e����������ֵΪ0�����ջ���򷵻�-1
int pop(STACK *s);

//ȡջ��Ԫ�غ�������ջ��Ԫ�ص�ֵ����e�����ǲ���Ӱ��ջ��ָ�롣��������ֵΪ0�����ջ���򷵻�-1
int get(STACK *s);

//ջɾ���������ͷ�ջ��ռ�ڴ�����ָ��ſ�
void delStack(STACK *s);

/*********************************************************************************/
/*********************************************************************************/
/******************************���к���������***************************************/
/*********************************************************************************/
/*********************************************************************************/

edge e[N * N * 2], ex[N * N * 2];
int p[N], px[N], eid, exid;
int h[N], vis[N];

//���г�ʼ��������Ϊ����ָ��s���붯̬�ڴ棬ͬʱ�����бߵ���㡢�յ㡢Ȩ�س�ʼ��Ϊ-1
void initQueue(QUEUE *q);

//�ж϶ӿպ������ӿ��򷵻�1�����򷵻�0
int is_emptyQueue(QUEUE *q);

//�ж϶��������������򷵻�1�����򷵻�0
int is_fullQueue(QUEUE *q);

//��Ӻ���������EDGE*���͵��������β����������ֵΪ0����������򷵻�-1
int enqueue(int n, QUEUE *q);

//���Ӻ����� ����ͷԪ�س��Ӳ���ֵ��e.��������ֵΪ0������ӿ��򷵻�-1
int dequeue( QUEUE *q);

//����ɾ������,�ͷŶ�����ռ�ڴ�����ָ��ſ�
void delQueue(QUEUE *q);

void add(int u, int v, int w);

void edge_init(int n, int m, int des, char name[]);

int min1(int a, int b);

void queue_init(queue * q, int cap);

int queue_size(queue * q);

void queue_expand(queue * q);

void queue_push(queue * q, int val);

int queue_pop(queue * q);

int queue_cmp(queue * a, queue * b);

void queue_print(queue * q, int path[]);

void spfa(int s);

void pq_init(priority_queue * q, int cap);

void swap(struct node2 * x, struct node2 * y);

int pq_cmp(node a, node b);

void pq_expand(priority_queue * q);

void pq_push(priority_queue * q, node val);

node pq_pop(priority_queue * q);

int pq_size(priority_queue * q);

int ok(queue * q, int v);

void Astar(int src, int des, int k, int path[]);
#endif
