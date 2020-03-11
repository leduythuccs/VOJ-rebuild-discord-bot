#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <string>
#include <deque>
#include <complex>
#include <sstream>
#include <iomanip>
using namespace std;

const int MAXN = 100;
const double MAX_SCORE = 2.5;


#include <spoj.h>
/*
#include <cassert>
FILE *spoj_p_in, *spoj_t_out, *spoj_score;
#define PIN "10.in"
#define TOUT "10.out"
#define SCORE "result.txt"

void spoj_init() {
    spoj_p_in = fopen(PIN, "r");
    spoj_t_out = fopen(TOUT, "r");
    spoj_score = fopen(SCORE, "w");
}
#define spoj_assert assert
*/
int nRow, nCol;
vector<int> row[MAXN], col[MAXN];
string solution[MAXN];

bool equal(vector<int> a, vector<int> b) {
    if (a.size() != b.size()) return false;

    for(int i = 0; i < a.size(); i++) {
        if (a[i] != b[i]) return false;
    }
    return true;
}

int get() {
    for(int i = 1; i <= nRow; i++)
    if (solution[i].length() != nCol + 1) return 0;

    for(int i = 1; i <= nRow; i++) {
        for(int j = 1; j <= nCol; j++)
        if (solution[i][j] < '0' || solution[i][j] > '1') return 0;
    }

    int res = 0;

    for(int i = 1; i <= nRow; i++) {
        string now = solution[i];
        for(int x = 0; x < now.length(); x++)
        if (now[x] == '0') now[x] = ' ';
        istringstream sin(now);
        vector<int> cur;
        string u;
        while (sin >> u) {
            cur.push_back(u.length());
        }
        if (equal(cur, row[i])) res++;
    }

    for(int j = 1; j <= nCol; j++) {
        string now = "";
        for(int i = 1; i <= nRow; i++)
            now = now + solution[i][j];
        for(int x = 0; x < now.length(); x++) 
        if (now[x] == '0') now[x] = ' ';
        istringstream sin(now);
        vector<int> cur;
        string u;
        while (sin >> u) {
            cur.push_back(u.length());
        }
        if (equal(cur, col[j])) res++;
    }
    return res;
}

void read_input() {
    fscanf(spoj_p_in, "%d %d", &nRow, &nCol);
    spoj_assert(nRow >= 1 && nCol >= 1 && nRow < MAXN && nCol < MAXN);
    
    if (nRow != nCol) {
        cout << "Warning: Number of row != number of column";
    }
    
    int sumRow = 0, sumCol = 0;
    for(int i = 1; i <= nRow; i++) {
        int k;
        fscanf(spoj_p_in, "%d", &k);
        while (k--) {
            int u;
            fscanf(spoj_p_in, "%d", &u);
            row[i].push_back(u);
            sumRow += u;
        }
    }

    for(int j = 1; j <= nCol; j++) {
        int k;
        fscanf(spoj_p_in, "%d", &k);
        while (k--) {
            int u;
            fscanf(spoj_p_in, "%d", &u);
            col[j].push_back(u);
            sumCol += u;
        }
    }
    
    spoj_assert(sumRow == sumCol);
}

void read_output() {
    for(int i = 1; i <= nRow; i++) {
        char tmp[211];
        fscanf(spoj_t_out, "%s\n", &tmp);
        spoj_assert(strlen(tmp) == nCol);
        solution[i] = " ";

        for(int x = 0; x < strlen(tmp); x++) {
            spoj_assert(tmp[x] == '0' || tmp[x] == '1');
            solution[i] += tmp[x];
        }
    }
}

int main() {
    spoj_init();

    read_input();
    read_output();

    int result = get();
    if (result <= max(nRow, nCol)) fprintf(spoj_score, "0");
    else if (result == nRow + nCol) fprintf(spoj_score, "%0.6lf", MAX_SCORE);
    else fprintf(spoj_score, "%0.6lf", (result * 1.0 - max(nRow, nCol)) / (nRow + nCol - max(nRow, nCol)) * (MAX_SCORE - 0.5) + 0.5);
    return 0;
}
