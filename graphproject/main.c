#include <stdio.h>
#include <stdlib.h>
#include "stats.h"
#include "search.h"
#include "mytools.h"

int strcmp(const char *p, const char *q)
{
	int i;
	for (i = 0; p[i] != '\0' && q[i] != '\0'; i++)
	{
		if (p[i] > q[i])
			return 1;
		if (p[i] < q[i])
			return -1;
	}
	if (p[i] == '\0' && q[i] != '\0')
		return -1;
	if (p[i] != '\0' && q[i] == '\0')
		return 1;
	return 0;
}

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

int main()
{
	
}
/*int main(int argc, char** argv)
{
	if (argc == 2)
	{
		if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help"))
		{
			printf("Helping tips are following:\n");
			printf("There are only 3 order forms you can use:\n\n");
			printf("1.\"./search-cli -h/--help\" to get help.\n");
			printf("Considering you are watching these words...just ignore this tip.hhh\n\n");
			printf("2.\".search-cli -g/--graph FILE_PATH -s/--stats STATS_PARAMS\" to display the stats information of graph contained in the file named \"FILE_PATH\".\n");
			printf("You can choose the following params as \"STATS_PARAMS\"\n");
			printf("edges\n");
			printf("vertices\n");
			printf("freeman\n");
			printf("betweenness\n");
			printf("closeness\n");
			printf("eigenvector\n\n");
			printf("3.\"./search-cli -g/--graph FILE_PATH -sp/--shortestpath SEARCH_PARAMS -u STARTING_POINT -v TARGET_POINT\" to display the shortest path from point u to point v using SEARCH_PARAMS.\n");
			printf("You can choose the following params as \"SEARCH_PARAMS\"\n");
			printf("DFS\n");
			printf("BFS\n");
			printf("Dijkstra\n");
			printf("SPFA\n");
			printf("A*\n");
		}
	}
	else if (argc == 5)
	{
		if ((strcmp(argv[1], "-g") == 0 || strcmp(argv[1], "--graph")) && (strcmp(argv[3], "-s") == 0 || strcmp(argv[3], "--states")))
		{
			if (strcmp(argv[4], "edges") == 0)
				printf("The number of edges is %d\n", numberOfEdges(argv[2]));
			else if (strcmp(argv[4], "vertics") == 0)
				printf("The number of vertics is %d\n", numberOfVertics(argv[2]));
			else if (strcmp(argv[4], "freeman") == 0)
				printf("The freeman's network centrality value is %lf\n", freemanNetworkCentrality(argv[2]));
			else if (strcmp(argv[4], "betweenness") == 0)
				printf("The betweenness centrality value is %lf\n", betweennessCentrality(argv[2]));
			else if (strcmp(argv[4], "closeness") == 0)
				printf("The closeness centrality value is %lf\n", closenessCentrality(argv[2]));
			else if (strcmp(argv[4], "eigenvector") == 0)
				printf("The largest eigenvector centrality value is %lf\n", eigenvectorCentrality(argv[2]));
		}
	}
	else if (argc == 9)
	{
		if ((strcmp(argv[1], "-g") == 0 || strcmp(argv[1], "--graph")) && (strcmp(argv[3], "-sp") == 0 || strcmp(argv[3], "--shortestpath")))
		{
			int path[MAXSIZE];
			if (strcmp(argv[4], "DFS") == 0)
			{
				DFS(argv[6][0] - '0', argv[6][0] - '0', argv[2], path);
				showPath(path);
			}
			else if (strcmp(argv[4], "BFS") == 0)
			{
				BFS(argv[6][0] - '0', argv[6][0] - '0', argv[2], path);
				showPath(path);
			}
			else if (strcmp(argv[4], "BFS") == 0)
			{
				BFS(argv[6][0] - '0', argv[6][0] - '0', argv[2], path);
				showPath(path);
			}
			else if (strcmp(argv[4], "Dijkstra") == 0)
			{
				Dijkstra(argv[6][0] - '0', argv[6][0] - '0', argv[2], path);
				showPath(path);
			}
			else if (strcmp(argv[4], "SPFA") == 0)
			{
				SPFA(argv[6][0] - '0', argv[6][0] - '0', argv[2], path);
				showPath(path);
			}
			else if (strcmp(argv[4], "A") == 0)
			{
				A(argv[6][0] - '0', argv[6][0] - '0', argv[2], path);
				showPath(path);
			}
		}
	}
	else
		printf("emm...Are you sure that you just input the rihgt order?\nIf you don\'t know what to do, try use\"./search-cli -h/--help\"\n");
	return 0;
}*/


