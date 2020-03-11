#include <bits/stdc++.h>
#include <spoj.h>
using namespace std;

char a[1010][1010];
int m, n, used[1010][1010], flip[1010][1010];

void readInput() 
{
	spoj_assert(fscanf(spoj_p_in, "%d %d", &m ,&n) == 2);
	spoj_assert(n >= 1 && n <= 1000);
	spoj_assert(m >= 1 && m <= 1000);
	
	for (int i = 1; i <= m; i++)
	{
		spoj_assert(fscanf(spoj_p_in, "%s", a[i] + 1) == 1);
		for (int j = 1; j <= n; j++)
			spoj_assert(a[i][j] == '0' || a[i][j] == '1');
	}
}

void readOutput() 
{
	int steps;
	spoj_assert(fscanf(spoj_t_out, "%d", &steps) == 1);
	
	int x, y, xx, yy, r, c;
	while (fscanf(spoj_t_out, "%d %d %d %d", &x, &y, &r, &c) == 4)
	{
		spoj_assert(--steps >= 0);
		
		spoj_assert(r > 0 && r <= m);
		spoj_assert(c > 0 && c <= n);
		spoj_assert(used[r][c] == 0);
		used[r][c] = 1;
		
		xx = x + r - 1;
		yy = y + c - 1;
		
		spoj_assert(x > 0 && x <= m);
		spoj_assert(xx > 0 && xx <= m);
		spoj_assert(y > 0 && y <= n);
		spoj_assert(yy > 0 && yy <= n);
		
		flip[x][y] ^= 1;
		flip[x][yy + 1] ^= 1;
		flip[xx + 1][y] ^= 1;
		flip[xx + 1][yy + 1] ^= 1;
	}
	
	spoj_assert(steps == 0);
	
	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= n; j++)
		{
			flip[i][j] ^= flip[i - 1][j] ^ flip[i][j - 1] ^ flip[i - 1][j - 1];
			spoj_assert(flip[i][j] == a[i][j] - '0');
		}
}

int main()
{
	spoj_init();
	readInput();
	readOutput();
	fprintf(spoj_score, "5");
	return 0;
}
