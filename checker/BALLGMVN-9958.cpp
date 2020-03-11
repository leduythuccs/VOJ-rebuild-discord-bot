#include "spoj.h"
/*
	spoj_p_in: input
	spoj_p_out: output
	spoj_t_out: user's output
	spoj_score: score
*/

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <string>
#include <cmath>
#include <cassert>
#include <ctime>
#include <utility>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <sstream>
#define FOR(a,b,c) for (int a=b,_c=c;a<=_c;a++)
#define FORD(a,b,c) for (int a=b;a>=c;a--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; ++i)
#define REPD(i,a) for(int i=(a)-1; i>=0; --i)
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define sz(a) int(a.size())
#define reset(a,b) memset(a,b,sizeof(a))

using namespace std;
/*
FILE *spoj_p_in, *spoj_p_out, *spoj_t_out, *spoj_score;
#define PIN "19.in"
#define POUT "19.out"
#define TOUT "a.out"
#define SCORE "score.txt"

void spoj_init()
{
	spoj_p_in=fopen(PIN,"r");
	spoj_p_out=fopen(POUT, "r");
	spoj_t_out=fopen(TOUT, "r");
	spoj_score=fopen(SCORE, "w");
}

void spoj_assert(bool t)
{
    assert(t);
}
*/

int n, res;
pair<int, int> p[2222];

bool check(pair<int, int> a, pair<int, int> b, pair<int, int> c) {
    b.first -= a.first;
    b.second -= a.second;

    c.first -= a.first;
    c.second -= a.second;

    long long res = (long long) b.first * c.second - (long long) b.second * c.first;

    return res == 0;
}

int main(){
    spoj_init();

    //judger input
    fscanf(spoj_p_in, "%d", &n);
    for (int i= 1; i <= 2 * n; i++)
        fscanf(spoj_p_in, "%d%d", &p[i].first, &p[i].second);

    //judger output
    fscanf(spoj_p_out, "%d", &res);

    //user output
    int userRes;
    spoj_assert (fscanf(spoj_t_out, "%d", &userRes) == 1);

    if (userRes == -1) {
        assert(res == -1);
        fprintf(spoj_score, "1");
        return 0;
    }

    assert(res != -1);
    int a = userRes, b, c;
    spoj_assert (fscanf(spoj_t_out, "%d", &b) == 1);
    spoj_assert (fscanf(spoj_t_out, "%d", &c) == 1);

    spoj_assert(1 <= a && a <= 2 * n);
    spoj_assert(1 <= b && b <= 2 * n);
    spoj_assert(1 <= c && c <= 2 * n);
    spoj_assert(a != b && b != c && c != a);
    spoj_assert ((a > n) != (b > n) || (b > n) != (c > n));

    spoj_assert(check(p[a], p[b], p[c]));
    //All ok!
    fprintf(spoj_score, "1");
    return 0;
}
