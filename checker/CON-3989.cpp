#include <spoj.h>
#include <stdio.h>
#include <string.h>

#define maxn 100001

int a[maxn + 2], b[maxn + 2], c[maxn + 2], n;
char name[100];

int main() {           
    spoj_init();
    
    fscanf(spoj_p_in, "%d", &n);
    for (int i = 1; i <= n; ++ i) fscanf(spoj_p_in, "%d", &b[i]);
        
    for (int i = 1; i <= n; ++ i) fscanf(spoj_t_out, "%d", &a[i]);
    a[0] = a[n];
    a[n+1] = a[1];
        
    bool correct = true;
        
    for (int i = 1; i <= n; ++ i) {
        c[i] = a[i-1] + a[i] + a[i+1];
        if (c[i] != b[i]) correct = false;
    }
    
    spoj_assert(correct);    
}
