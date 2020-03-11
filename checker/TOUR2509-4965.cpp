#include <spoj.h>
#include <iostream>
#include <algorithm>
using namespace std;
#define max 30000
typedef struct {int u, v;} Edge;
int n, m, m1=0, best, result;
int no[max];
Edge z[max];

bool cmp(Edge A, Edge B)
{
   return (A.u < B.u) || (A.u==B.u && A.v<B.v);
}     
 
void read_data()
{int i, j, k;
  fscanf(spoj_p_in, "%d %d", &n, &m);   
  for (k=1; k <= m; k++)
  { no[k] = 0;
    fscanf(spoj_p_in, "%d %d", &z[k].u, &z[k].v);     
    if (z[k].u > z[k].v) swap(z[k].u, z[k].v);
  } 
  sort(z+1, z+m+1, cmp);  
  fscanf(spoj_p_out, "%d", &best);   
  fscanf(spoj_t_out, "%d", &result);   
}

int yes(int i, int j)
{int L=1, R=m, h=0, k;
  while (L <= R)
  { k = (L+R)/2;
    if (i==z[k].u && j==z[k].v) { h = 1;                                 
                                  break;
                                }  
    else
    if (i<z[k].u || (i==z[k].u && j<z[k].v)) R = k-1;
    else
    if (i>z[k].u || (i==z[k].u && j>z[k].v)) L = k+1;        
  }     
  return h;   
}         

int check(int i, int j)
{int L=1, R=m, h=1, k;
  while (L <= R)
  { k = (L+R)/2;
    if (i==z[k].u && j==z[k].v) { if (no[k] == 1) h = 0;
                                  no[k] = 1;  
                                  break;
                                }  
    else
    if (i<z[k].u || (i==z[k].u && j<z[k].v)) R = k-1;
    else
    if (i>z[k].u || (i==z[k].u && j>z[k].v)) L = k+1;        
  }     
  return h;   
}    

void process()
{int run, k, i, j, e, h;   
   for (k=1; k <= result; k++)
   { fscanf(spoj_t_out, "%d", &h);
     spoj_assert(h >= 2);  
     fscanf(spoj_t_out, "%d", &e);
     for (run=1; run < h; run++)
     { fscanf(spoj_t_out, "%d", &j);
       i = e;
       e = j;
       if (i > j) swap(i, j);
       spoj_assert(yes(i, j) == 1);  
       spoj_assert(check(i, j) == 1);  
     }
     m1 += h-1;
   }    
   spoj_assert(m1 == m);  
   spoj_assert(result <= best); 
}     
 
int main() 
{
    spoj_init();               
    read_data();
    process();
    return 0; 
} 
