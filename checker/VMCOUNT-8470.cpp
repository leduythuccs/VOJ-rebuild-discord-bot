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
#include <spoj.h>
using namespace std;
const int expect[] = {2241, 61200920, 454553455, 403238471, 10916, 33022, 880639351, 427958180, 953026246, 131751338};

int main() 
{
	spoj_init();
	int score = 0, output;
	for (int i = 0; i < 10; i++)
	{
		fscanf(spoj_t_out, "%d", &output);
		if (output == expect[i]) score += 10;
		fprintf(spoj_p_info, "%d %d\n", expect[i], output);
	}
	fprintf(spoj_score, "%d\n", score);
}
