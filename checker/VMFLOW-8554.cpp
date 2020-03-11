#include <spoj.h>
#include <iostream>
//#include <cassert>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;
#define REP(i, n) for (int i = 0; i < n; i++)
#define FOR(i, a, b) for (int i = a; i <= b; i++)

const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

/*
FILE *spoj_p_in, *spoj_p_out, *spoj_t_out, *spoj_score;
#define PIN "in.txt"
#define TOUT "out.txt"
#define SCORE "result.txt"

void spoj_init()
{
	spoj_p_in=fopen(PIN, "r");
	spoj_t_out=fopen(TOUT, "r");
	spoj_score=fopen(SCORE, "w");
}

#define spoj_assert assert
*/

int n;
char a[55][55];
int x[55][55];
bool used[55][55];

bool checkConnection(int si, int sj) {
	char base = a[si][sj];
	queue<int> qx;
	queue<int> qy;
	qx.push(si);
	qy.push(sj);
	used[si][sj] = true;
	bool connection = false;
	while (!qx.empty()) {
		int i = qx.front(); qx.pop();
		int j = qy.front(); qy.pop();
		int count = 0;
		REP(dir, 4)	if (x[i][j] & (1 << dir)) {
			int u = i + dx[dir];
			int v = j + dy[dir];
			if (used[u][v]) continue;
//			cerr << i << " " << j << " " << u << " " << v << " " << a[u][v] << endl;
			count++;
			spoj_assert(count <= 1); //Make sure this is a path, not a tree

			used[u][v] = true;
			if (a[u][v] == base) { //Connect to the end point
				connection = true;
				continue;
			} else {
				//must equals '.'
				spoj_assert(a[u][v] == '.');
				//mustn't found connection
				spoj_assert(connection == false);
				a[u][v] = base + 32;
				qx.push(u);
				qy.push(v);
			}
		}
	}

	//Not connect to the end point, check again, make sure the start point must have no connection
	if (!connection) {
		spoj_assert(x[si][sj] == 0);
		used[si][sj] = false;
	}
	return connection;
}

int main()
{
	spoj_init();
	/***********Doc input *******/
	fscanf(spoj_p_in, "%d", &n);
	FOR(i, 1, n) FOR(j, 1, n) {
		while (true) {
			fscanf(spoj_p_in, "%c", &a[i][j]);
			if (a[i][j] == '.') break;
			if ('A' <= a[i][j] && a[i][j] <= 'Z') break;
		}
	}
	/***********Doc input *******/


	/***********Doc output *******/
	memset(x, 0, sizeof(x));
	FOR(i, 1, n) FOR(j, 1, n) {
		spoj_assert(fscanf(spoj_t_out, "%d", &x[i][j]) == 1);
		spoj_assert(0 <= x[i][j] && x[i][j] <= 15);
	}
	/***********Doc output *******/


	/***********Check cac o trong output phai khop voi nhau *******/
	FOR(i, 1, n) FOR(j, 1, n) REP(dirij, 4) {
		int u = i + dx[dirij];
		int v = j + dy[dirij];
		int diruv = (dirij + 2) % 4;

		bool from_ij_to_uv = (x[i][j] & (1 << dirij));
		bool from_uv_to_ij = (x[u][v] & (1 << diruv));
//		cerr << "Check cell " << i << " " << j << " " << (bool)(from_ij_to_uv) << " " << u << " " << v << " " << (bool)(from_uv_to_ij) << " " << x[u][v] << " " << diruv << endl;
		spoj_assert(from_ij_to_uv == from_uv_to_ij);
	}
	/***********Check cac o trong output phai khop voi nhau *******/


	/***********Kiem tra cac duong di*******/
	memset(used, false, sizeof(used));
	int totalPairs = 0;
	int unconnectedPairs = 0;
	int connectedPairs = 0;
	FOR(i, 1, n) FOR(j, 1, n) if (a[i][j] != '.' && !used[i][j]) {
		if (checkConnection(i, j)) {
			connectedPairs++;
		} else {
			unconnectedPairs++;
			used[i][j] = false;
		}
	}
	/***********Kiem tra cac duong di*******/

	spoj_assert(unconnectedPairs % 2 == 0);
	unconnectedPairs /= 2;
	totalPairs = unconnectedPairs + connectedPairs;


	FOR(i, 1, n) FOR(j, 1, n) if (!used[i][j]) spoj_assert(x[i][j] == 0); /*make sure there is no loop try to trick the checker*/

	int totalUsed = 0;
	FOR(i, 1, n) FOR(j, 1, n) if (used[i][j]) totalUsed++;

	if (totalUsed == n * n && totalPairs == connectedPairs) {
		fprintf(spoj_score, "2.000000");
		printf("Score = 2");
	} else {
		fprintf(spoj_score, "%0.6lf", 1.5 * connectedPairs * totalUsed / (totalPairs * n * n));
		printf("Score = %0.6lf", 1.5 * connectedPairs * totalUsed / (totalPairs * n * n));
	}

	return 0;
}
