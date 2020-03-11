#define sqr(x) ((x) * (x))

#include <spoj.h>
//#include <cassert>
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <set>
using namespace std;

/*
FILE *spoj_p_in, *spoj_t_out, *spoj_p_out;
#define PIN "in.txt"
#define TOUT "out.txt"
#define POUT "ans.txt"
#define spoj_assert assert

void spoj_init()
{
	spoj_p_in=fopen(PIN, "r");
	spoj_t_out=fopen(TOUT, "r");
	spoj_p_out=fopen(POUT, "r");
}
*/

int cx[333];
int cy[333];
int ax[333];
int ay[333];
int m, n;
int expected;
int result;
int connect[333];
int cnt[333];

void read_in() {
	fscanf(spoj_p_in, "%d%d", &m, &n);
	for (int i = 1; i <= m; i++) {
		fscanf(spoj_p_in, "%d%d", &ax[i], &ay[i]);
	}
	for (int i = 1; i <= n; i++) {
		fscanf(spoj_p_in, "%d%d", &cx[i], &cy[i]);
	}
}

void read_ans() {
	fscanf(spoj_p_out, "%d", &expected);
}

void read_out() {
	spoj_assert(fscanf(spoj_t_out, "%d", &result) == 1);
	for (int i = 1; i <= n; i++) {
		spoj_assert(fscanf(spoj_t_out, "%d", &connect[i]) == 1);
	}
}

int main() {
	spoj_init();
	read_in();	
	read_ans();
	read_out();
	spoj_assert(expected == result);
	for (int i = 1; i <= n; i++) 
		spoj_assert(1 <= connect[i] && connect[i] <= m);
	for (int i = 1; i <= n; i++) {
		int j = connect[i];
		int s = sqr(cx[i] - ax[j]) + sqr(cy[i] - ay[j]);
		result -= s;
	}
	spoj_assert(result == 0);
	memset(cnt, 0, sizeof(cnt));
	for (int i = 1; i <= n; i++) cnt[connect[i]]++;
	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= m; j++)
			spoj_assert(abs(cnt[i] - cnt[j]) <= 1);
	return 0;
}
