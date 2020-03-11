#include <spoj.h>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <sstream>
#include <map>
using namespace std;


/*FILE *spoj_p_in, *spoj_p_out, *spoj_t_out, *spoj_score;
#define PIN "Test\\input25.txt"
#define POUT "Test\\output25.txt"
#define TOUT "output.txt"
#define SCORE "result.txt"

void spoj_init()
{
	spoj_p_in=fopen(PIN, "r");
	spoj_p_out=fopen(POUT, "r");
	spoj_t_out=fopen(TOUT, "r");
	spoj_score=fopen(SCORE, "w");
}

#define spoj_assert assert*/

#define MAXN 1010

int n, m, solutionLen, expectedLen;
vector <int> out;
bool e[MAXN][MAXN], exist[MAXN];

int main() {
	spoj_init();

    spoj_assert(fscanf(spoj_p_in, "%d%d", &n, &m) == 2);
    for (int i = 0; i < m; i++) {
        int u, v;
        spoj_assert(fscanf(spoj_p_in, "%d%d", &u, &v) == 2);
        e[u][v] = true;
        e[v][u] = true;
    }
    spoj_assert(fscanf(spoj_t_out, "%d\n", &solutionLen));
    char tmp[20001];
    spoj_assert(fgets(tmp, 10000, spoj_t_out) != NULL);
    string s = tmp;
    stringstream ss(s);
    int cur;
    while (ss >> cur) {
        out.push_back(cur);
        spoj_assert(exist[cur] == false);
        exist[cur] = true;
        spoj_assert(cur >= 1 && cur <= n);
    }
    spoj_assert(solutionLen == out.size());
    for (int i = 0; i + 1 < out.size(); i++)
        spoj_assert(e[out[i]][out[i + 1]] == true);

    fscanf(spoj_p_out, "%d", &expectedLen);

    double ratio = solutionLen * 1.0 / expectedLen;
    double point;
    if (ratio < 0.8)
        point = pow(100.0, ratio);
    else
    if (ratio <= 1)
        point = 40 + pow(60.0, (ratio - 0.8) / 0.2);
    else
        point = 100 + pow(100.0, ratio / 3.0);
    fprintf(spoj_score, "%0.6lf", point);
    //cout << point << endl;

    return 0;
}
