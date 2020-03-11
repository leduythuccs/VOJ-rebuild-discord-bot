#include <cmath>
#include <cstdio>
#include <cstdlib>

using namespace std;

const int
        RV_POSITIVE = 0,
        RV_NEGATIVE = 1,
        RV_INTERNALERROR = 2;
const int
        MAX_NUMSTRLEN = 64,
        TP_DOUBLE = 1,
        TP_CHAR = 2,
        TP_EOF = 3;

double epsilon=0.0001;

// <0-255> normal, -1 white, -2 eof

class lexem
{
private:
    char c;
    double d;

public:

    int type;
    
    lexem get ()
    {
        type = TP_EOF;
        return *this;
    }

    lexem get (char _c)
    {
        type = TP_CHAR;
        c = _c;
        return *this;
    }

    lexem get (double _d)
    {
        type = TP_DOUBLE;
        d = _d;
        return *this;
    }

    static bool equal (lexem a, lexem b)
    {
        if (a.type != b.type) return false;
        if (a.type==TP_EOF) return true;
        if (a.type==TP_CHAR) return (a.c==b.c);
        return (fabs(a.d-b.d)<=epsilon);
    }
};


class myFileReader
{
    char buf[MAX_NUMSTRLEN+2];
    bool last_was_whitespace;
    int buf_pos, buf_end;
    lexem last;

public:

    myFileReader ()
    {
        last_was_whitespace=true;
        buf_pos=buf_end=0;
    }

    lexem getChar (FILE *f)
    {
        bool white;
        char ch;
        if (!last_was_whitespace && buf_pos<buf_end)
        {
            buf_pos++;
            if (buf[buf_pos-1]==' ') last_was_whitespace=true;
            return last.get(buf[buf_pos-1]);
        }
        do
        {
            ch=getc (f);
            if (ch==EOF)
            {
                if (last_was_whitespace)
                    return last.get();
                else
                {
                    last_was_whitespace=true;
                    return last.get(' ');
                }
            }
            if (ch==' ' || ch=='\n' || ch=='\t' || ch=='\r')
                white=true;
            else white=false;
        }
        while (white && last_was_whitespace);
        if (white)
        {
            last_was_whitespace=true;
            return last.get (' ');
        }
        if (!last_was_whitespace)
            return last.get (ch);
        last_was_whitespace=false;
        bool is_a_number = true, has_had_dot = false;
        buf_pos=0;
        buf_end=0;
        while (buf_end<MAX_NUMSTRLEN)
        {
            if (ch=='\n' || ch=='\t' || ch=='\r')
                ch=' ';
            buf[buf_end]=ch;
            if (ch==' ')
                break;
            if (( ch<'0' || ch>'9' ) && (ch!='.' || has_had_dot) && ch!='-' && ch!='+' && ch!='e' && ch!='E')
            {
                is_a_number=false;
                break;
            }
            if (ch=='.') has_had_dot=true;
            ch=getc(f);
            if (ch==EOF) ch=' ';
            buf_end++;
        }
        if (buf_end==MAX_NUMSTRLEN) is_a_number=false;
            else buf_end++;
        if (!is_a_number)
        {
            buf_pos=1;
            return last.get(buf[0]);
        }
        else
        {
            double f;
            buf[buf_end]=0;
            char *sc;
            f=strtod (buf, &sc);
            if(*sc)
            {
                buf_end=1;
                buf_pos=0;
                buf[0]=' ';
                return last.get(f);
            }
            buf_pos++;
            return last.get(buf[0]);
        }
    }
};

int main(int argc, char *argv[]) {
        FILE *file1 = fdopen(3, "r");
        if (!file1)
                exit(RV_INTERNALERROR);
        
        FILE *file2 = fdopen(4, "r");
        if (!file2)
                exit(RV_INTERNALERROR);
        
        epsilon*=1.00001;
        
        myFileReader f1, f2;
        lexem l1 = f1.getChar(file1);
        lexem l2 = f2.getChar(file2);
        while (lexem::equal(l1,l2))
        {
                if (l1.type==TP_EOF)
                    exit(RV_POSITIVE);
                l1 = f1.getChar(file1);
                l2 = f2.getChar(file2);
        };
        return RV_NEGATIVE;
}
