#include <spoj.h>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
using namespace std;

/*
FILE *spoj_p_in, *spoj_p_out, *spoj_t_out, *spoj_score;
#define PIN "input.txt"
#define POUT "answer.txt"
#define TOUT "output.txt"
#define SCORE "result.txt"

void spoj_init()
{
	spoj_p_in=fopen(PIN, "r");
	spoj_p_out=fopen(POUT, "r");
	spoj_t_out=fopen(TOUT, "r");
	spoj_score=fopen(SCORE, "w");
}

#define spoj_assert assert
*/

int main() {
	spoj_init();

	int c[111111];
	int m;
	memset(c, 0, sizeof(c));
	
	fscanf(spoj_p_out, "%d", &m);
	for (int i = 0; i < m; i++) {
		int x;
		fscanf(spoj_p_out, "%d", &x);
		c[x]++;
	}
	
	spoj_assert(fscanf(spoj_t_out, "%d", &m)==1);
	for (int i = 0; i < m; i++) {
		int x;
		spoj_assert(fscanf(spoj_t_out, "%d", &x) == 1);
		c[x]--;
	}
	
	for (int i = 0; i < 111111; i++) 
		spoj_assert(c[i] == 0);
		
	int score = 2;
	
	double ans, out;
	ans = out = -1;
	fscanf(spoj_p_out, "%lf", &ans);
	fscanf(spoj_t_out, "%lf", &out);
	if (abs(ans - out) < 0.000001) score+=2;
	
	fprintf(spoj_score, "%d", score);
	
	return 0;
}
