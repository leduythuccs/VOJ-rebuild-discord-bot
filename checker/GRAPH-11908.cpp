#include <spoj.h>
//#include <cassert>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <cstring>
using namespace std;

/*FILE *spoj_p_in, *spoj_p_out, *spoj_t_out;
#define PIN "in.txt"
#define POUT "ans.txt"
#define TOUT "out.txt"

void spoj_init()
{
	spoj_p_in=fopen(PIN, "r");
	spoj_p_out=fopen(POUT, "r");
	spoj_t_out=fopen(TOUT, "r");
}

#define spoj_assert assert*/

class ConstantArray // Eli Bendersky
{
public:
    ConstantArray(size_t len_, int init_val_ = 0)
    {
        vec = new int[len_];

        from = new size_t[len_];
        to = new size_t[len_];
        top = 0;
        init_val = init_val_;
        len = len_;
    }

    int& operator[](size_t n)
    {
        if (from[n] < top && to[from[n]] == n)
            return vec[n];
        else
        {
            from[n] = top;
            to[top] = n;
            vec[n] = init_val;
            top++;

            return vec[n];
        }
    }

    ~ConstantArray()
    {
        delete[] vec;
        delete[] from;
        delete[] to;
    }

private:
    int* vec;
    size_t* from;
    size_t* to;
    size_t top;
    int init_val;
    size_t len;
};

int n, u, v, k, m;
char ins[10], ans[10];
ConstantArray *c=0;
#define POS(i,j) ((i-1)*n+(j-1))

int main()
{
	spoj_init();
	while (1) {
		fscanf(spoj_p_in, "%s", ins);		
		if (strcmp(ins, "NEW")==0) {
			fscanf(spoj_p_in, "%d%d", &n,&k);					
			spoj_assert(k==0 || k==1);
			if (c!=0) delete c;
			if (k==0) {
				c=new ConstantArray(n*n,0);
				m=0;
			}
			else {
				c=new ConstantArray(n*n,1);
				m=n*n;
			}
			
		} else if (strcmp(ins, "ANY")==0) {
			if (m==0) {
				spoj_assert(fscanf(spoj_t_out, "%d", &u)==1);
				spoj_assert(u==-1);
			} else {
				spoj_assert(fscanf(spoj_t_out, "%d%d", &u, &v)==2);
				spoj_assert((*c)[POS(u,v)]==1);
				--m;
				(*c)[POS(u,v)]=0;				
			}
		} else if (strcmp(ins, "ADD")==0) {
			fscanf(spoj_p_in, "%d%d", &u, &v);
			if ((*c)[POS(u,v)]==0) {
				++m;
				(*c)[POS(u,v)]=1;
			}
		} else if (strcmp(ins, "DEL")==0) {
			fscanf(spoj_p_in, "%d%d", &u, &v);
			if ((*c)[POS(u,v)]==1) {				
				--m;
				(*c)[POS(u,v)]=0;						
			}
		} else if (strcmp(ins, "EDG")==0) {
			fscanf(spoj_p_in, "%d%d", &u, &v);
			spoj_assert(fscanf(spoj_t_out, "%s", ans)==1);			
			spoj_assert(strcmp(ans,"YES")==0 || strcmp(ans,"NO")==0);
			spoj_assert((*c)[POS(u,v)]==((strcmp(ans,"YES")==0)));			
		} else if (strcmp(ins, "END")==0) {
			break;
		}
	}
    return 0;
}
