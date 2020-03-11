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
#define PIN "input.txt"
#define TOUT "wrong2.txt"
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
		
	int row[5], column[5], a[5][5];
	for (int i = 0; i < 5; i++) 
		fscanf(spoj_p_in, "%d", &row[i]);
	for (int i = 0; i < 5; i++) 
		fscanf(spoj_p_in, "%d", &column[i]);

	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++) 
			spoj_assert(fscanf(spoj_t_out, "%d", &a[i][j]) == 1);
		
	for (int i = 0; i < 5; i++) 
		for (int j = 0; j < 5; j++) 
			spoj_assert(((1<=a[j][j])&&(a[i][j]<=25)));
			
	for (int i = 0; i < 5; i++) {
		int sum = 0;
		for (int j = 0; j < 5; j++) sum += a[i][j];
		spoj_assert(sum == row[i]);
	}	
	
	for (int j = 0; j < 5; j++) {
		int sum = 0;
		for (int i = 0; i < 5; i++) sum += a[i][j];		
		spoj_assert(sum == column[j]);
	}
	
	fprintf(spoj_score, "5");
	
	return 0;
}
