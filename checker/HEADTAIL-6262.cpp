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
FILE *spoj_p_in, *spoj_t_out, *spoj_p_out, *spoj_score;

#define PIN "in.txt"
#define TOUT "out.txt"
#define POUT "ans.txt"
#define SCORE "score.txt"
#define spoj_assert assert

void spoj_init()
{
	spoj_p_in=fopen(PIN, "r");
	spoj_t_out=fopen(TOUT, "r");
	spoj_p_out=fopen(POUT, "r");
	spoj_score=fopen(SCORE, "w");
}
*/

string expected[4];
string output[4];

void read_ans() {
	int t;
	fscanf(spoj_p_out, "%d", &t);
	while (t--) {
		int tmp1;
		char tmp2[10000];
		fscanf(spoj_p_out, "%d", &tmp1);
		fscanf(spoj_p_out, "%s", &tmp2);
		expected[tmp1] = tmp2;
	}
}

void read_out() {
	for (int i = 0; i < 4; i++) output[i] = "#";
	
	int t;
	spoj_assert(fscanf(spoj_t_out, "%d", &t) == 1);
	while (t--) {
		int tmp1;
		char tmp2[10000];
		spoj_assert(fscanf(spoj_t_out, "%d", &tmp1) == 1);
		spoj_assert(fscanf(spoj_t_out, "%s", &tmp2) == 1);
		spoj_assert(output[tmp1] == "#");
		output[tmp1] = tmp2;
	}
}

int main() {
	spoj_init();
	read_ans();
	read_out();
//	cout << expected[1] << " " << expected[2] << endl;
//	cout << output[1] << " " << output[2] << endl;
	int score = 0;
	if (expected[1] == output[1]) score += 4;
	if (expected[2] == output[2]) score += 1;
	
	fprintf(spoj_score, "%d", score);
	return 0;
}
