#include <bits/stdc++.h>
#include "spoj.h"
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

#define NMAX 210
int a[NMAX][NMAX];
int n, m;

int main()
{
	spoj_init();  	

    memset(a, 0, sizeof(a));    
	fscanf(spoj_p_in, "%d%d", &n, &m);  
	for (int i=0; i<n; i++) {int x; fscanf(spoj_p_in, "%d", &x);}
	for (int i=0; i<m; i++)
	{
		int u, v;
      	fscanf(spoj_p_in, "%d%d", &u, &v);  
      	a[u][v]++;
		a[v][u]++;
    }	

    int k;
    spoj_assert(fscanf(spoj_t_out, "%d", &k)==1);  
    spoj_assert(k==m);

	{
		int u, v;    
		spoj_assert(fscanf(spoj_t_out, "%d", &u)==1);  
		for (int i=0; i<m; i++)
		{
			spoj_assert(fscanf(spoj_t_out, "%d", &v)==1);  
			spoj_assert(a[u][v]>0);
			a[u][v]--;
			a[v][u]--;
			u=v;
		}
	}
	return 0;
}

