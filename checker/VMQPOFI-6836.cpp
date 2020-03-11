#include <spoj.h>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <map>
using namespace std;


/*FILE *spoj_p_in, *spoj_p_out, *spoj_t_out, *spoj_score;
#define PIN "Test\\input39.txt"
#define TOUT "Test\\output39.txt"
#define SCORE "result.txt"

void spoj_init()
{
	spoj_p_in=fopen(PIN, "r");
	//spoj_p_out=fopen(POUT, "r");
	spoj_t_out=fopen(TOUT, "r");
	spoj_score=fopen(SCORE, "w");
}

#define spoj_assert assert*/

#define MAXN 100100
#define LIM 100000
#define LL long long
#define MOD 1000000007

int n, m, first, last, ansInput, ansOutput;

int input[MAXN], output[MAXN], stack[MAXN], queue[MAXN];

bool isCorrect1, isCorrect2;

double point;

int convert(string s) {
    if (s.length() == 1) {
        if (s[0] == '+') return LIM + 1;
        if (s[0] == '-') return LIM + 2;
        if (s[0] == '*') return LIM + 3;
    }
    char tmp[101];
    strcpy(tmp, s.c_str());
    int ans;
    spoj_assert(sscanf(tmp, "%d", &ans) == 1);
    return ans;
}

LL calc(LL x, LL y, int o) {
    if (o == LIM + 1) return (x + y + MOD) % MOD;
    if (o == LIM + 2) return (x - y + MOD) % MOD;
    if (o == LIM + 3) return ((x * y) % MOD + MOD) % MOD;
}

int evaluateUsingStack() {
    last = 0;
    //for (int i = 0; i < n; i++) cout << input[i] << ' '; cout << endl;
    for (int i = 0; i < n; i++)
        if (input[i] < LIM) stack[++last] = input[i];
        else {
            last--;
            //cout << stack[last] << ' ' << stack[last + 1] << ' ' << calc(stack[last], stack[last + 1], input[i]) << endl;
            stack[last] = calc(stack[last], stack[last + 1], input[i]);
        }
    return stack[last];
}

int evaluateUsingQueue() {
    first = 1, last = 0;
    for (int i = 0; i < n; i++)
        if (output[i] < LIM) queue[++last] = output[i];
        else {
            //cout << queue[first] << ' ' << queue[first + 1] << ' ' << calc(queue[first], queue[first + 1], output[i]) << endl;
            queue[++last] = calc(queue[first], queue[first + 1], output[i]);
            first += 2;
        }
    return queue[first];
}

bool checkAllZeroes() {
    for (int i = 0; i < n; i++)
        if (output[i] != 0) return false;
    return true;
}

bool checkAnswer1() {
    char tmp[1000100];
    spoj_assert(fgets(tmp, 10000000, spoj_t_out) != NULL);
    string s = tmp;
    stringstream ss(s);
    string cur;
    m = 0;
    while (ss >> cur)
        output[m++] = convert(cur);
    spoj_assert(m == n);
    // all zeroes?
    if (checkAllZeroes()) return false;
    // same operators and operands ?
    vector <int> a;
    for (int i = 0; i < n; i++)
        a.push_back(input[i]);
    vector <int> b;
    for (int i = 0; i < n; i++)
        b.push_back(output[i]);
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    assert(a.size() == b.size());
    for (int i = 0; i < n; i++)
        spoj_assert(a[i] == b[i]);
    // same results?
    ansOutput = evaluateUsingQueue();
    spoj_assert(ansOutput == ansInput);
    return true;
}

bool checkAnswer2() {
    char tmp[1000100];
    spoj_assert(fgets(tmp, 10000000, spoj_t_out) != NULL);
    string s = tmp;
    stringstream ss(s);
    string cur;
    m = 0;
    while (ss >> cur)
        output[m++] = convert(cur);
    spoj_assert(m == n);
    // all zeroes?
    if (checkAllZeroes()) return false;
    // has - ?
    for (int i = 0; i < n; i++)
        spoj_assert(output[i] != LIM + 2);
    // same operands ?
    vector <int> a;
    for (int i = 0; i < n; i++)
        if (input[i] < LIM) a.push_back(abs(input[i]));
    vector <int> b;
    for (int i = 0; i < n; i++)
        if (output[i] < LIM) b.push_back(abs(output[i]));
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    spoj_assert(a.size() == b.size());
    for (int i = 0; i < a.size(); i++)
        spoj_assert(a[i] == b[i]);
    // same results?
    ansOutput = evaluateUsingQueue();
    spoj_assert(ansOutput == ansInput);
    return true;
}



int main() {
	spoj_init();

    // read from input
    spoj_assert(fscanf(spoj_p_in, "%d\n", &n) == 1);
    for (int i = 0; i < n; i++) {
        char tmp[20];
        spoj_assert(fscanf(spoj_p_in, "%s", tmp) == 1);
        string s = tmp;
        input[i] = convert(s);
    }
    ansInput = evaluateUsingStack();

    // read from output
    isCorrect1 = checkAnswer1();
    isCorrect2 = checkAnswer2();

    if (isCorrect1 && isCorrect2) point = 1;
    else
        if (isCorrect1 || isCorrect2) point = 0.8;
        else point = 0;
    fprintf(spoj_score, "%0.6lf", point);
    //cout << point << endl;;

    return 0;
}
