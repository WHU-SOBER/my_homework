#ifndef _STATS_H
#define _STATS_H



//�������ļ���Ϊͼ��ʶ����char���飬����ͼ�бߵ���Ŀ
int numberOfEdges(char name[]);


//�������ļ���Ϊͼ��ʶ����char���飬����ͼ��(���űߵ�)�������Ŀ
int numberOfVertices(char name[]);



//�������ļ���Ϊͼ��ʶ����char����,����ͼ��Freeman's Network Centralityֵ
//���ṩ����Ϊ����ͼ�������������ֵ��ʱ����Ե���˫����ͨ
double freemanNetworkCentrality(char name[]);




//�������ļ���Ϊͼ��ʶ����char���飬����ͼ��Betweenness Centralityֵ
double betweennessCentrality(char name[], char NOde[]);



//�������ļ���Ϊͼ��ʶ����char���飬����ͼ��Clossness Centralityֵ
double closenessCentrality(char name[], char NOde[]);



//�������ļ���Ϊͼ��ʶ����char���飬����ͼ������Eigenvector Centralityֵ
double eigenvectorCentrality(char name[], char NOde[]);
#endif

