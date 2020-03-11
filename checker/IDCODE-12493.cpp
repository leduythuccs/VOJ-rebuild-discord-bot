#include <bits/stdc++.h>
#include "spoj.h"

const int MAXN = 20002;
const int MAXM = 2000002;

using namespace std;

vector<int> a[MAXN];
vector<int> Q[MAXM];
vector<pair<int, int> > E;
int p[MAXN];
int ans[MAXN];
bool done[MAXN];
int n, m;

bool isPermutation() {
    vector<int> t (ans + 1, ans + 1 + n);
    sort(t.begin(), t.end());
    for (int i = 0; i < n; ++i) if (t[i] != i + 1) return false;
    return true;
}

bool check() {
    for (int i = 1; i <= n; ++i) a[i].clear();
    for (int i = 0; i < E.size(); ++i) {
        int u = E[i].first;
        int v = E[i].second;
        a[u].push_back(v);
        a[v].push_back(u);
    }
    for (int i = 1; i <= n; ++i) fscanf(spoj_t_out, "%d", &ans[i]);//output >> ans[i];
    spoj_assert(isPermutation());
    for (int i = 1; i <= n; ++i) p[ans[i]] = i;
    for (int i = 1; i <= n; ++i) Q[i].clear();
    for (int i = 1; i <= n; ++i) done[i] = false;
    Q[p[1]].push_back(0);
    for (int it = 1; it <= n; ++it) {
        for (int i = 1; i <= n; ++i) if (!done[p[i]] && !Q[p[i]].empty()) {
            int u = p[i];
            done[u] = true;
            for (int j = 0; j < a[u].size(); ++j) {
                int v = a[u][j];
                if (!done[v]) {
                    Q[v].push_back(i);
                }
            }
            break;
        }
    }
    for (int i = 2; i <= n; ++i) if (Q[p[i]] < Q[p[i - 1]]) return false;
    return true;
}

int main() {
    spoj_init();
    fscanf(spoj_p_in, "%d %d", &n, &m);
    E.resize(m);
    for (int i = 0; i < m; ++i)
        fscanf(spoj_p_in, "%d %d", &E[i].first, &E[i].second);
    spoj_assert(check());
    return 0;
}
