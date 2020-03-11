#include "spoj.h"

#include <iostream>
#include <vector>

using namespace std;

/*
FILE *spoj_p_in, *spoj_p_out, *spoj_t_out, *spoj_score;

#define PIN "i.in"
#define POUT "a.ans"
#define TOUT "o.out"
#define SCORE "p.txt"
#define spoj_assert assert

void spoj_init(){
    spoj_p_in = fopen(PIN, "r");
    spoj_p_out = fopen(POUT, "r");
    spoj_t_out = fopen(TOUT, "r");
    spoj_score = fopen(SCORE, "w");
}
*/

#define MAXN 30002

typedef pair<int, double> PID;

int n, m, k, p, d, q = 0;
double r[MAXN], pp, pd, point = 0.0, ans;
vector<int> t[MAXN];
vector<PID> tower;

int main() {
    spoj_init();

    fscanf(spoj_p_out, "%lf", &ans);

    fscanf(spoj_p_in, "%d%d%d%d%d", &n, &m, &k, &p, &d);

    pp = (double)p / 100;
    pd = (double)d / 100 + 1.0;

    for (int i = 1; i <= n; i++) fscanf(spoj_p_in, "%lf", &r[i]);

    for (int i = 1; i <= m; i++) {
        int h;
        fscanf(spoj_p_in, "%d", &h);
        q += h;
        while (h--) {
            int id;
            fscanf(spoj_p_in, "%d", &id);
            t[i].push_back(id);
        }
    }

    for (int kkk = 0; kkk < k; kkk++) {
        int l, i;
        double addpoint;
        spoj_assert(fscanf(spoj_t_out, "%d", &l));
        spoj_assert(1 <= l && l <= m);
        spoj_assert(t[l].size());

        i = t[l].back();

        if (tower.empty() || ((PID)tower.back()).first != i) addpoint = r[i];
        else addpoint = ((PID)tower.back()).second * pd;

        if (t[l].size() <= t[l - 1].size() || t[l].size() <= t[l + 1].size()) addpoint *= pp;

        t[l].pop_back();
        tower.push_back(PID(i, addpoint));
        point += addpoint;
    }

    double heso = (double)1 / 1000000 * k * m;
    fprintf(spoj_score, "%lf\n", point / ans * heso);

    return 0;
}
