#include "spoj.h"
#include <stdio.h>
#include <string.h>

#define foru(i,a,b) for(int i = int(a); i <= int(b); ++i)
#define ford(i,b,a) for(int i = int(b); i >= int(a); --i)
#define rep(i, n) for(int i = 0; i < int(n); ++i)
#define all(a) a.begin(),a.end()
#define size(a) int(a.size())
#define fill(a,x) memset(a, (x), sizeof(a))


const int MAX_N = 222;
int a[MAX_N], b[MAX_N];

int main()
{
   spoj_init();

   /* Check for AC */

   fscanf(spoj_p_out, "%d", &a[1]);
   fscanf(spoj_t_out, "%d", &b[1]);
   if (a[1] == -1 || b[1] == -1) return int(a[1] != b[1]);

   int n, m;
   fscanf(spoj_p_in, "%d%d", &n,&m);
   foru(i,2,n) fscanf(spoj_t_out, "%d", &b[i]);

   foru(i,1,n) {
      if (b[i] < 1 || b[i] > n) return 1;
      foru(j,i+1,n)
         if (b[i] == b[j]) return 1;
   }

   rep(id,m) {
      int t,x,y,v;
      fscanf(spoj_p_in, "%d%d%d%d", &t,&x,&y,&v);
      if (t == 1) {
         bool ok = false;
         for(int i = x; i <= y; ++i)
            if (b[i] > v) return 1;
            else if (b[i] == v) ok = true;
         if (!ok) return 1;
      }
      else {
         bool ok = false;
         for(int i = x; i <= y; ++i)
            if (b[i] < v) return 1;
            else if (b[i] == v) ok = true;
         if (!ok) return 1;
      }
   }
   return 0;
}
