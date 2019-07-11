#include "util.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#define max	10000
#define	INF	0x3f3f3f3f

char trans(int a, int b, int size);

int main() {
  game_state_t state;
  memset(&state, 0, sizeof(state));
  init(&state);
  // write your code here
  int x,y;
  int dx[] = {-1,0,1,0};
  int dy[] = {0,1,0,-1};
  int number[max];
  double dist[max];
  int path[max];
  int count = 0;
  int s[max];
  int u,i,j;
  for(int i = 0; i<state.m * state.n; i++){
	  s[i] = 0;
  }
  

  
  	for(int j =0;j<(state.m)*(state.n);j++){
    	if(state.grid[j/state.m][j%state.m] == 0){
        	dist[j] = INF;
            path[j] = -1;
        }
    }
  

  x = state.start_x;
  y = state.start_y;
  int di,dj;
  for(int k = 0; k<4; k++){
	  di = x + dx[k];
	  dj = y + dy[k];
	  if(di>=0 && di< state.n && dj>=0 && dj<state.m && state.grid[di][dj] == 0){
		  dist[di*state.m + dj] = state.cost[di][dj];
		  path[di*state.m + dj] = x*state.m + y;
		  //printf("%d-%d-%d\n",di,dj,path[di*state.m + dj]);
	  }
  }


  int v = state.start_x * state.m + state.start_y;
  s[v] = 1;
  path[v] = 0;
  int mindis = INF;
  for( i = 0; i<state.m*state.n ; i++){
	 if(state.grid[i/state.m][i%state.m] == 0){
		mindis = INF;
		//printf("%d\n",i);
 	 	for( j = 0; j < state.m*state.n; j++){
 			if(s[j] == 0 && state.grid[j/state.m][j%state.m] == 0 && dist[j] < mindis)			 {				
				u = j;
			    mindis = dist[j];
			}
		} 
		//printf("%d\n",mindis);
		s[u] = 1;
		for(int p = 0;p<state.n;p++){
			for(int k = 0;k<state.m;k++){
				if(s[p*state.m+k] == 0){
					if(state.grid[p][k] == 0&&fabs(u/state.m-p)+fabs(u%state.m-k)<=1
						&& dist[u] + state.cost[p][k] < dist[p*state.m+k]){
						dist[p*state.m+k] = dist[u] + state.cost[p][k];
						path[p*state.m+k] = u;
						//printf("%d-%d-%d\n",p,k,path[p*state.m+k]);
					}
				}
			}
		}
  	}
  }


  //for(j = 0;j < state.n*state.m; j++){
	//  if(state.grid[j/state.m][j%state.m] == 0){
	//	  printf("%d-%d-%d\n",j/state.m,j%state.m,path[j]);
	//  }
// }
  char result[max];
  int end = state.goal_x *state.m + state.goal_y;
  int d = end , t,cx = 0;
  while(d!=v){
	  t = path[d];
	  result[cx++] = trans(t,d,state.m);
	  d = t;
  } 
  
  for(int i = cx-1;i>=0; i--){
	  printf("%c",result[i]);
  }
  // 
  destroy(&state);
  return 0;
}


char trans(int a, int b, int size){
     if(a - b == 1)
         return 'W';
     else if(a - b == -1)
         return 'E';
     else if(a - b == size)
         return 'N';
     else if(a - b == -size)
         return 'S';
     else
         return '0';
}
