#include <spoj.h>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
using namespace std;


/*FILE *spoj_p_in, *spoj_p_out, *spoj_t_out, *spoj_score;
#define PIN "input.txt"
#define POUT "output.txt"
#define TOUT "wrong2.txt"
#define SCORE "result.txt"

void spoj_init()
{
	spoj_p_in=fopen(PIN, "r");		
	spoj_p_out=fopen(POUT, "r");
	spoj_t_out=fopen(TOUT, "r");	
	spoj_score=fopen(SCORE, "w");
}

#define spoj_assert assert	*/

#define	foru(i,l,r)		for(int i=l; i<=r; i++)
#define maxn	5000

int		n,	m;
int 	a[maxn],	b[maxn];
bool	selected[maxn];
long long	res;

void read_input_output(){
	fscanf(spoj_p_in,"%d",&n);
	foru(i,1,n)	fscanf(spoj_p_in,"%d",&a[i]);
	
	fscanf(spoj_p_in,"%d",&m);
	foru(i,1,m)	fscanf(spoj_p_in,"%d",&b[i]);
	
	fscanf(spoj_p_out,"%lld",&res);
}

void read_answer(){
	long long ans;
	spoj_assert(fscanf(spoj_t_out,"%lld",&ans)==1);
	spoj_assert(ans == res);
	long long sum=0;
	int j;
	fill(selected,selected+m+10,0);
	foru(i,1,n){
		spoj_assert(fscanf(spoj_t_out,"%d",&j)==1);
		spoj_assert(j>0 && j<=m);
		selected[j] = 1;
		sum += abs(a[i]-b[j]);
	}
	
	spoj_assert(sum == res);	
	foru(i,1,m)	spoj_assert(selected[i] == 1);
}

int main(){
	spoj_init();
	read_input_output();
	read_answer();
	fprintf(spoj_score, "%lf",(double)5/3);		
	return 0;
}
