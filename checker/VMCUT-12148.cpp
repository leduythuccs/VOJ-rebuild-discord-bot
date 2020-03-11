#include "spoj.h"
#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;

const int MN = 100111;
struct DSU {
    int lab[MN];
    void init(int n) {
        for(int i = 0; i <= n; ++i)
            lab[i] = -1;
    }

    int getRoot(int u) {
        if (lab[u] < 0) return u;
        return lab[u] = getRoot(lab[u]);
    }

    bool merge(int u, int v) {
        u = getRoot(u); v = getRoot(v);
        if (u == v) return false;
        if (lab[u] > lab[v]) swap(u, v);
        lab[u] += lab[v];
        lab[v] = u;
        return true;
    }
};

int main() {
    spoj_init();

    // input the graph
    int n, m;
    vector<pii> edges;
    fscanf(spoj_p_in, "%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        pii edge;
        fscanf(spoj_p_in, "%d%d", &edge.first, &edge.second);
        edges.push_back(edge);
    }

    // check D(H)
    int dh, t_dh;
    fscanf(spoj_p_out, "%d", &dh);
    spoj_assert(fscanf(spoj_t_out, "%d", &t_dh));

    // check the set H 
    int h_size;
    set<int> h;
    spoj_assert(fscanf(spoj_t_out, "%d", &h_size));
    for (int i = 0; i < h_size; i++) {
        int vertex;
        spoj_assert(fscanf(spoj_t_out, "%d", &vertex));
        
        // verify whether the user vertex is correct 
        spoj_assert(1 <= vertex && vertex <= n);

        // no vertex appears twice in the list
        spoj_assert(h.find(vertex) == h.end());

        h.insert(vertex);
    }

    if (h.size() > 0) {
        // check H is connected
        DSU dsu;
        dsu.init(n);
        for (int i = 0; i < m; ++i) {
            int u = edges[i].first, v = edges[i].second;
            if (h.count(u) && h.count(v))
                dsu.merge(u, v);
        }
        int u = *h.begin();
        for (__typeof(h.begin()) it = h.begin(); it != h.end(); ++it) {
            spoj_assert(dsu.getRoot(*it) == dsu.getRoot(u));
        }
    }

    int counter = t_dh;
    for (int i = 0; i < m; i++) {
        if ((h.find(edges[i].first) != h.end() && h.find(edges[i].second) == h.end()) ||
            (h.find(edges[i].second) != h.end() && h.find(edges[i].first) == h.end()))
            counter--;
    }
    // verify whether the set H corresponds to D(H)
    spoj_assert(counter == 0);

    fprintf(spoj_score, "%.2lf", double(t_dh) / dh);

    return 0;
}
