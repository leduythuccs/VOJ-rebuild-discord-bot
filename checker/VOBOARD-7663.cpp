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
using namespace std;

const int MAXN = 100;
const double MAX_SCORE = 2.5;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)

#include <spoj.h>

/*
#include <cassert>
FILE *spoj_p_in, *spoj_t_out, *spoj_score, *spoj_p_out;
#define PIN "1.in"
#define POUT "1.out"
#define TOUT "output.txt"
#define SCORE "result.txt"

void spoj_init() {
    spoj_p_in = fopen(PIN, "r");
    spoj_p_out = fopen(POUT, "r");
    spoj_t_out = fopen(TOUT, "r");
    spoj_score = fopen(SCORE, "w");
}
#define spoj_assert assert
*/

int m, n, k, a[1011][1011], row[1011], col[1011];


void read_input() {
    spoj_assert(fscanf(spoj_p_in, "%d %d %d\n", &m, &n, &k) == 3);
    spoj_assert(m >= 1 && m <= 1000 && n >= 1 && n <= 1000);

    FOR(i,1,m) FOR(j,1,n) {
        spoj_assert(fscanf(spoj_p_in, "%d", &a[i][j]) == 1);
        spoj_assert(a[i][j] >= 0 && a[i][j] < k);
    }
}

void read_output() {
    long long best;
    fscanf(spoj_p_out, "%lld", &best);

    long long res;
    fscanf(spoj_t_out, "%lld", &res);

    spoj_assert(res == best);

    long long sum = 0;
    FOR(i,1,m) {
        fscanf(spoj_t_out, "%d", &row[i]);
        sum += row[i];
    }
    FOR(j,1,n) {
        fscanf(spoj_t_out, "%d", &col[j]);
        sum += col[j];
    }

    spoj_assert(sum == res);

    FOR(i,1,m) FOR(j,1,n)
        spoj_assert((a[i][j] + row[i] + col[j]) % k == 0);
}

int main() {
    spoj_init();

    read_input();
    read_output();

    fprintf(spoj_score, "10");
    return 0;
}
