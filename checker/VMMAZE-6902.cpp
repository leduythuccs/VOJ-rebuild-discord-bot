#include "spoj_interactive.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <map>
#include <set>
#include <stack>
#include <list>
#include <vector>
#include <queue>

using namespace std;

#define PI acos(-1)
#define MP make_pair
#define PB push_back
#define VI vector <int>
#define PII pair <int, int>
#define LL long long
#define SET(v,i) memset(v, i, sizeof(v))
#define FOR(i,a,b) for (int i = (a); i <= (b); i++)
#define FORD(i,a,b) for (int i = (a); i >= (b); i--)
#define FORN(i,a,b) for (int i = (a); i < (b); i++)
#define DOWN(i,a,b) for (int i = (a); i > (b); i--)
#define FIT(it,v) for (typeof(v.begin()) it = v.begin(); it != v.end(); it++)
#define FITD(it,v) for (typeof(v.rbegin()) it = v.rbegin(); it != v.rend(); it++)
#define FREOPEN freopen("a.in", "r", stdin); freopen("a.out", "w", stdout)

#define FI first
#define SE second
#define maxn 100

int cd[] = {-1, 0, 1, 0}, cc[] = {0, 1, 0, -1};//0, 1, 2, 3 = N E S W

int n, m, k;
PII st, ed;
PII pos[maxn];
bool used[maxn];
string MAP[maxn];

char tmp[maxn];

int main()
{
    spoj_init();                       

	// Read input file
	fscanf(spoj_p_in, "%d%d%d\n", &m, &n, &k);
	FOR (i, 1, m) {
		fscanf(spoj_p_in, "%s\n", &tmp[0]);
		MAP[i] = string(tmp);
		MAP[i] = '#' + MAP[i];
	}
	fprintf(spoj_p_info, "Read input file: %d %d %d\n", m, n, k);
	
	// Find starting position
	FOR (i, 1, m)
	FOR (j, 1, n) 
		if (MAP[i][j] == 'S') st.FI = i, st.SE = j, MAP[i][j] = '.';
	
	// Initialize portals
	SET (used, false);
	
	// cnt = number of movements
	int cnt = 0;
	int x, y;

	// Print to tested's input
	spoj_printf("%d ", m);
	spoj_printf("%d ", n);
	spoj_printf("%d\n", k);

	while ( 1 ) {
		// Read tested's output
		spoj_scanf("%d", &x);
		fprintf(spoj_p_info, "Read: %d\n", x);

		// Update number of movements
		cnt ++;

		// Check for invalid inputs
		if (cnt > 8*m*n + 10 || x < 0 || x > 6) {
			return SPOJ_RV_WA;
		}
		
		// Move to adjacent squares
		if (x < 4) {
			st.FI += cd[x];
			st.SE += cc[x];
			
			if (MAP[st.FI][st.SE] == '#') {
				spoj_printf("%d ", 0);
				fflush(spoj_for_tested);
				st.FI -= cd[x];
				st.SE -= cc[x];
			}
			else if (MAP[st.FI][st.SE] == '.') {
				spoj_printf("%d ", 1);
				fflush(spoj_for_tested);
			}
			else if (MAP[st.FI][st.SE] == 'T') {
				spoj_printf("%d ", 999);
				fflush(spoj_for_tested);
				break;
			}
		}
		
		// Put portal at current position
		if (x == 4) {
			spoj_scanf("%d", &y);
			if (y < 1 || y > k) {
				return SPOJ_RV_WA;
			}
			if (used[y]) {
				spoj_printf("%d ", 0);
				fflush(spoj_for_tested);
			}
			else {
				used[y] = true;
				pos[y] = st;
				spoj_printf("%d ", 1);
				fflush(spoj_for_tested);
			}
		}
		
		// Remove portal from current position
		if (x == 5) {
			spoj_scanf("%d", &y);
			if (y < 1 || y > k) {
				return SPOJ_RV_WA;
			}
			if (!used[y] || pos[y] != st) {
				spoj_printf("%d ", 0);
				fflush(spoj_for_tested);
			}
			else {
				used[y] = false;
				spoj_printf("%d ", 1);
				fflush(spoj_for_tested);
			}
		}
		
		// Go to portal
		if (x == 6) {
			spoj_scanf("%d", &y);
			if (y < 1 || y > k) {
				return SPOJ_RV_WA;
			}
			if (!used[y]) {
				spoj_printf("%d ", 0);
				fflush(spoj_for_tested);
			}
			else {
				st = pos[y];
				spoj_printf("%d ", 1);
				fflush(spoj_for_tested);
			}
		}
	}
	
	fprintf(spoj_score, "%.5lf", (double) (8 * m * n) / (double) (cnt));
    return SPOJ_RV_AC;                 
}
