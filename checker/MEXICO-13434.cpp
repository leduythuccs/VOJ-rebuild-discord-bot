#include <spoj.h>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;
/*
    #include <cassert>
    FILE *spoj_p_in, *spoj_p_out, *spoj_t_out;
    #define PIN "MEXICO.inp"
    #define POUT "MEXICO.ans"
    #define TOUT "MEXICO.out"

    void spoj_init()
    {
        spoj_p_in=fopen(PIN, "r");
        spoj_p_out=fopen(POUT, "r");
        spoj_t_out=fopen(TOUT, "r");
    }

    #define spoj_assert assert
*/
int n, m;
bool c[1001][1001];
int path[1001];
bool done[1001];
bool cross(int a1, int a2, int b1, int b2){
    if(a1>a2) swap(a1, a2);
    if(b1>b2) swap(b1, b2);
    if((a1<b1)&&(b1<a2)){
        return ((b2>a2)||(b2<a1));
    }
    else{
        return ((a1<b2)&&(b2<a2));
    }
}
int main()
{
	spoj_init();
	int result;
	int t=fscanf(spoj_p_out, "%d", &result);
	int no_solution=(t==EOF);
	spoj_assert(fscanf(spoj_t_out, "%d", &path[1])==1);
	if(no_solution){
        spoj_assert(path[1]==-1);
        return 0;
	}
    fscanf(spoj_p_in, "%d%d", &n, &m);
    {
        int u, v;
        for(int i=1; i<=m; i++){
            fscanf(spoj_p_in, "%d%d", &u, &v);
            c[u][v]=c[v][u]=1;
        }
    }
    spoj_assert((1<=path[1])&&(path[1]<=n));
    done[path[1]]=1;
    ///check vertices and edges
    for(int i=2; i<=n; i++){
        spoj_assert(fscanf(spoj_t_out, "%d", &path[i])==1);
        spoj_assert((1<=path[i])&&(path[i]<=n));
        spoj_assert(done[path[i]]==0);
        spoj_assert(c[path[i-1]][path[i]]==1);
        done[path[i]]=1;
    }
    ///check crossover
    for(int i=2; i<=n; i++) for(int j=i+2; j<=n; j++){
        spoj_assert(cross(path[i-1], path[i], path[j-1], path[j])==0);
    }
	return 0;
}