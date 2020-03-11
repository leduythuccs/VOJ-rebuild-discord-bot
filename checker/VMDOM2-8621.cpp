#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <string>
#include <deque>
#include <complex>
#include <sstream>
#include <iomanip>
#include <cassert>
#include <spoj.h>
using namespace std;

/*FILE *spoj_p_in, *spoj_t_out, *spoj_score;
#define PIN "in.in"
#define TOUT "out.out"
#define SCORE "result.out"

void spoj_init()
{
	spoj_p_in = fopen(PIN, "r");
	spoj_t_out = fopen(TOUT, "r");
	spoj_score = fopen(SCORE, "w");
}

#define spoj_assert assert*/

int n, m, flag[111][111];

void readInput() 
{
	spoj_assert(fscanf(spoj_p_in, "%d%d\n", &m, &n) == 2);
	spoj_assert(n >= 10 && n <= 100 && n % 2 == 0);
	spoj_assert(m >= 10 && m <= 100 && m % 2 == 0);
	
	int x, y;
	for (int i = 0; i < 2; i++)
	{
		spoj_assert(fscanf(spoj_p_in, "%d%d\n", &x, &y) == 2);
		spoj_assert(x >= 1 && x <= m);
		spoj_assert(y >= 1 && y <= n);
		spoj_assert(flag[x][y] == 0);
		flag[x][y] = -1;
	}
}

int readOutput() 
{
  int sol;
	spoj_assert(fscanf(spoj_t_out, "%d", &sol) == 1);
	spoj_assert(sol >= 0 && sol <= 10);
	
	set < vector < pair<int,int> > > s;

	for (int cur = 0; cur < sol; cur++)
	{
		int x, y, xx, yy;
		vector < pair<int,int> > v;
		for (int i = 0; i < m * n / 2 - 1; i++)
		{
			spoj_assert(fscanf(spoj_t_out, "%d%d%d%d\n", &x, &y, &xx, &yy) == 4);
			spoj_assert(x >= 1 && x <= m);
			spoj_assert(xx >= 1 && xx <= m);
			spoj_assert(y >= 1 && y <= n);
			spoj_assert(yy >= 1 && yy <= n);
			spoj_assert(flag[x][y] == cur);
			spoj_assert(flag[xx][yy] == cur);
			spoj_assert(abs(x - xx) + abs(y - yy) == 1);
			flag[x][y] = flag[xx][yy] = cur + 1;
			
			x = x * n + y; xx = xx * n + yy;
			if (x > xx) swap(x, xx);
			v.push_back(make_pair(x, xx));
		}
		
		sort(v.begin(), v.end());
		spoj_assert(s.count(v) == 0);
		s.insert(v);
	}
	
	return sol;
}

int main()
{
	spoj_init();
	readInput();
	fprintf(spoj_score, "%.1lf\n", 0.5 * readOutput());
	return 0;
}
