#ifndef _SEARCH_H_
#define _SEARCH_H_

int DFS(int u, int v, char name[], int path[]);

void BFS(int u, int v, char name[], int path[]);

int Dijkstra(int u, int v, char name[], int path[]);

void SPFA(int u, int v, char name[], int path[]);

void A(int u, int v, char name[], int path[]);

int* shortestPath(int u, int v, char algorithm[], char name[]);

#endif
