#include <spoj.h>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <iomanip>
#include <bitset>
#include <complex>

#define FOR(i,a,b) for(int i = (a), _b=(b); i <= _b; ++i)
#define MP make_pair
#define PB push_back

using namespace std;

//#define RR

#ifdef RR
FILE *spoj_p_in, *spoj_p_out, *spoj_t_out, *spoj_score;
#define PIN "0.in"
#define TOUT "output.txt"
#define SCORE "result.txt"

void spoj_init()
{
    spoj_p_in=fopen(PIN, "r");
    //spoj_p_out=fopen(POUT, "r");
    spoj_t_out=fopen(TOUT, "r");
    spoj_score=fopen(SCORE, "w");
}

#define spoj_assert assert
#endif

int n;

int min_left(int n) {
    if (n % 3 == 0) return 2;
    else return 1;
}

set< pair<int,int> > s;

int main() {
    spoj_init();

    // Read number of test
    int ntest;
    fscanf(spoj_p_in, "%d", &ntest);

    // Initialize total score
    double score = 0.0;

    while (ntest--) {
        // Initialize board
        fscanf(spoj_p_in, "%d", &n);
        s.clear();
        FOR(i,1,n) FOR(j,1,n) s.insert(MP(i,j));

        // Read student's move sequence
        int want;
        if (fscanf(spoj_t_out, "%d", &want) != 1) {
            break;
        }

        bool ok = true;
        FOR(i,1,want) {
            // Move from (u0, v0) to (u2, v2) through (u1, v1)
            int u0, v0, u1, v1, u2, v2;
            if (fscanf(spoj_t_out, "%d%d%d%d", &u0, &v0, &u2, &v2) != 4) {
                ok = false;
                break;
            }
            u1 = (u0 + u2) / 2;
            v1 = (v0 + v2) / 2;

            // Check states of (u0, v0), (u1, v1) and (u2, v2)
            if (s.find(MP(u0,v0)) == s.end()) {
                ok = false;
            }
            if (s.find(MP(u1, v1)) == s.end()) {
                ok = false;
            }
            if (s.find(MP(u2, v2)) != s.end()) {
                ok = false;
            }

            // Switch to new state
            if (!ok) continue;
            s.erase(MP(u0, v0));
            s.erase(MP(u1, v1));
            s.insert(MP(u2, v2));
        }
        if (ok) {
            int can = n*n - min_left(n);
            long double t = want / (long double) can;
            if (want == can) score += 1;
            else score += 0.7 * t * t * t;
        }
    }

    // Output total score
    fprintf(spoj_score, "%.5lf", score);
    return 0;
}
 