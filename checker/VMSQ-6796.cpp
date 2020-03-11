#include <spoj.h>
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

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define ll long long
#define F first
#define S second
#define PB push_back
#define MP make_pair
using namespace std;

const double PI = acos(-1.0);

/*
FILE *spoj_p_in, *spoj_p_out, *spoj_t_out, *spoj_score;
#define PIN "6.in"
#define POUT "2.in"
#define TOUT "output.txt"
#define SCORE "result.txt"

void spoj_init()
{
	spoj_p_in=fopen(PIN, "r");
	spoj_p_out=fopen(POUT, "r");
	spoj_t_out=fopen(TOUT, "r");
	spoj_score=fopen(SCORE, "w");
}

#define spoj_assert assert
*/

int n;
int a[111][111];
int b[111][111];
const int MAXN = 50;
vector< pair<int,int> > ls;

long double getScore() {
    long long cnt = 0, sumdist = 0;
    FOR(i,1,n) FOR(j,1,n) {
        if (a[i][j] < 0 && b[i][j] > 0) ++cnt;
    }
    FOR(x,1,n) {
        ls.clear();
        long long cur = 0;
        FOR(i,1,n) FOR(j,1,n) if (b[i][j] == x) ls.PB(MP(i,j));
        REP(i,ls.size()) REP(j,i)
            cur += abs(ls[i].F - ls[j].F) + abs(ls[i].S - ls[j].S);
        sumdist += cur;
    }
    int empty = 0;
    FOR(i,1,n) FOR(j,1,n) if (a[i][j] < 0) ++empty;
    if (empty == 0) return 0.0;
    long double t = cnt * cnt * sumdist / (long double) empty / empty / n / n / n / n;
    return t*t*t*100;
}

bool check(int a[][111]) {
    FOR(i,1,n)
        FOR(j1,1,n) FOR(j2,j1+1,n)
        if (a[i][j1] > 0 && a[i][j2] > 0)
        if (a[i][j1] == a[i][j2]) return false;
    FOR(j,1,n)
        FOR(i1,1,n) FOR(i2,i1+1,n)
        if (a[i1][j] > 0 && a[i2][j] > 0)
        if (a[i1][j] == a[i2][j]) return false;
    return true;
}

int main() {
    spoj_init();
    // Read & check input file
    spoj_assert(fscanf(spoj_p_in, "%d", &n) == 1);
    spoj_assert(1 <= n && n <= MAXN);
    FOR(i,1,n) FOR(j,1,n) {
        spoj_assert(fscanf(spoj_p_in, "%d", &a[i][j]) == 1);
        spoj_assert(a[i][j] == -1 || (1 <= a[i][j] && a[i][j] <= n));
    }
    
    // Read & check output file
    FOR(i,1,n) FOR(j,1,n) {
        spoj_assert(fscanf(spoj_t_out, "%d", &b[i][j]) == 1);
        spoj_assert(b[i][j] == -1 || (1 <= b[i][j] && b[i][j] <= n));
        spoj_assert(a[i][j] < 0 || a[i][j] == b[i][j]);
    }
    
    // Check validity of boards
    spoj_assert(check(a));
    spoj_assert(check(b));
    
    // Get score
    fprintf(spoj_score, "%.5lf\n", (double)getScore());
    return 0;
}
