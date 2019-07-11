#include<stdio.h>
#include<stdlib.h>
#include"stats.h"
#include"mytools.h"


int numberOfEdges(char name[]) {
	FILE *fp = fopen(name, "r");
	int n = 0;
	while (fscanf(fp, "%*d%*d%*d") != EOF)
	{
		n++;
	}
	fclose(fp);
	return n;
}


//�������ļ���Ϊͼ��ʶ����char���飬����ͼ��(���űߵ�)�������Ŀ
int numberOfVertices(char name[]) {
	NODE *list[MAXSIZE];
	initList(list);
	return creatGraph(name, list);
}


//�������ļ���Ϊͼ��ʶ����char����,����ͼ��Freeman's Network Centralityֵ
//���ṩ����Ϊ����ͼ�������������ֵ��ʱ����Ե���˫����ͨ
double freemanNetworkCentrality(char name[]) {

	NODE *list[MAXSIZE];
	initList(list);
	creatGraph(name, list);
	NODE *p;
	int sum = 0;
	int count, degree = 0, max = 0;
	count = numberOfVertices(name);
	int cx = 0, k = 0;
	while (cx < count) {
		degree = 0;
		p = list[k];
		if (p->next != NULL) {
			cx++;
		}
		while (p->next != NULL) {
			p = p->next;
			degree++;
		}
		sum += degree;
		max = (max > degree) ? max : degree;
		k++;
	}
	double val = (double)(count*max - sum) / ((count - 1)*(count - 2));
	return val;
}


//�������ļ���Ϊͼ��ʶ����char���飬����ͼ��Betweenness Centralityֵ
double betweennessCentrality(char name[], char NOde[]) {
	int total = 0;
	int maxnum = 0;
	int path[MAXSIZE];
	//��ʼ���ڽӱ�
	NODE *list[MAXSIZE];
	initList(list);
	//��ͼ�����ڽӱ�
	creatGraph(name, list);
	for (int i = 0; i < MAXSIZE; i++)
	{
		if (list[i]->next != NULL)
			maxnum = i;
	}
	int score[MAXSIZE];
	int k = 0;
	for (int i = 0; i <= maxnum; i++)
		score[i] = 0;
	for (int i = 0; i <= maxnum; i++)
	{
		for (int j = 0; j <= maxnum; j++)
		{
			Dijkstra(i, j, name, path);
			if (path[k] != -1)
				total++;
			while (path[k] != -1)
			{
				score[path[k]]++;
				k++;
			}
			k = 0;
		}
	}
	if (strcmp(NOde, "max") == 0)
	{
		int maxbc = 0;
		for (int i = 0; i <= maxnum; i++)
		{
			if (score[i] > maxbc)
				maxbc = score[i];
		}
		return (double)maxbc / total;
	}
	else
	{
		int rs = transNumber(NOde);
		return (double)score[rs];
	}
}


//�������ļ���Ϊͼ��ʶ����char���飬����ͼ��Clossness Centralityֵ
double closenessCentrality(char name[], char NOde[])
{
		NODE *list[MAXSIZE];
		initList(list);
		creatGraph(name, list);
		int count, sum = 0;
		int n = 1;
		int path[MAXSIZE];
		for (int i = 0; i < MAXSIZE; i++) {
			path[i] = -1;
		}
		double closs[MAXSIZE] = { 0 };	//��¼Clossness Centrality
		count = numberOfVertices(name);
		int i = 0, k = 0;
		int flag = 0;
		int cx1 = 0, cx2 = 0;
		while (cx1 < count) {
			sum = 0;
			k = 0;
			flag = 0;
			cx2 = 0;
			while (cx2 < count - 1) {
				if (i != k) {
					if (Dijkstra(i, k, name, path) != -1) {
						sum += Dijkstra(i, k, name, path);
						flag++;
					}
					cx2++;
				}
				k++;
			}
			if (flag > 0) {
				sum = sum / flag;
				closs[i] = (double)1.0 / sum;
				cx1++;
			}
			i++;
		}
		if (strcmp(NOde, "max") == 0)
		{
			double max = 0;
			for (int t = 0; t < i; t++) {
				max = (max > closs[t]) ? max : closs[t];
			}
			return max;
		}
		else
		{
			int rs = transNumber(NOde);
			return (double)closs[rs];
		}
}

//�������ļ���Ϊͼ��ʶ����char���飬����ͼ������Eigenvector Centralityֵ
double eigenvectorCentrality(char name[], char NOde[]) {
	//

}
