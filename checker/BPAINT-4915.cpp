#include <spoj.h>
#include <cassert>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <iostream>
#include <cstring>
using namespace std;

/*FILE *spoj_p_in, *spoj_p_out, *spoj_t_out, *spoj_score;
#define PIN "in.txt"
#define POUT "ans.txt"
#define TOUT "out.txt"
#define SCORE "score.txt"

void spoj_init()
{
spoj_p_in=fopen(PIN, "r");
spoj_p_out=fopen(POUT, "r");
spoj_t_out=fopen(TOUT, "r");
spoj_score=fopen(SCORE, "w"); 
}

#define spoj_assert assert*/

#define MAX 60

int a[MAX][MAX], n, m, k, cnt;
bool visit[MAX][MAX];

const int di[] = {-1,0,1,0};
const int dj[] = {0,1,0,-1};

void dfs(int i, int j) {
    visit[i][j]=true;
    ++cnt;
    for (int d=0; d<4; ++d) {
        int i2 = i + di[d];
        int j2 = j + dj[d];
        if (1<=i2 && i2<=n && 1<=j2 && j2<=m && a[i2][j2]==a[i][j] && !visit[i2][j2]) {
            dfs(i2,j2);
        }
    }
}

int main() {
    spoj_init();
    fscanf(spoj_p_in, "%d%d%d",&n,&m,&k);
    for (int i=1; i<=n; ++i) for (int j=1; j<=m; ++j) fscanf(spoj_p_in,"%d", &a[i][j]);
    
    double hs2 = 1;
    if(m == 5 || m == 20 || m == 30) hs2 = 2;
    if(m == 40) hs2 = 1/1.5;
    if(m == 50) hs2 = 1/12.0;
    
    memset(visit,0,sizeof(visit));
    int heso = 0;
    for(int i=1;i<=n;++i) for(int j=1;j<=m;++j)if(!visit[i][j]){
		cnt = 0;
		dfs(i,j);
		heso += cnt * cnt;	
	}
	memset(visit,0,sizeof(visit));
    
    while (k--) {
        int i, j, t;
        spoj_assert(fscanf(spoj_t_out, "%d%d%d", &i, &j, &t) == 3);
        spoj_assert(1<=i && i<=n);
        spoj_assert(1<=j && j<=m);
        spoj_assert(1<=t && t<=3000);
        memset(visit,0,sizeof(visit));
        dfs(i,j);
        for (int i=1; i<=n; ++i) for (int j=1; j<=m; ++j) if (visit[i][j]) a[i][j]=t;        
    }
/*    for (int i=1; i<=n; ++i) {
        for (int j=1; j<=m; ++j) cout << a[i][j] << " ";
        cout << endl;
    }*/
    double scr = 0;
    memset(visit,0,sizeof(visit));
    for (int i=1; i<=n; ++i) for (int j=1; j<=m; ++j) if (!visit[i][j]) {
        cnt = 0;
        dfs(i,j);        
        scr += cnt*cnt;
    }
    scr/=heso;
    scr = scr * hs2;
    fprintf(spoj_score, "%lf", scr);    
    return 0;
}
