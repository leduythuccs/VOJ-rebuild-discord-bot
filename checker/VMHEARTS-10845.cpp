#include "spoj.h"
#include <cstring>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
using namespace std;

char tmp[100100];
int main() {
    spoj_init();

    cerr << "Read input" << endl;
    spoj_assert(fscanf(spoj_t_out, "%s", &tmp[0]) == 1);
    string predicted = string(tmp);
    spoj_assert(fscanf(spoj_p_out, "%s", &tmp[0]) == 1);
    string expected = string(tmp);
    cerr << "Done read input" << endl;

    cerr << "Compute score" << endl;
    spoj_assert(predicted.length() == 20000);
    spoj_assert(expected.length() == 20000);
    double score = 0.0;
    for (int i = 0; i < 20000; i++) {
        spoj_assert(predicted[i] >= '1' && predicted[i] <= '4');
        if (predicted[i] == expected[i]) {
            score++;
        }
    }
    cerr << "Done compute score" << endl;

    score /= 200;
    fprintf(spoj_score, "%.2lf\n", score);
    cerr << score << endl;
}