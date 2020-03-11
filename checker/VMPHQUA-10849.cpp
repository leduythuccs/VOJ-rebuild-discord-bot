#include "spoj.h"

#include <set>
#include <map>
#include <list>
#include <cmath>
#include <queue>
#include <stack>
#include <cstdio>
#include <string>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <complex>
#include <iostream>
#include <algorithm>

#include <ctime>
#include <deque>
#include <bitset>
#include <cctype>
#include <utility>
#include <cassert>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

const int MAXN = 500;
const int MAXV = 50;
const int MAXD = 40000;
const int MAXX = 10000;

int n, v, c;
int d[MAXN + 11];
double x[MAXN + 11], y[MAXN + 11], Y, X;
bool marked[MAXN + 11];

inline double sqr(double x) { return x*x; }

void readInput() {
    spoj_assert(fscanf(spoj_p_in, "%d%d%d", &n, &v, &c) == 3);
    spoj_assert(1 <= n && n <= MAXN);
    spoj_assert(1 <= v && v <= MAXV);
    spoj_assert(1 <= c && c <= MAXD);

    for(int i = 0; i < n; ++i) {
        spoj_assert(fscanf(spoj_p_in, "%d%lf%lf", &d[i], &x[i], &y[i]) == 3);
        if (i == 0) {
            spoj_assert(d[i] == 0);
        } else {
            spoj_assert(d[i] > 0 && d[i] <= MAXD);
        }
        spoj_assert(-MAXX <= x[i] && x[i] <= MAXX);
        spoj_assert(-MAXX <= y[i] && y[i] <= MAXX);
    }
}

void readOutput() {
    X = 0;
    for(int i = 0; i < v; ++i) {
        int u;
        spoj_assert(fscanf(spoj_t_out, "%d", &u) == 1);
        spoj_assert(u == 0);

        vector<int> cur; cur.push_back(u);
        spoj_assert(fscanf(spoj_t_out, "%d", &u) == 1);

        while (u) {
            cur.push_back(u);
            spoj_assert(fscanf(spoj_t_out, "%d", &u) == 1);
        }
        cur.push_back(u);

        // PR0(cur, cur.size());

        REP(t, cur.size() - 1) {
            int u = cur[t], v = cur[t+1];
            X += sqrt(sqr(x[u] - x[v]) + sqr(y[u] - y[v]));
        }

        // Check if every point visit <= 1 time
        int sum = 0;
        FOR(t,1,cur.size()-2) {
            spoj_assert(marked[cur[t]] == false);
            marked[cur[t]] = true;

            sum += d[cur[t]];
        }
        spoj_assert(sum <= c);
    }

    // Check if every point visit >= 1 time
    for(int i = 1; i < n; ++i) {
        spoj_assert(marked[i]);
    }
    // DEBUG(X);
}

void readOptimal() {
    spoj_assert(fscanf(spoj_p_out, "%lf", &Y) == 1);
    // DEBUG(Y);
}

int main() {
    spoj_init();
    readInput();
    readOutput();
    readOptimal();

    fprintf(spoj_score, "%.4lf\n", min(Y / X, 3.0));
}
