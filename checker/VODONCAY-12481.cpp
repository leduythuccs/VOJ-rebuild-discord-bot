#include<spoj.h>
#include<bits/stdc++.h>
using namespace std;

int n, h[4000005], ans, cut[4000005],fall[4000005];

void readInput()
{
	fscanf(spoj_p_in,"%d",&n);
	for(int i=1; i<=n; i++) fscanf(spoj_p_in,"%d",&h[i]);
}
void readAnswer()
{
	fscanf(spoj_p_out,"%d",&ans);
}

void Try(int u)
{
	fall[u] = 1;
	int last = u+h[u]*cut[u];
	for(int i=u+cut[u]; i!=0 && i!=n+1 && i!=last; i+=cut[u])
	{
		fall[i] = 1;
		spoj_assert(!cut[i]);
		int nlast = i+h[i]*cut[u];
		if(cut[u]<0) last = min(last,nlast);
		else last = max(last,nlast);
	}
}

void readOutput()
{
	int res,x;
	spoj_assert(fscanf(spoj_t_out,"%d",&res)==1);
	spoj_assert(res<=ans);
	for(int i=1; i<=res; i++)
	{
		spoj_assert(fscanf(spoj_t_out,"%d",&x)==1);
		spoj_assert(abs(x)>=1 && abs(x)<=n);
		cut[abs(x)] = x/abs(x);
	}
	for(int i=1; i<=n; i++)
		if(cut[i]) Try(i);
	for(int i=1; i<=n; i++)
		spoj_assert(fall[i]);
}
int main()
{
	spoj_init();
    readInput();
    readAnswer();
    readOutput();
    return 0;
}
