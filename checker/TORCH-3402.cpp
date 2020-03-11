#include <spoj.h>
//#include <cassert>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

/*
FILE *spoj_p_in, *spoj_p_out, *spoj_t_out, *spoj_score;
#define PIN "in.txt"
#define POUT "ans.txt"
#define TOUT "out.txt"
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
double expectedResult;
double result;
int n;
double x[111], y[111];
int p[111];

int main()
{
	spoj_init();
	//Doc ans
	fscanf(spoj_p_out, "%lf", &expectedResult);
	//Doc in
	fscanf(spoj_p_in, "%d", &n);
	for (int i = 1; i <= n; i++) fscanf(spoj_p_in, "%lf%lf", &x[i], &y[i]);
	
	spoj_assert( fscanf(spoj_t_out, "%lf", &result) == 1);
	for (int i = 1; i <= n; i++) 
		spoj_assert( fscanf(spoj_t_out, "%d", &p[i]) );
	for (int i = 1; i <= n; i++)
		for (int j = i + 1; j <= n; j++) spoj_assert(p[i] != p[j]);
	spoj_assert(p[1] == 1);
	p[n + 1] = 1;
	for (int i = 1; i <= n; i++)
		spoj_assert(1 <= p[i] && p[i] <= n);
	
	double s = 0;
	for (int i = 1; i <= n; i++) {
		int u = p[i];
		int v = p[i + 1];
		s += pow(pow(x[u] - x[v], 2) + pow(y[u] - y[v], 2), 0.5);
	}
	spoj_assert(abs(s - result) <= 0.0005);
	if (s <= expectedResult + 1e-4) {
		fprintf(spoj_score, "10");
	} else {
		if (result > expectedResult * 1.5) fprintf(spoj_score, "0");
		else {
			double score = 9 - pow(1.5, ((result - expectedResult) / 25));
			if (score < 0) score = 0;

			fprintf(spoj_score, "%0.6lf", score);
		}
	}
	return 0;
}
