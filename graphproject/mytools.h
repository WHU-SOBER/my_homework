#ifndef _MYTOOLS_H_
#define _MYTOOLS_H_

//定义一些常量
#define MAXSIZE 1000
#define N 55

/*********************************************************************************/
/*********************************************************************************/
/******************************结构体定义区****************************************/
/*********************************************************************************/
/*********************************************************************************/

//栈结构体，其中数据类型为 EDGE* ，即 “边指针”类型
typedef struct stack {
	int data[MAXSIZE];
	int top;
}STACK;

//邻接表节点结构体
typedef struct node1 {
	int num;
	struct node *next;
	int weight;
}NODE;

//队列结构体，其中数据类型为 EDGE* ，即 “边指针”类型
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

//另一个邻接表节点结构体
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
}QUERE;	//非环形队列类型

//图结构体
typedef struct {
	NODE *list[MAXSIZE];		//邻接表的头结点数组
	int n, e;	//图中的顶点数n和边数e
}AdjGraph;

//边结构体
typedef struct edge1 {
	int start;
	int end;
	int weight;
}EDGE;

typedef struct edge2 { // 边的定义 /*{{{*/
	int v, w, next;   // v:顶点 w:u->v  next:下个点的位置
} edge;/*}}}*/


/*********************************************************************************/
/*********************************************************************************/
/******************************常用函数定义区***************************************/
/*********************************************************************************/
/*********************************************************************************/

//返回start->end有向边的权重
int getWeight(int start, int end, NODE *list[]);

int  creatGraph(char name[], NODE *list[]);

void initList(NODE *list[]);

//同上
void showPath(int path[]);

void drawPicture();

int pow1(int a, int x);

int transNumber(char s[]);

/*********************************************************************************/
/*********************************************************************************/
/******************************栈函数定义区****************************************/
/*********************************************************************************/
/*********************************************************************************/


//栈初始化函数，为栈指针s申请动态内存，同时将所有边的起点、终点、权重初始化为-1
void initStack(STACK **s);

//判断栈空的函数，栈空则返回1，否则返回0
int is_emptyStack(STACK *s);

//判断栈满的函数，栈空则返回1，否则返回0
int is_fullStack(STACK *s);

//压栈函数，接收EDGE*类型的数据压栈。正常返回值为0，如果栈满则返回-1
int push(int n, STACK *s);

//出栈函数，将栈顶元素泵出，赋值给e。正常返回值为0，如果栈空则返回-1
int pop(STACK *s);

//取栈顶元素函数，将栈顶元素的值赋给e，但是并不影响栈顶指针。正常返回值为0，如果栈空则返回-1
int get(STACK *s);

//栈删除函数，释放栈所占内存区域，指针放空
void delStack(STACK *s);

/*********************************************************************************/
/*********************************************************************************/
/******************************队列函数定义区***************************************/
/*********************************************************************************/
/*********************************************************************************/

edge e[N * N * 2], ex[N * N * 2];
int p[N], px[N], eid, exid;
int h[N], vis[N];

//队列初始化函数，为队列指针s申请动态内存，同时将所有边的起点、终点、权重初始化为-1
void initQueue(QUEUE *q);

//判断队空函数，队空则返回1，否则返回0
int is_emptyQueue(QUEUE *q);

//判断队满函数，队满则返回1，否则返回0
int is_fullQueue(QUEUE *q);

//入队函数，接收EDGE*类型的数据入队尾。正常返回值为0，如果队满则返回-1
int enqueue(int n, QUEUE *q);

//出队函数， 将队头元素出队并赋值给e.正常返回值为0，如果队空则返回-1
int dequeue( QUEUE *q);

//队列删除函数,释放队列所占内存区域，指针放空
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
