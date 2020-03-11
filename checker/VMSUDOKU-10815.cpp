#include "spoj.h"

#include <cstring>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
using namespace std;

string a[11];
char tmp[111];

bool row[11][11], col[11][11], cell[4][4][11];

void read_input() {
    for(int i = 0; i < 9; ++i) {
        spoj_assert(fscanf(spoj_t_out, "%s\n", &tmp[0]) == 1);
        spoj_assert(strlen(tmp) == 9);

        for(int j = 0; j < 9; ++j) {
            spoj_assert(tmp[j] >= '1' && tmp[j] <= '9');
        }

        a[i] = string(tmp);

        cerr << a[i] << endl;
    }

    for(int i = 0; i < 9; ++i)
        for(int j = 0; j < 9; ++j) {
            int cur = a[i][j] - '0';

            spoj_assert(row[i][cur] == false);
            spoj_assert(col[j][cur] == false);
            spoj_assert(cell[i/3][j/3][cur] == false);

            row[i][cur] = true;
            col[j][cur] = true;
            cell[i/3][j/3][cur] = true;
        }
}

int main() {
    spoj_init();
    cerr << "Init" << endl;
    read_input();
    cerr << "Done read input" << endl;

    int res = 0;
    for(int t = 1; t <= 9; ++t) {
        for(int i1 = 0; i1 < 9; ++i1)
            for(int j1 = 0; j1 < 9; ++j1)
                if (a[i1][j1] == t + '0')
                    for(int i2 = 0; i2 < 9; ++i2)
                        for(int j2 = 0; j2 < 9; ++j2)
                            if (a[i2][j2] == t + '0')
                                if (make_pair(i1, j1) < make_pair(i2, j2)) {
                                    res += t * abs(i1 - i2) * abs(j1 - j2);
                                }
    }
    fprintf(spoj_score, "%d\n", max(0, res - 17000));
    cerr << res << endl;
}
