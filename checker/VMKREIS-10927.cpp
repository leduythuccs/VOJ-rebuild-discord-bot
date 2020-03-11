#include "spoj_interactive.h"
#include <cassert>
#include <cstdio>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
using namespace std;


/*FILE *spoj_p_in, *spoj_p_out, *spoj_t_out, *spoj_score, *spoj_for_tested;
#define PIN "input.txt"
#define POUT "output.txt"
#define TOUT "wrong2.txt"
#define SCORE "result.txt"

void spoj_init()	{
	spoj_p_in=fopen(PIN, "r");		
	spoj_p_out=fopen(POUT, "r");
	spoj_t_out=fopen(TOUT, "r");	
	spoj_score=fopen(SCORE, "w");
}

#define spoj_assert assert
#define spoj_scanf			scan
#define spoj_printf			printf
#define	SPOJ_RV_AC			0
#define SPOJ_RV_WA			1
#define spoj_for_tested		stdout	*/

double	w,	h,	r,	x,	y;
double	xr,	yr,	rr,	score;
int		ext,	mode,	count;
bool	rep;

double sqr(double x)	{
	return x*x;
}

int main(){
	spoj_init();
	fscanf(spoj_p_in,"%lf %lf %d",&w,&h,&ext);		//read input
	fscanf(spoj_p_out,"%lf %lf %lf",&x,&y,&r);		//read output
	count=0;
	score=5;
	
	//fscanf(spoj_t_out,"%d",&mode);
	spoj_scanf("%d",&mode);
	//fscanf(spoj_t_out,"%lf %lf %lf",&xr,&yr,&rr);
	//spoj_assert(abs(xr-x)<=0.01 && abs(yr-y)<=0.01 && abs(rr-r)<=0.01);
	if (count <= ext) score=5;
	else if (count <= 2*ext) score = (double)5* (1-(score-ext)/100);
		else score=0;
	fprintf(spoj_score, "%.2lf\n",score);		
	return SPOJ_RV_AC;
}
