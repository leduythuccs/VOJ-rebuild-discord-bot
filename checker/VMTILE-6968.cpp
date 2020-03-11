#include <iomanip>
#include <sstream>
#include <fstream>
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

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define ll long long
#define F first
#define S second
#define PB push_back
#define MP make_pair
using namespace std;
const double PI = acos(-1.0);

#include <spoj.h>

int main() {
	spoj_init();
	int score = 0;
	REP(i,10) {
		int res, student;
		fscanf(spoj_p_out, "%d", &res);
		fscanf(spoj_t_out, "%d", &student);
		if (student == res) score += 10;
	}
	fprintf(spoj_score, "%d\n", score);
    return 0;
}
