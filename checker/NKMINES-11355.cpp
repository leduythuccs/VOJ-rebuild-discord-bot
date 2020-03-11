#include <spoj.h>
#include <bits/stdc++.h>
using namespace std ;

#define NMAX 220
int a[NMAX][NMAX], b[NMAX][NMAX];
const int di[]={1,1,1,0,0,-1,-1,-1};
const int dj[]={-1,0,1,-1,1,-1,0,1};

int main()
{
	spoj_init();  

    int m, n;
	fscanf(spoj_p_in, "%d%d", &m, &n);  
    for (int i=1; i<=m; i++)
        for (int j=1; j<=n; j++)            
            fscanf(spoj_p_in, "%d", &a[i][j]);
    memset(b, 0, sizeof(b));
    for (int i=1; i<=m; i++)
        for (int j=1; j<=n; j++)            
        {
            spoj_assert(fscanf(spoj_t_out, "%d", &b[i][j])==1);                
            spoj_assert(b[i][j]==0 || b[i][j]==1);            
        }
    for (int i=1; i<=m; i++)
        for (int j=1; j<=n; j++)
        {
            int c=0;
            for (int d=0; d<8; d++)
                c+=b[i+di[d]][j+dj[d]];
            spoj_assert(c==a[i][j]);                 
        }
	return 0;
}
