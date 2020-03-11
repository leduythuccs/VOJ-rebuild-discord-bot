#include "spoj.h"
#include <stdio.h>
#include <algorithm>
#include <stack>
#include <string.h>
using namespace std;

//input: in.txt
//output: out.txt
//answer: ans.txt


//FILE *spoj_p_in, *spoj_p_out, *spoj_t_out;
//#define PIN "in.txt"
//#define POUT "ans.txt"
//#define TOUT "out.txt"
#define foru(i, l, r) for(i = l; i <= r;i ++)

const int maxN = 2*int(1e6)+111;

struct edge {
         int u, v;
         edge (int u, int v) : u(u), v(v) {}
         edge() {}
};

bool operator < (edge i, edge j) {
         if (i.u != j.u) return i.u < j.u;
         return i.v < j.v;
}

bool operator == (edge i, edge j) {
         if (i.u != j.u) return false;
         return i.v == j.v;
}

edge     inp[maxN], tmp_edge;
int      path[maxN];
bool     dau[maxN], vip[maxN];
int      N, M, S, K, i, tmp, D, dem = 0, x;

//void spoj_init()
//{
//    spoj_p_in=fopen(PIN, "r");
//    spoj_p_out=fopen(POUT, "r");
//    spoj_t_out=fopen(TOUT, "r");
//}
//
//void spoj_assert(bool b) {
//    if (!b) exit(1);
//}

int main(){
    spoj_init();

    char ans[100], ret[100];
    fscanf(spoj_p_out, "%s", ans);
    fscanf(spoj_t_out, "%s", ret);
    spoj_assert(strcmp(ans, ret)==0);
    if (strcmp(ans, "TAK")==0) {
         //fscanf(spoj_t_out, "\n");
         int s, k, n;
         fscanf(spoj_p_in, "%d %d %d %d", &N, &M, &S, &K);
         foru(i, 1, M) fscanf(spoj_p_in, "%d %d", &inp[i].u, &inp[i].v);

         tmp = M;
         foru(i, 1, M)
                  inp[++tmp] = edge(inp[i].v, inp[i].u);
         M = tmp;
         sort(inp+1, inp+M+1);

         fscanf(spoj_t_out, "%d", &D);
         foru(i, 1, D) fscanf(spoj_t_out, "%d", &path[i]);

         foru(i, 1, K) fscanf(spoj_p_in, "%d", &x), vip[x] = true;

         spoj_assert(path[1] == S);
         spoj_assert(path[D] == S);

         foru(i, 2, D) {
                  tmp_edge = edge(path[i-1], path[i]);
                  x = lower_bound(inp+1, inp+M+1, tmp_edge)-inp;
                  spoj_assert(x <= M);
                  spoj_assert(tmp_edge == inp[x]);
                  spoj_assert(!dau[x]);
                  dau[x] = true;
                  vip[path[i]] = false;
         }

         foru(i, 1, N) spoj_assert(!vip[i]);
    }
    return 0;
}
