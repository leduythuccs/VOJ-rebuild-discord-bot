#include <cstdio>
#include "spoj.h"
#include <iostream>
#include <cstring>
using namespace std ;

#define NMAX 2200
char s[NMAX],p[NMAX];

int main()
{
	spoj_init();  

	fscanf(spoj_p_in, "%s", s) ;  
	int ret;    
	fscanf(spoj_p_out, "%d", &ret);  

	fscanf(spoj_t_out,"%s",p);
	spoj_assert(strlen(p)==ret);
	for (int i=0; i<ret; i++)  
	  spoj_assert(p[i]==p[ret-i-1]);   	

	int l=strlen(s);
	int j=0;
	for (int i=0; i<ret; i++)
	{
		while (s[j]!=p[i] && j<l) j++;
		spoj_assert(j<l);
		j++;
	}
	return 0;
}
