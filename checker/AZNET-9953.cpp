#include "spoj.h"
/*
	spoj_p_in: input
	spoj_p_out: output
	spoj_t_out: user's output
	spoj_score: score
*/

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <string>
#include <cmath>
#include <cassert>
#include <ctime>
#include <utility>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <sstream>
#define FOR(a,b,c) for (int a=b,_c=c;a<=_c;a++)
#define FORD(a,b,c) for (int a=b;a>=c;a--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; ++i)
#define REPD(i,a) for(int i=(a)-1; i>=0; --i)
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define sz(a) int(a.size())
#define reset(a,b) memset(a,b,sizeof(a))
#define oo 2000000007

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int maxn=100007;

struct edge{
    int x,y,id;
    edge(){}
    edge(int a, int b, int c):x(a), y(b), id(c){}
}e1[maxn],e2[maxn];

struct edge2{
    int x,y,t;
}e[maxn];

int a[maxn],b[maxn],n,m,m1,m2,T,lab[2][maxn], Xmax,Xmin,X,Y,res;
int ans[maxn], cnt;

int getroot(int u, int *lab){
    if(lab[u]<0) return u;
    lab[u]=getroot(lab[u],lab);
    return lab[u];
}

void dsu(int r1, int r2, int *lab){
    if(lab[r1]<lab[r2]){
        lab[r1]+=lab[r2];
        lab[r2]=r1;
    }else{
        lab[r2]+=lab[r1];
        lab[r1]=r2;
    }
}

/*For testing
FILE *spoj_p_in, *spoj_p_out, *spoj_t_out, *spoj_score;
#define PIN "48.in"
#define POUT "8.out"
#define TOUT "48.out"
#define SCORE "score.txt"

void spoj_init()
{
	spoj_p_in=fopen(PIN,"r");
	spoj_p_out=fopen(POUT, "r");
	spoj_t_out=fopen(TOUT, "r");
	spoj_score=fopen(SCORE, "w");
}

void spoj_assert(bool t)
{
    assert(t);
}
*/
char s[15 * 100007];

int main(){
    spoj_init();

    int u,v,t;
    fscanf(spoj_p_in, "%d",&T);
    REP(tt,T){
        fscanf(spoj_p_in,"%d%d",&n,&m);
        m1=m2=0;
        FOR(i,1,n-1) fscanf(spoj_p_in,"%d",&a[i]);
        FOR(i,1,n-1) fscanf(spoj_p_in,"%d",&b[i]);
        FOR(i,1,m){
            fscanf(spoj_p_in,"%d%d%d",&u,&v,&t);
            spoj_assert(u!=0);
            spoj_assert(v!=0);
            if(t==1) e1[++m1]=edge(u,v,i);
            else e2[++m2]=edge(u,v,i);
            e[i].x=u; e[i].y=v; e[i].t=t;
        }

        //input user output
        fgets(s,15 * 100000,spoj_t_out);
        int t=0;
        bool space=1;
        cnt=0;
        REP(i,strlen(s)){
            if(s[i]=='\n') break;
            if(s[i]==' ' && !space){
                space=1;
                spoj_assert(1<=t && t<=m);
                ans[++cnt]=t;

                t=0;
            }else if('0'<=s[i] && s[i]<='9'){
                space=0;
                t=t*10+s[i]-'0';
                spoj_assert(0<=t && t<=m);
            }
            spoj_assert(cnt<n);
        }
        if(!space){
            spoj_assert(1<=t && t<=m);
           ans[++cnt]=t;
           t=0;
        }
        spoj_assert(cnt==n-1);
        //========================================

        reset(lab[0],-1); reset(lab[1],-1);

        //Match all 1
        Xmax=0;
        FOR(i,1,m1){
            u=getroot(e1[i].x, lab[0]); v=getroot(e1[i].y, lab[0]);
            if(u!=v){
               ++Xmax;
               dsu(u,v,lab[0]);
            }
        }
        //Match 2
        Y=0;
        FOR(i,1,m2){
            u=getroot(e2[i].x,lab[0]); v=getroot(e2[i].y, lab[0]);
            if(u!=v){
                dsu(u,v,lab[0]);
                u=getroot(e2[i].x,lab[1]); v=getroot(e2[i].y, lab[1]);
                dsu(u,v,lab[1]);
                ++Y;
            }
        }
        spoj_assert(Xmax+Y>=n-1);

        //Continue with 2
        FOR(i,1,m2){
            u=getroot(e2[i].x,lab[1]); v=getroot(e2[i].y,lab[1]);
            if(u!=v){
                dsu(u,v,lab[1]);
                ++Y;
            }
        }

        //Find best match
        Xmin=n-1-Y;
        res=oo;
        FOR(x,Xmin,Xmax)
            if(a[x]+b[n-1-x]<res){
                X=x; Y=n-1-x;
                res=a[x]+b[n-1-x];
            }

        //Check the result
        int c1=0,c2=0;
        FOR(i,1,n-1){
            if(e[ans[i]].t==1) ++c1; else ++c2;
        }
        if(res<a[c1]+b[c2]){
            spoj_assert(1==0);
            return 0;
        }
        reset(lab[0],-1);
        cnt=0;
        FOR(i,1,n-1){
            u=getroot(e[ans[i]].x,lab[0]);
            v=getroot(e[ans[i]].y,lab[0]);
            if(u==v){
                spoj_assert(1==0);
                return 0;
            }
            dsu(u,v,lab[0]);
        }

    }

    //All ok!
    fprintf(spoj_score, "1");
    return 0;
}
