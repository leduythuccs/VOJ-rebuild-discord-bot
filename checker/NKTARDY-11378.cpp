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

#define NMAX 102000
int p[NMAX], d[NMAX];
bool dau[NMAX];

int main()
{
	spoj_init();  	

	int n, ans, ret;	
	fscanf(spoj_p_out, "%d", &ans);
	spoj_assert(fscanf(spoj_t_out, "%d", &ret)==1);
	spoj_assert(ret==ans);	
	fscanf(spoj_p_in, "%d", &n);	
	for (int i=1; i<=n; i++)
		fscanf(spoj_p_in, "%d", &p[i]);
	for (int i=1; i<=n; i++)
		fscanf(spoj_p_in, "%d", &d[i]);			
	int t=0, c=0;
	memset(dau, false, sizeof(dau));
	for (int i=1; i<=n; i++)
	{
		int x;
		spoj_assert(fscanf(spoj_t_out, "%d", &x)==1);
		spoj_assert(1<=x && x<=n);
		spoj_assert(!dau[x]);
		dau[x]=true;
		t+=p[x];
		if (t>d[x])
			c++;
	}
	spoj_assert(c==ans);
	return 0;
}
