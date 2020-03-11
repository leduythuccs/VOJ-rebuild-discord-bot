#include <spoj.h>
//#include <cassert>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
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

#define spoj_assert assert*/

char a[10010][10010];

int main()
{
	spoj_init();
	int result, x1;
	fscanf(spoj_p_out, "%d", &result);
	spoj_assert(fscanf(spoj_t_out, "%d", &x1)==1);
	if (result==-1)	spoj_assert(result==x1);
	else
	{
		int x2, x3, x4, m, n, x, y;
		spoj_assert(fscanf(spoj_t_out, "%d%d%d", &x2, &x3, &x4)==3);
		fscanf(spoj_p_in, "%d%d", &n, &m);
		spoj_assert(1 <= x1 && x1 <= n);
		spoj_assert(1 <= x2 && x2 <= n);
		spoj_assert(1 <= x3 && x3 <= n);
		spoj_assert(1 <= x4 && x4 <= n);
		while (m--) fscanf(spoj_p_in,"%d%d",&x,&y), a[x][y]=a[y][x]=1;
		spoj_assert(a[x1][x2] && a[x2][x3] && a[x3][x4] && a[x4][x1]);
	}
	return 0;
}
