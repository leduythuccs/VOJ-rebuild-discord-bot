/*
	Allow max swap is 10^5
*/

#include "spoj.h"
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000 + 5;
int a[MAXN][MAXN];
int row_id[MAXN], col_id[MAXN];
int m,n;
int MAX_SWAP = (int)1e5;

int main(){
	spoj_init();
	
	//input the board;
	fscanf(spoj_p_in, "%d%d", &m, &n);
	for(int i=1; i<=m; ++i)
	for(int j=1; j<=n; ++j)
		fscanf(spoj_p_in, "%d", &a[i][j]);
		
	//init row_id, col_id
	for(int i=1; i<=m; ++i) row_id[i] = i;
	for(int j=1; j<=n; ++j) col_id[j] = j;
	
	//solution x0, y0
	int sol_x0, sol_y0;
	fscanf(spoj_p_out, "%d %d", &sol_x0, &sol_y0);
	
	//Check output x0, y0
	int x0, y0;
	spoj_assert(fscanf(spoj_t_out, "%d %d\n", &x0, &y0)==2);
	spoj_assert(0<=x0 && x0<=m && 0<=y0 && y0<=n);
	spoj_assert(x0+y0 == sol_x0+sol_y0);
	if (sol_x0==0 && sol_y0==0){
		fprintf(spoj_score, "1");
		return 0;
	}
	
	//Check swap
	int num_swap;
	spoj_assert(fscanf(spoj_t_out, "%d\n", &num_swap)==1);
	spoj_assert(0<=num_swap && num_swap<=MAX_SWAP);
	while(num_swap--){
		char c; int i, j;
		spoj_assert(fscanf(spoj_t_out,"%c %d %d\n", &c, &i, &j)==3);
		spoj_assert(c=='R' || c=='C');		
		if (c=='R'){
			spoj_assert(1<=i && i<=m && 1<=j && j<=m);
			swap(row_id[i], row_id[j]);
		}
		else {
			spoj_assert(1<=i && i<=n && 1<=j && j<=n);
			swap(col_id[i], col_id[j]);
		}		
	}
	
	//Check board after swap
	for(int i=1; i<=x0; ++i)
	for(int j=1; j<=y0; ++j)
		spoj_assert( a[row_id[i]][col_id[j]] == 1 );		
		
	fprintf(spoj_score, "1");	
	return 0;
}