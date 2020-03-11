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

int dx[4] = {0, -1, 0, 1};
int dy[4] = {-1, 0, 1, 0};
bool inq[1010][1010], kt[10001000];
int a[10001000], b[1010][1010];
int m, n, k;

int loang(int u, int v, int t)
{
    int res = 1;
    inq[u][v] = false;
    for(int i=0; i<4; i++)
    {
        int x = u + dx[i], y = v + dy[i];
        if (x<1||x>m||y<1||y>n) continue;
        if (!inq[x][y]) continue;
        if (b[x][y] != t) continue;
        inq[x][y] = false;
        res += loang(x, y, t);
    }
    return res;
}

void ReadInput()
{
    spoj_assert(fscanf(spoj_p_in, "%d%d\n", &m, &n) == 2);
    spoj_assert(n>=1 && n<=1000);
    spoj_assert(m>=1 && m<=1000);
    spoj_assert(fscanf(spoj_p_in, "%d\n", &k) == 1);
    int sum = 0;
    for(int i=1; i<=k; i++)
    {
        spoj_assert(fscanf(spoj_p_in, "%d", &a[i]) == 1);
        sum += a[i];
    }
    spoj_assert(sum <= m*n);
}

int readOutput()
{
    for(int i=1; i<=m; i++)
        for(int j=1; j<=n; j++)
    {
        int x;
        spoj_assert(fscanf(spoj_t_out, "%d", &x) == 1);
        b[i][j] = x;
        spoj_assert(x <= k);
    }
    memset(kt, true, sizeof(kt));
    memset(inq, true, sizeof(inq));
    for(int i=1; i<=m; i++)
        for(int j=1; j<=n; j++)
            if (b[i][j]>0)
            {
                int x = b[i][j];
                if (!kt[x] && inq[i][j]) spoj_assert(1 == 0);
                if (!inq[i][j]) continue;
                int y = loang(i, j, x);
                spoj_assert(y == a[x]);
                kt[x] = false;
            }
    for(int i=1; i<=k; i++) spoj_assert(a[i]==0 || !kt[i]);
    return 4;
}

int main()
{
    spoj_init();
    ReadInput();
    fprintf(spoj_score, "%d\n", readOutput());
    return 0;
}
