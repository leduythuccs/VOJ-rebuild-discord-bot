#include <spoj.h>
#include <stdio.h>

#define maxn 1024

int ret, ans, n, diff, 
    br[maxn + 1][maxn + 1], ba[maxn + 1][maxn + 1];
char c;

int main() {
    spoj_init();    

    fscanf(spoj_p_out, "%d\n", &ans);
    fscanf(spoj_t_out, "%d\n", &ret);
    
    spoj_assert(ret == ans);
    
    fscanf(spoj_p_in, "%d\n", &n);
    for (int i = 1; i <= n; ++ i) {
        for (int j = 1; j <= n; ++ j) {
            fscanf(spoj_p_in, "%c", &c);    
            ba[i][j] = c - '0';
        }
        fscanf(spoj_p_in, "\n");
    }
    
    for (int i = 1; i <= n; ++ i) {
        for (int j = 1; j <= n; ++ j) {
            fscanf(spoj_t_out, "%c", &c);    
            br[i][j] = c - '0';
        }
        fscanf(spoj_t_out, "\n");
    }    
    
    diff = 0;
    for (int i = 1; i <= n; ++ i)
        for (int j = 1; j <= n; ++ j)
            if (ba[i][j] != br[i][j]) ++ diff;
        
    spoj_assert(diff == ret);
    
    return 0;    
}
