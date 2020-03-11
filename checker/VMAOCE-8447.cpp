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

int n, d[100100], region[100100], subtree[100100], cnt[10];
vector <int> a[100100];

int get(int x)
{
	return x == d[x] ? x : d[x] = get(d[x]);
}

void readInput() 
{
	spoj_assert(fscanf(spoj_p_in, "%d\n", &n) == 1);
	spoj_assert(n >= 1 && n <= 100000);
	
	for (int i = 1; i <= n; i++) d[i] = i;

	int x, y;
	for (int i = 1; i < n; i++)
	{
		spoj_assert(fscanf(spoj_p_in, "%d %d\n", &x, &y) == 2);
		spoj_assert(x >= 1 && x <= n);
		spoj_assert(y >= 1 && y <= n);
		spoj_assert(get(x) != get(y));
		d[get(x)] = get(y);
		a[x].push_back(y);
		a[y].push_back(x);
	}
}

void dfs(int x, int par, int curRegion)
{
	spoj_assert(region[x] == curRegion);
	subtree[x] = 1;
	for (int i = 0; i < int(a[x].size()); i++)
	{
		int y = a[x][i];
		if (y != par)
		{
			dfs(y, x, curRegion);
			subtree[x] += subtree[y];
		}
	}
}

void readOutput() 
{
	int hasAnswer;
	spoj_assert(fscanf(spoj_p_out, "%d", &hasAnswer) == 1);

  int sol;
	spoj_assert(fscanf(spoj_t_out, "%d", &sol) == 1);

	if (hasAnswer == -1) spoj_assert(sol == -1);
	else spoj_assert(sol != -1);
	
	if (hasAnswer == -1) return;
	
	region[1] = sol;

	for (int i = 2; i <= n; i++)
		spoj_assert(fscanf(spoj_t_out, "%d", region + i) == 1);
		
	int root = 0;
	for (int i = 1; i <= n; i++)
	{
		spoj_assert(region[i] >= 0 && region[i] <= 3);
		if (region[i] == 0)
		{
			spoj_assert(root == 0);
			root = i;
		}
	}
	
	// check each subtree must be in 1 region
	for (int i = 0; i < int(a[root].size()); i++)
	{
		int x = a[root][i];
		dfs(x, root, region[x]);
		cnt[region[x]] += subtree[x];
	}
	
	// check number of vertices in each region
	for (int i = 1; i <= 3; i++)
		spoj_assert(cnt[i] > 0 && cnt[i] * 2 <= n);
}

int main()
{
	spoj_init();
	readInput();
	readOutput();
	fprintf(spoj_score, "5");
	return 0;
}
