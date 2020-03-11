#include <spoj.h>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
using namespace std;

/*
FILE *spoj_p_in, *spoj_t_out, *spoj_score;
#define PIN "1.in"
#define TOUT "ac.txt"
#define SCORE "result.txt"

void spoj_init()
{
	spoj_p_in=fopen(PIN, "r");
	spoj_t_out=fopen(TOUT, "r");
	spoj_score=fopen(SCORE, "w");
}

#define spoj_assert assert
*/

int main() {
	spoj_init();
	
	int c[222][222];
	char s[222];
	int n, m;
	memset(c, 0, sizeof(c));
	
	fscanf(spoj_p_in, "%d%d", &n, &m);
	for (int i = 0; i < m; i++) {
		int u, v;
		fscanf(spoj_p_in, "%d%d", &u, &v);
		c[u][v] = c[v][u] = 1;
	}
	
	for (int i = 1; i <= n; i++) {
		spoj_assert(fscanf(spoj_t_out, "%c", &s[i]) == 1);
		spoj_assert('1' <= s[i] && s[i] <= '3');		
	}
	
	for (int i = 1; i <= n; i++)
	for (int j = 1; j <= n; j++) if (c[i][j] == 1) 
		spoj_assert(s[i] != s[j]);
	
	int cnt[5];
	memset(cnt, 0, sizeof(cnt));
	for (int i = 1; i <= n; i++) cnt[s[i] - '0']++;
	spoj_assert(cnt[1] > 0 && cnt[2] > 0 && cnt[3] > 0);
	
	fprintf(spoj_score, "5");
	
	return 0;
}
