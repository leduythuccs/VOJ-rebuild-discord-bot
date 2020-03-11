#include <spoj.h>
#include <stdio.h>
#include <string.h>

int n, a[1005][1005], x, y, z, deg[1005], q[1005];
bool exist[1005][1005], correct;

bool cycle() {     
     for (int i = 1; i <= n; ++ i) deg[i] = 0;
     
     for (int i = 1; i <= n; ++ i)
         for (int j = 1; j <= n; ++ j)
             if (a[i][j] == 1) {
                exist[i][j] = true;
                ++ deg[j];
             }
             else exist[i][j] = false;
             
     int fi = 1, la = 0;
     for (int i = 1; i <= n; ++ i)
         if (deg[i] == 0) q[++ la] = i;
     while (fi <= la) {
           int i = q[fi ++];
           for (int j = 1; j <= n; ++ j)
               if (a[i][j] == 1 && exist[i][j]) {
                  exist[i][j] = false;
                  -- deg[j];
                  if (deg[j] == 0) q[++ la] = j;
               }      
     }
     
     for (int i = 1; i <= n; ++ i)
         for (int j = 1; j <= n; ++ j)
             if (exist[i][j]) return true;
     return false;
}

int main() {
    spoj_init();
    
    fscanf(spoj_p_in, "%d", &n);
    for (int i = 1; i <= n; ++ i)
        for (int j = 1; j <= n; ++ j) fscanf(spoj_p_in, "%d", &a[i][j]);
    
    x = y = z = -5;
    fscanf(spoj_t_out, "%d%d%d", &x, &y, &z);

    if (x == -1 && y == -1 && z == -1) {
       if (cycle()) correct = false;
       else correct = true;
    } 
    else {
         if (x < 1 || x > n || y < 1 || y > n || z < 1 || z > n) correct = false;
         else correct = (a[x][y] == 1 && a[y][z] == 1 && a[z][x] == 1);
    }    

    spoj_assert(correct);
}
