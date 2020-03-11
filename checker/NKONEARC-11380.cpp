#include <spoj.h>
#include <bits/stdc++.h>
using namespace std;

#define NMAX 2200
int n, m;
bool a[2][NMAX][NMAX], dau[NMAX];

void dfs(int i, int u)
{
    dau[u]=true;
    for (int v=1; v<=n; v++)
        if (!dau[v] && a[i][u][v])
            dfs(i, v);
}

int main()
{
	spoj_init();  

    memset(a, false, sizeof(a));
	fscanf(spoj_p_in, "%d%d", &n, &m);  
	for (int i=0; i<m; i++)
	{
        int u, v;
    	fscanf(spoj_p_in, "%d%d", &u, &v) ;  
    	a[0][u][v]=true;
    	a[1][v][u]=true;
    }
    {
        char ans[100];
        int u, v;
    	fscanf(spoj_t_out, "%s%d%d", ans, &u, &v);  
    	a[0][u][v]=true;
    	a[1][v][u]=true;    	
    	spoj_assert(strcmp(ans,"YES")==0);
    }
    memset(dau, false, sizeof(dau));
    dfs(0, 1);
    for (int u=1; u<=n; u++)
        spoj_assert(dau[u]);
    memset(dau, false, sizeof(dau));        
    dfs(1, 1);
    for (int u=1; u<=n; u++)
        spoj_assert(dau[u]);    
	return 0;
}
