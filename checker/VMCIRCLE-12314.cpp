#include "spoj.h"
#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 300 + 5;
struct Edge{
	int adj, color;	
	Edge(int adj, int color) : adj(adj), color(color) {}	
};

int n;
int nColor;
vector<Edge> a[MAX_N];	//Big circle is 0
bool f[MAX_N][8];


void addEdge(int i, int j, int c){
	a[i].push_back( Edge(j, c) );
	a[j].push_back( Edge(i, c) );
}

void input(){
	fscanf(spoj_p_in,"%d",&n);
}

void loadOutput(){
	//Solution color
	int solColor;	
	fscanf(spoj_p_out,"%d",&solColor);
	
	//Ouput color
	spoj_assert( fscanf(spoj_t_out,"%d\n",&nColor)==1 );
	spoj_assert( solColor == nColor );
		
	for(int color, i=1; i<=n; ++i){
		spoj_assert( fscanf(spoj_t_out,"%d",&color)==1 );
		spoj_assert( 1<=color && color<=nColor );
		color--;	//Checker use 0-base color
		addEdge(0, i, color);
	}
	
	for(int color, i=1; i<=n; ++i){
		spoj_assert( fscanf(spoj_t_out,"%d",&color)==1 );
		spoj_assert( 1<=color && color<=nColor );
		color--;	//Checker use 0-base color
		
		int j = (i%n) + 1;
		addEdge(i, j, color);		
	}	
}

void check(int i){
	memset(f, false, sizeof f);
	f[i][0] = true;
	
	queue< pair<int,int> > q;
	q.push( make_pair(i,0) );
	set<int> visited;
	while (!q.empty()){
		int i = q.front().first, state = q.front().second;
		q.pop();
		visited.insert(i);
		
		for(int k=0; k<(int)a[i].size(); ++k){
			int j = a[i][k].adj, color = a[i][k].color;
			if ( (state & (1<<color))==0 ){
				int nextState = state | (1<<color);
				if (!f[j][nextState]){
					f[j][nextState] = true;
					q.push( make_pair(j, nextState) );
				}
			}
		}
	}
	
	spoj_assert((int)visited.size()==n+1);	
}

int main(){
	spoj_init();
	input();
	loadOutput();
	for(int i=1; i<=n; ++i) check(i);
	fprintf(spoj_score, "1");
}