//#include <stdafx.h>
#include <spoj.h>
#include <bits/stdc++.h>
using namespace std;

/*FILE *spoj_p_in, *spoj_p_out, *spoj_t_out;
#define PIN "in.txt"
#define POUT "ans.txt"
#define TOUT "out.txt"

void spoj_init()
{
	spoj_p_in=fopen(PIN, "r");
	spoj_p_out=fopen(POUT, "r");
	spoj_t_out=fopen(TOUT, "r");
}
void spoj_assert(bool b)
{	
	if (!b)
	{			
		printf("WA");
		exit(1);		
	}
}*/

#define NMAX 220
int a[NMAX][NMAX];
int n;
bool dau[NMAX];

void dfs(int u)
{
	dau[u]=true;
	for (int v=1; v<=n; v++)
		if (!dau[v] && a[u][v]>0)
			dfs(v);
}

int main()
{
	spoj_init();  	

	int s, t, m;
	fscanf(spoj_p_in,"%d%d",&n,&m);
	memset(a,0,sizeof(a));
	for (int i=0; i<m; i++)
	{
		int u, v, c;
		fscanf(spoj_p_in,"%d%d%d",&u,&v,&c);
		a[u][v]=a[v][u]=c;
	}
	fscanf(spoj_p_in,"%d%d", &s, &t);
	int cans, kans, kret,cret=0;
	fscanf(spoj_p_out,"%d%d",&cans,&kans);
	spoj_assert(fscanf(spoj_t_out,"%d",&kret)==1);
	spoj_assert(kans==kret);	
	for (int i=0; i<kans; i++)
	{
		int u, v;
		spoj_assert(fscanf(spoj_t_out,"%d%d",&u, &v)==2);
		spoj_assert(a[u][v]>0);		
		cret=max(cret,a[u][v]);
		a[u][v]=a[v][u]=0;
	}
	spoj_assert(cans==cret);
	memset(dau, false, sizeof(dau));
	dfs(s);
	spoj_assert(!dau[t]);

	return 0;
}

