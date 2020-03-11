{$R-,Q-}
const fi = '';
        fo = '';
        vc = 790972;
var
        f : text;
        a,c : array[0..100000] of int64;
        b,d : array[0..100000] of int64;
        key,n,i,j,h,k,first,last,i1 : longint;
        res,res1,s : int64;
        procedure quick(l1,r1 : longint);
        var
                i1,j1,temp,pivot : longint;
        begin
                if l1 >= r1 then exit;
                pivot := B[(l1 + r1) div 2];
                i1 := l1;
                j1 := r1;
                repeat
                        While b[i1] < pivot do inc(i1);
                        while b[j1] > pivot do dec(j1);
                        if i1 <= j1 then
                        begin
                                if i1 < j1 then
                                begin
                                        temp := a[i1];
                                        a[i1] := a[j1];
                                        a[j1] := temp;
                                        temp := b[i1];
                                        b[i1] := b[j1];
                                        b[j1] := temp;
                                End;
                                inc(i1);
                                dec(j1);
                        End;
                Until i1 > j1;
                quick(l1,j1);
                quick(i1,r1);
        End;
        function tinh(l1,r1 : longint) : int64;
        begin
                j := 0;
                b[0] := 0;
                d[0] := 0;
                for i := l1 to r1 do
                Begin
                        inc(j);
                        b[j] := b[j-1] + a[i];
                        D[j] := d[j-1] + a[i]*b[j-1];
                End;

                For h := 2 to k do
                begin
                        j := 0;
                        for i := l1 to r1 do
                        begin
                                inc(j);
                                b[j] := d[j] mod vc;
                                d[j] := d[j-1] + a[i]*b[j-1];
                        End;
                End;
                tinh := b[j] mod vc;
        End;
begin
        assign(f,fi);
        reset(f);
        readln(f,n,k);
        For i := 1 to n do
                readln(f,a[i],b[i]);
        Close(f);
        quick(1,n);
        key := 0;
        For i := 1 to n do
                if (i = 1) or ((i > 1) and (b[i] <> b[i-1])) then
                begin
                        inc(key);
                        c[i] := key;
                End
                else c[i] := key;
        res := tinh(1,n);
        For i1 := 1 to n do
        Begin
                if (i1 = 1) or (c[i1] <> c[i1-1]) then first := i1;
                if (i1 = n) or (c[i1] <> c[i1+1]) then
                Begin
                        last := i1;
                        res1 := tinh(first,last);
                        res := (res mod vc) - (res1 mod vc);
                        if res < 0 then res := res + vc;
                End;
        End;
        Assign(f,fo);
        rewrite(f);
        writeln(f,res mod vc);
        Close(f);
End.
