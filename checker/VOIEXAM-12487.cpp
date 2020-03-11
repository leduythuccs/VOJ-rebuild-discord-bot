#include "spoj.h"
#include<bits/stdc++.h>
#define MAX   2020
#define NMOD   3
#define FOR(i,a,b) for (int i=(a),_b=(b);i<=_b;i=i+1)
#define FORD(i,b,a) for (int i=(b),_a=(a);i>=_a;i=i-1)
#define REP(i,n) for (int i=0,_n=(n);i<_n;i=i+1)
#define FORE(i,v) for (__typeof((v).begin()) i=(v).begin();i!=(v).end();i++)
#define ALL(v) (v).begin(),(v).end()
#define fi   first
#define se   second
#define MASK(i) (1LL<<(i))
#define BIT(x,i) (((x)>>(i))&1)
#define next   ___next
#define prev   ___prev
#define left   ___left
#define right   ___right
using namespace std;
const int mod[]={(int)1e9+2277,(int)1e9+5277,(int)1e9+8277,(int)1e9+9277};
template<class X,class Y>
    void minimize(X &x,const Y &y) {
        if (x>y) x=y;
    }
template<class X,class Y>
    void maximize(X &x,const Y &y) {
        if (x<y) x=y;
    }
struct Hash {
    int val[NMOD];
    Hash() {
        memset(val,0,sizeof val);
    }
    Hash(long long x) {
        REP(i,NMOD) val[i]=(x%mod[i]+mod[i])%mod[i];
    }
    Hash operator + (const Hash &x) const {
        Hash res;
        REP(i,NMOD) {
            res.val[i]=val[i]+x.val[i];
            if (res.val[i]>=mod[i]) res.val[i]-=mod[i];
        }
        return (res);
    }
    Hash operator - (const Hash &x) const {
        Hash res;
        REP(i,NMOD) {
            res.val[i]=val[i]-x.val[i];
            if (res.val[i]<0) res.val[i]+=mod[i];
        }
        return (res);
    }
    Hash operator * (const Hash &x) const {
        Hash res;
        REP(i,NMOD) res.val[i]=1LL*val[i]*x.val[i]%mod[i];
        return (res);
    }
    bool operator < (const Hash &x) const {
        REP(i,NMOD) if (val[i]!=x.val[i]) return (val[i]<x.val[i]);
        return (false);
    }
};
const char validChar[]="$()+-*";
#define OPEN   -1
#define CLOSE   -2
#define ADD   -3
#define SUB   -4
#define MUL   -5
#define EMPTY   -6
deque<int> token;

Hash loadExprLv1(int exprID);
Hash loadExprLv2(int exprID);
Hash loadExprLv3(int exprID);

int nextToken(void) {
    if (token.empty()) return (-6);
    return (token.front());
}
void popToken(void) {
    spoj_assert(!token.empty());
    token.pop_front();
}
Hash loadExprLv1(int exprID) {
    if (nextToken()>=0) {
        Hash res(nextToken());
        popToken();
        return (res);
    }
    if (nextToken()==OPEN) {
        popToken();
        Hash res=loadExprLv3(exprID);
        //if (nextToken()!=CLOSE) stream.quitf(_wa,"Expression #%d is invalid",exprID);
        spoj_assert(nextToken() == CLOSE);
        popToken();
        return (res);
    }
    //stream.quitf(_wa,"Expression #%d is invalid",exprID);
    spoj_assert(false);
}
Hash loadExprLv2(int exprID) {
    Hash res=loadExprLv1(exprID);
    while (nextToken()==MUL) {
        popToken();
        res=res*loadExprLv1(exprID);
    }
    return (res);
}
Hash loadExprLv3(int exprID) {
    Hash res=loadExprLv2(exprID);
    while (nextToken()==ADD || nextToken()==SUB) {
        bool isAdd=nextToken()==ADD;
        popToken();
        if (isAdd) res=res+loadExprLv2(exprID);
        else res=res-loadExprLv2(exprID);
    }
    return (res);
}
Hash checkExpr(int exprID,string expr) {
    //if (expr.empty()) stream.quitf(_wa,"Expression #%d is empty",exprID);
    spoj_assert(!expr.empty());
    FORE(it,expr) {
        bool ok=false;
        if ('0'<=*it && *it<='9') ok=true;
        FOR(i,1,5) if (*it==validChar[i]) ok=true;
        //if (!ok) stream.quitf(_wa,"Expression #%d is invalid",exprID);
        spoj_assert(ok);
    }
    token.clear();
    bool lastNum=false;
    FORE(it,expr) {
        if ('0'<=*it && *it<='9') {
            if (!lastNum) {
                token.push_back(0);
                lastNum=true;
            }
            token.back()=token.back()*10+*it-'0';
        }
        FOR(i,1,5) if (*it==validChar[i]) {
            token.push_back(-i);
            lastNum=false;
        }
    }
    Hash res=loadExprLv3(exprID);
    //if (nextToken()!=EMPTY) stream.quitf(_wa,"Expression #%d is invalid",exprID);
    spoj_assert(nextToken() == EMPTY);
    return (res);
}
const string noAns="NO SOLUTION";
string expr[MAX];
int n;
void init(void) {
    fscanf(spoj_p_in, "%d", &n);
    char tmp[100];
    FOR(i, 1, n) {
        fscanf(spoj_p_in, "%s\n", tmp);
        expr[i] = string(tmp);
    }
}
bool checkMatchExpr(string expr,string form) {
    string tmp;
    FORE(it,expr) if (*it!='(' && *it!=')') tmp.push_back(*it);
    return (tmp==form);
}
bool checkAnswer() {
    map<Hash,int> exprID;
    char tmp_raw[100000];
    FOR(i,1,n) {
        //string tmp=readLine();
        fscanf(spoj_t_out, "%s\n", tmp_raw);
        string tmp = string (tmp_raw);
        if (i==1 && tmp==noAns) return (false);
        Hash val=checkExpr(i,tmp);
        //if (!checkMatchExpr(tmp,expr[i])) stream.quitf(_wa,"Expression #%d does not correspond to the given one",i);
        spoj_assert(checkMatchExpr(tmp, expr[i]));
        //if (exprID.find(val)!=exprID.end()) stream.quitf(_wa,"Expression #%d and #%d has same value",i,exprID[val]);
        spoj_assert(exprID.find(val) == exprID.end());
        exprID[val]=i;
    }
    return (true);
}
void process(void) {
    char t[100];
    fscanf(spoj_p_out, "%s\n", t);
    if (t[0] == 'N') {
        char tt[1111];
        fscanf(spoj_t_out, "%s\n", tt);
        spoj_assert(tt[0] == 'N');
        return;
    }
    bool res=checkAnswer();
    spoj_assert(res);
}
int main(int c,char **v) {
    spoj_init();
    init();
    process();
    return 0;
}
