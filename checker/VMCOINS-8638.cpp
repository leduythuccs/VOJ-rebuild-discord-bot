#include <spoj.h>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <set>
using namespace std;

/*
FILE *spoj_p_in, *spoj_t_out, *spoj_score;
#define PIN "input.txt"
#define TOUT "output.txt"
#define SCORE "result.txt"

void spoj_init()
{
    spoj_p_in=fopen(PIN, "r");
    spoj_t_out=fopen(TOUT, "r");
    spoj_score=fopen(SCORE, "w");
}

#define spoj_assert assert
*/

const int MN = 100111;

int n, k;
pair<int,int> a[MN], b[MN];
set< pair<int,int> > cur;

const int di[] = {-1,1,0,0};
const int dj[] = {0,0,-1,1};

int main() {
    spoj_init();

    // Read input file
    fscanf(spoj_p_in, "%d", &n);

    // Read start configuration
    for(int i = 0; i < n; ++i) {
        fscanf(spoj_p_in, "%d%d", &a[i].first, &a[i].second);
        cur.insert(a[i]);
    }

    // Read target configuration
    for(int i = 0; i < n; ++i)
        fscanf(spoj_p_in, "%d%d", &b[i].first, &b[i].second);


    // Read output file & process
    spoj_assert(fscanf(spoj_t_out, "%d", &k) == 1);
    spoj_assert(k >= 0 && k <= 1000000);

    while (k--) {
        int x, y, u, v;
        spoj_assert(fscanf(spoj_t_out, "%d%d%d%d", &x, &y, &u, &v) == 4);

        // Position (x, y) must have a coin
        spoj_assert(cur.find(make_pair(x, y)) != cur.end());

        // Position (u, v) must not have a coin
        spoj_assert(cur.find(make_pair(u, v)) == cur.end());

        // Take coin from (x, y)
        cur.erase(make_pair(x, y));
        int cnt = 0;

        for(int dir = 0; dir < 4; ++dir) {
            int uu = u + di[dir], vv = v + dj[dir];
            if (cur.find(make_pair(uu, vv)) != cur.end()) ++cnt;
        }

        // New position must be adjacent to at least 2 coins
        spoj_assert(cnt >= 2);

        // Put coin to new position
        cur.insert(make_pair(u, v));
    }

    // Check final configuration
    for(int i = 0; i < n; ++i)
        spoj_assert(cur.find(b[i]) != cur.end());

    fprintf(spoj_score, "5");
    
    return 0;
}
