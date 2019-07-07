#ifndef _STATS_H
#define _STATS_H



//接受以文件名为图标识符的char数组，返回图中边的数目
int numberOfEdges(char name[]);


//接受以文件名为图标识符的char数组，返回图中(连着边的)顶点的数目
int numberOfVertices(char name[]);



//接受以文件名为图标识符的char数组,返回图中Freeman's Network Centrality值
//所提供数据为有向图，但是在算这个值的时候可以当成双向联通
double freemanNetworkCentrality(char name[]);




//接受以文件名为图标识符的char数组，返回图中Betweenness Centrality值
double betweennessCentrality(char name[], char NOde[]);



//接受以文件名为图标识符的char数组，返回图中Clossness Centrality值
double closenessCentrality(char name[], char NOde[]);



//接受以文件名为图标识符的char数组，返回图中最大的Eigenvector Centrality值
double eigenvectorCentrality(char name[], char NOde[]);
#endif

