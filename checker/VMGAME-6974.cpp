#include "spoj_interactive.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <cmath>
#include <ctime>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <stack>

#define FOR(i,a,b) for(int i=(a); i <= (b); ++i)
#define FORD(i,a,b) for(int i=(a); i >= (b); --i)
#define REP(i,a) FOR(i,0,(a)-1)
#define PB push_back
#define MP make_pair
#define F first
#define S second
using namespace std;

int n;
int a[111][111], row[111], col[111];
bool used[111];

void readInput() {
	fprintf(spoj_p_info, "ReadInput\n");
	fscanf(spoj_p_in, "%d", &n);
	FOR(i,1,n) FOR(j,1,n) {
		fscanf(spoj_p_in, "%d", &a[i][j]);
		row[i] += a[i][j];
		col[j] += a[i][j];
	}
	fprintf(spoj_p_info, "n = %d\n", n);
}

void writeInput() {
	fprintf(spoj_p_info, "WriteInput\n");
	spoj_printf("%d\n", n);
	FOR(i,1,n) {
		FOR(j,1,n) spoj_printf("%d ", a[i][j]);
		spoj_printf("\n", 0);
	}
	fflush(spoj_for_tested);
}

int main() {
	spoj_init();
	
	int score = 10;
	readInput();
	writeInput();

	FOR(turn,1,n) {
		int best = -1;
		FOR(i,1,n) if (!used[i]) {
			if (best == -1) best = i;
			if (row[i] + col[i] > row[best] + col[best]) best = i;
		}
		used[best] = true;
		if (turn <= 10) {
			fprintf(spoj_p_info, "best move = %d\n", best);
		}

		if (turn % 2 == 1) {
			int move;
			spoj_scanf("%d", &move);
			if (move != best) {
				score = 0;
			}
		}
		else {
			spoj_printf("%d\n", best);
			fflush(spoj_for_tested);
		}
	}

	fprintf(spoj_score, "%d\n", score);
	return SPOJ_RV_AC;
}
