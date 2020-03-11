#include <spoj.h>
#include <stdio.h>
#include <string.h>

int main() 
{
   int L, R, ret, ans,
       n, Left[100], Right[100];
   
   spoj_init();
   
   fscanf(spoj_p_out, "%d%d", &L, &R);
   ans = L + R;
   
   fscanf(spoj_t_out, "%d%d", &L, &R);
   ret = L + R;
   
   spoj_assert(ret == ans);
   
   fscanf(spoj_p_in, "%d", &n);
   for (int i = 1; i <= n; ++i) fscanf(spoj_p_in, "%d", &Left[i]);
   for (int i = 1; i <= n; ++i) fscanf(spoj_p_in, "%d", &Right[i]);
   
   int maxX = (1 << (n-1));
   
   for (int x = 0; x <= maxX; ++x) {
       int sumL = 0, sumR = 0;
       
       for (int i = 0; i < n; ++i)
           if ( (x >> i) & 1 == 1 ) sumL += Left[i+1];
              else sumR += Right[i+1];
       
       spoj_assert(L > sumL || R > sumR);
           
   }
   
   return 0;
}
