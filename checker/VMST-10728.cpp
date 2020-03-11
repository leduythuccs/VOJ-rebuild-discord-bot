#include <spoj.h>

#include <iostream>
#include <cstdio>
#include <vector>
#include <cassert>
#include <algorithm>
using namespace std;

int n, m;
bool c[1011][1011];
int lab[1011];

int getRoot(int u) {
    if (lab[u] < 0) return u;
    else return lab[u] = getRoot(lab[u]);
}

void merge(int u, int v) {
    u = getRoot(u);
    v = getRoot(v);

    lab[u] += lab[v];
    lab[v] = u;
}

vector< pair<int,int> > x[3];

void readInput() {
    spoj_assert(fscanf(spoj_p_in, "%d%d", &n, &m) == 2);
    spoj_assert(1 <= n && n <= 1000);
    spoj_assert(1 <= m && m <= 1500 && n <= m);
    while (m--) {
        int u, v;
        spoj_assert(fscanf(spoj_p_in, "%d%d", &u, &v) == 2);
        spoj_assert(1 <= u && u <= n);
        spoj_assert(1 <= v && v <= n);
        spoj_assert(u != v && !c[u][v]);

        c[u][v] = c[v][u] = true;
    }
}

void readOutput() {
    int k;
    // Check exists k and 0 < k <= 3
    spoj_assert(fscanf(spoj_t_out, "%d", &k) == 1);
    spoj_assert(k > 0 && k <= 3);

    for(int turn = 0; turn < k; ++turn) {
        memset(lab, -1, sizeof lab);
        for(int i = 0; i < n-1; ++i) {
            int u, v;
            // Check if edge is valid
            spoj_assert(fscanf(spoj_t_out, "%d%d", &u, &v));
            spoj_assert(1 <= u && u <= n);
            spoj_assert(1 <= v && v <= n);
            spoj_assert(c[u][v]);

            x[turn].push_back(make_pair(min(u, v), max(u, v)));

            // Check if edge does not form cycle
            assert(getRoot(u) != getRoot(v));
            merge(u, v);
        }

        sort(x[turn].begin(), x[turn].end());
    }

    // Check whether no 2 spanning trees are the same
    for(int u = 0; u < k; ++u)
        for(int v = u+1; v < k; ++v) {
            bool equal = true;
            for(int i = 0; i < n-1; ++i)
                equal = equal && (x[u][i] == x[v][i]);
            spoj_assert(!equal);
        }

    if (k == 1) fprintf(spoj_score,      "1\n");
    else if (k == 2) fprintf(spoj_score, "2\n");
    else fprintf(spoj_score, "5\n");
}

int main() {
    spoj_init();
    readInput();
    readOutput();
}


// Master judge: STRATEGY master judge