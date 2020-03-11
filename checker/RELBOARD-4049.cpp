#include <spoj.h>
#include <stdio.h>

/*
FILE *spoj_p_in, *spoj_t_out, *spoj_score;

void spoj_init() {
     spoj_p_in  = fopen("r.in", "r");
     spoj_t_out = fopen("r.out", "r");
     spoj_score = fopen("score.out", "w");
}

void spoj_assert(bool b) {
     if (b == true) fprintf(spoj_score, "Accepted.\n");
     else fprintf(spoj_score, "Wrong Answer.\n");
}

*/

#define maxn 1000

int n, a[maxn + 5][maxn + 5], maxT, T[maxn + 5];
bool correct;

int main() {
    spoj_init();
    
    fscanf(spoj_p_in, "%d", &n);
    for (int i = 1; i <= n; ++ i)
        for (int j = 1; j <= n; ++ j) fscanf(spoj_p_in, "%d", &a[i][j]);
        
    for (int i = 1; i <= n; ++ i) T[i] = -1;
    fscanf(spoj_t_out, "%d", &maxT);
    for (int i = 1; i <= n; ++ i) fscanf(spoj_t_out, "%d", &T[i]);
    
    correct = true;
    for (int i = 1; i <= n; ++ i)
        if (T[i] <= 0) correct = false;

    int mT = 0;
    for (int i = 1; i <= n; ++ i)      
        if (mT < T[i]) mT = T[i];
    if (mT != maxT) correct = false;
    
    for (int i = 1; i <= n; ++ i)
        for (int j = 1; j <= n; ++ j) {
            switch (a[i][j]) {
                   case 0:
                        if (T[i] != T[j]) {
                           correct = false;
                        }
                        break;
                   case 1:
                        if (T[i] >= T[j]) {
                           correct = false;
                        }
                        break;
                   case -1:
                        if (T[i] <= T[j]) {
                           correct = false;
                        }
                        break;
                   case 2:
                        if (T[i] > T[j]) {
                           correct = false;
                        }
                        break;
                   case -2:
                        if (T[i] < T[j]) {
                           correct = false;
                        }
                        break;
                   case 3:
                        if (T[i] == T[j]) {
                           correct = false;
                        }
                        break;
            }    
        }

    spoj_assert(correct);
    fprintf(spoj_score, "%d\n", maxT);

    return 0;
}
