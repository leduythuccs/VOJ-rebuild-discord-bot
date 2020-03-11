#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <string>
#include <deque>
#include <complex>
#include <sstream>
#include <iomanip>
#include <cassert>
#include "spoj.h"
using namespace std;
/*FILE *spoj_p_in, *spoj_t_out, *spoj_score;
#define PIN "in.in"
#define TOUT "out.out"
#define SCORE "result.out"

void spoj_init()
{
	spoj_p_in = fopen(PIN, "r");
	spoj_t_out = fopen(TOUT, "r");
	spoj_score = fopen(SCORE, "w");
}

#define spoj_assert assert*/
struct bg{
    int a, b, c;} c[5005];

bool cmp(const bg&x, const bg&y)
{
    if (x.a>y.a) return true;
    return false;
}

int f[5005][3000], n, vt[5005];
bool kt[5005];

void ReadInput()
{
    spoj_assert(fscanf(spoj_p_in, "%d\n", &n) == 1);
    spoj_assert(n>=1 && n<=5000);
    for(int i=1; i<=n; i++)
    {
        spoj_assert(fscanf(spoj_p_in, "%d\n", &c[i].a) == 1);
        spoj_assert(c[i].a>=1 && c[i].a<=400000);
    }
    for(int i=1; i<=n; i++)
    {
        spoj_assert(fscanf(spoj_p_in, "%d\n", &c[i].b) == 1);
        spoj_assert(c[i].b>=1 && c[i].b<=400000);
    }
    for(int i=1; i<=n; i++) c[i].c = i;
    sort(1+c, 1+n+c, cmp);
    f[1][1] = 0;
    for(int i=2; i<=n; i++)
    {
        for(int j=0; j<=i/2; j++)
        {
            f[i][j] = f[i-1][j];
            if (j>0) f[i][j] = max(f[i][j], f[i-1][j-1] + c[i].b);
        }
    }
    for(int i=1; i<=n; i++) vt[c[i].c] = i;
}

int ReadOutput()
{
    int res;
    spoj_assert(fscanf(spoj_t_out, "%d", &res) == 1);
    spoj_assert(res == f[n][n/2]);
    int sum = 0;
    memset(kt, true, sizeof(kt));
    for(int i=1; i<=n/2; i++)
    {
        int x, y;
        spoj_assert(fscanf(spoj_t_out, "%d%d", &x, &y) == 2);
        spoj_assert(x>=1 && x<=n);
        spoj_assert(y>=1 && y<=n);
        spoj_assert(kt[x]);  kt[x] = false;
        spoj_assert(kt[y]);  kt[y] = false;
        x = vt[x]; y = vt[y];
        if (c[x].a<c[y].a) sum += c[x].b; else sum += c[y].b;
    }
    spoj_assert(sum == res);
    return 10;
}

int main()
{
    spoj_init();
    ReadInput();
    fprintf(spoj_score, "%d\n", ReadOutput());
    return 0;
}
