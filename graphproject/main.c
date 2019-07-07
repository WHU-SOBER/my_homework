#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stats.h"
#include "search.h"
#include "mytools.h"

int main(int argc, char** argv)
{

	if (argc == 2)
	{
		if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)
		{
			printf("Helping tips are following:\n");
			printf("There are only 3 order forms you can use:\n\n");
			printf("0.\"./search-cli -j\" to see how SuanTouJun looks like.\n\n");
			printf("1.\"./search-cli -h/--help\" to get help.\n");
			printf("Considering you are watching these words...just ignore this tip.hhh\n\n");
			printf("2.\".search-cli -g/--graph FILE_PATH -s/--stats STATS_PARAMS -u node's name\"to display the stats information of graph contained in the file named \"FILE_PATH\".\n");
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
		else if (strcmp(argv[1], "-j") == 0)
			drawPicture();
	}
	else if (argc == 5 || argc == 7)
	{
		if ((strcmp(argv[1], "-g") == 0 || strcmp(argv[1], "--graph")) && (strcmp(argv[3], "-s") == 0 || strcmp(argv[3], "--states")))
		{
			if (strcmp(argv[4], "edges") == 0)
				printf("The number of edges is %d\n", numberOfEdges(argv[2]));
			else if (strcmp(argv[4], "vertices") == 0)
				printf("The number of vertices is %d\n", numberOfVertices(argv[2]));
			else if (strcmp(argv[4], "freeman") == 0)
				printf("The freeman's network centrality value is %lf\n", freemanNetworkCentrality(argv[2]));
			else if (strcmp(argv[4], "betweenness") == 0)
				{
				if(strcmp(argv[5], "-u") == 0)
					printf("The betweenness centrality value is %lf\n", betweennessCentrality(argv[2], argv[6]));
				}
			else if (strcmp(argv[4], "closeness") == 0)
				{
				if (strcmp(argv[5], "-u") == 0)
					printf("The closeness centrality value is %lf\n", closenessCentrality(argv[2], argv[6]));
				}
			else if (strcmp(argv[4], "eigenvector") == 0)
				{
				if (strcmp(argv[5], "-u") == 0)
					printf("The eigenvector centrality value is %lf\n", eigenvectorCentrality(argv[2], argv[6]));
				}
		}
	}
	else if (argc == 9)
	{
		if ((strcmp(argv[1], "-g") == 0 || strcmp(argv[1], "--graph")) && (strcmp(argv[3], "-sp") == 0 || strcmp(argv[3], "--shortestpath")))
		{
			showPath(shortestPath(transNumber(argv[6]), transNumber(argv[8]), argv[4], argv[2]));
		}
	}
	else
		printf("emm...Are you sure that you just input the rihgt order?\nIf you don\'t know what to do, try use\"./search-cli -h/--help\"\n");
	return 0;
}


