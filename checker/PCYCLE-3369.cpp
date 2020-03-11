#include <numeric>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <spoj.h>
using namespace std ;

#define FOREACH(it,c) for(typeof((c).begin()) it=(c).begin();it!=(c).end();it++)
#define FOR(i,a,b) for( int i=(a),_b=(b);i<=_b;i++)
#define DOW(i,b,a) for( int i=(b),_a=(a);i>=_a;i--)
#define REP(i,n) for( int i=0,_n=(n);i<_n;i++)
#define DEP(i,n) for( int i=(n)-1;i>=0;i--)

int edge[205][205] ;
int n, m, start, solution ;

main()
{
	spoj_init() ;
	fscanf(spoj_t_out,"%d",&start) ;
	fscanf(spoj_p_out,"%d",&solution) ;
	spoj_assert( start * solution > 0 ) ;
	if ( solution == -1 ) return 0 ;
	fscanf(spoj_p_in,"%d %d",&n,&m) ;
	FOR(u,1,n)
	FOR(v,1,n) edge[u][v] = 100000000 ;
	REP(i,m) {
		int u, v, val ;
		fscanf(spoj_p_in,"%d %d %d",&u,&v,&val) ;
		edge[u][v] = edge[v][u] = val ;
	}
	
	int u = start ;
	int tong = 0 ;
	REP(i,m) {
		int v ;
		fscanf(spoj_t_out,"%d",&v) ;
		spoj_assert( v > 0 && v <= n ) ;
		spoj_assert( edge[u][v] <= 10000 ) ;
		tong += edge[u][v] ;
		edge[v][u] = edge[u][v] = 10001 ;
		spoj_assert( tong >= 0 ) ;
		u = v ;
	}
	
	spoj_assert( start == u ) ;
	FOR(u,1,n)
	FOR(v,1,n) spoj_assert( edge[u][v] > 10000 ) ;
	return 0 ; 
}
