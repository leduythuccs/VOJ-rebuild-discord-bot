#include "spoj.h"

#include <set>
#include <map>
#include <list>
#include <cmath>
#include <queue>
#include <stack>
#include <cstdio>
#include <string>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <complex>
#include <iostream>
#include <algorithm>

#include <ctime>
#include <deque>
#include <bitset>
#include <cctype>
#include <utility>
#include <cassert>

using namespace std;
int n,m,K,cnt[55][55],ans,used[1005];
vector<string> dict;
set<string> exist;
char grid[55][55],tmp[55];
int X,Y,Z,T;
bool ngang[55][55], doc[55][55];

void row(string S,int u,int v)
{
	spoj_assert(!ngang[u][v-1]);
	spoj_assert(v+S.length()-1 <= 50);
	spoj_assert(!ngang[u][v+S.length()]);

	for(int i=0; i<S.size(); i++)
	{
		spoj_assert(grid[u][v+i]=='.' || grid[u][v+i]==S[i]);
		grid[u][v+i]=S[i];
		cnt[u][v+i]++;

		spoj_assert(!ngang[u][v+i]);
		ngang[u][v+i] = true;
	}
}
void col(string S,int u,int v)
{
	spoj_assert(!doc[u-1][v]);
	spoj_assert(u+S.length()-1 <= 50);
	spoj_assert(!doc[u+S.length()][v]);

	for(int i=0; i<S.size(); i++)
	{
		spoj_assert(grid[u+i][v]=='.' || grid[u+i][v]==S[i]);
		grid[u+i][v]=S[i];
		cnt[u+i][v]++;

		spoj_assert(!doc[u+i][v]);
		doc[u+i][v] = true;
	}
}
void readinput()
{
	spoj_assert(fscanf(spoj_p_in,"%d %d %d",&n,&m,&K) == 3);
	spoj_assert(n>=1 && n<=50);
	spoj_assert(m>=1 && m<=50);
	spoj_assert(K>=1 && K<=1000);
	for(int i=1; i<=K; i++)
	{
		fscanf(spoj_p_in,"%s",tmp);
		spoj_assert(!exist.count(string(tmp)));

		int l = strlen(tmp);
		spoj_assert(4 <= l && l <= 30);
		exist.insert(tmp);
		dict.push_back(string(tmp));
	}
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++) grid[i][j]='.';
}
void readoutput()
{
	int id,u,v,t;
	spoj_assert(fscanf(spoj_t_out,"%d",&ans)==1);
	spoj_assert(ans>=0 && ans<=K);
	for(int i=1; i<=ans; i++)
	{
		spoj_assert(fscanf(spoj_t_out,"%d %d %d %d",&id,&u,&v,&t)==4);
		spoj_assert(id>=1 && id<=K);
		spoj_assert(!used[id]); used[id]++;
		spoj_assert(u>=1 && u<=n);
		spoj_assert(v>=1 && v<=m);
		spoj_assert(t==0 || t==1);
		if(t==0) X++;
		else Y++;
		if(t==0) row(dict[id-1],u,v);
		else col(dict[id-1],u,v);
	}
}
void scoring()
{
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++)
			if(cnt[i][j]==2) Z++;
			else if(cnt[i][j]==1) T++;
	T+=Z;
	fprintf(spoj_score,"%.2lf\n",1.0*(X*Y+sqrt(Z*Z*Z)+T)/(1.0*n*m));
	cerr << X << ' ' << Y << ' ' << Z << ' ' << T << endl;
}
int main()
{
	spoj_init();
	readinput();
	readoutput();
	scoring();
	return 0;
}
