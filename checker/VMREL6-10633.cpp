#include <spoj.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <cstdio>
#include <cassert>
using namespace std;

int a[111], c[111][111], n, ln, solution;

void readSol() {
    fscanf(spoj_p_out, "%d", &solution);
}

void readSequence() {
    spoj_assert(fscanf(spoj_t_out, "%d", &ln) == 1);
    cerr << "OK: output = expected answer" << endl;
    spoj_assert(ln == solution);
    for(int i = 0; i < n; ++i)
        spoj_assert(fscanf(spoj_t_out, "%d", &a[i]) == 1);

    cerr << "OK: Can read all output" << endl;
}

void readBoard() {
    spoj_assert(fscanf(spoj_p_in, "%d", &n) == 1);
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j)
            spoj_assert(fscanf(spoj_p_in, "%d", &c[i][j]) == 1);
}

bool check() {
    spoj_assert(ln == *max_element(a, a+n));

    cerr << "OK: max value = true max" << endl;

    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j) {
            switch (c[i][j]) {
                case 0:
                    spoj_assert(a[i] == a[j]);
                    break;
                case 1:
                    spoj_assert(a[i] < a[j]);
                    break;
                case 2:
                    spoj_assert(a[i] <= a[j]);
                    break;
                case -1:
                    spoj_assert(a[i] > a[j]);
                    break;
                case -2:
                    spoj_assert(a[i] >= a[j]);
                    break;
            }
        }
    cerr << "OK: all conditions satisfy" << endl;
    return true;
}

int main() {
    spoj_init();
    readSol();
    readBoard();
    readSequence();
    if (check()) {
        fprintf(spoj_score, "100");
    } else {
        fprintf(spoj_score, "0");
    }
    return 0;
}
