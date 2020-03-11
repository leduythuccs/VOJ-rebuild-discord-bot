#include <bits/stdc++.h>
#include "spoj.h"
using namespace std;

/*FILE *spoj_p_in, *spoj_p_out, *spoj_t_out;
#define PIN "in.txt"
#define POUT "ans.txt"
#define TOUT "out.txt"

void spoj_init()
{
	spoj_p_in=fopen(PIN, "r");
	spoj_p_out=fopen(POUT, "r");
	spoj_t_out=fopen(TOUT, "r");	
}
void spoj_assert(bool b)
{
	if (!b)
	{
		printf("WA");
		exit(1);		
	}
}*/

int main()
{
	spoj_init();  		    

	char ans[100], ret[100];	
	fscanf(spoj_p_out, "%s", ans);	
	spoj_assert(fscanf(spoj_t_out, "%s", ret)==1);
	spoj_assert(strcmp(ans, ret)==0);
	if (strcmp(ans, "YES")==0)
	{
		int s, k, n;
		fscanf(spoj_p_in, "%d%d%d", &s, &k, &n);
		int a[30][30];
		for (int i=0; i<n; i++)
			for (int j=0; j<k; j++)
				fscanf(spoj_p_in,"%d",&a[i][j]);
		int sum=0, x=-1;
		for (int j=0; j<k; j++)
		{			
			int y;
			spoj_assert(fscanf(spoj_t_out, "%d", &y)==1);
			spoj_assert(y>=x);
			x=y;
			bool b=false;
			for (int i=0; i<n; i++)			
				b|=a[i][j]==x;
			spoj_assert(b);
			sum+=x;
		}
		spoj_assert(sum==s);
	}	
	return 0;
}

