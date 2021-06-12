program main;
    var d,a,b,k,j,i:integer;
        data : record
            i : integer;
            j : integer;
            k : integer;
            s: real;
            name: char;
        end;
    function  Fibonacci(m, n : integer) : integer;
        begin
            if m>10
                then Fibonacci  := m
            else
                Fibonacci  := Fibonacci(m+n,m);
        end;
    function  encode(m : integer) : integer;
            begin
                case m mod 4 of
                        0 : call write (0);
                        1 : call write (1);
                        2 : call write (10);
                        3 : call write (11)
                end
            end;

    function  fun(flag, n,m: integer) : integer;
            begin
                if flag=0
                    then fun  := encode(n)
                else
                    fun  := Fibonacci(n,m)
            end;

    function  print(n: real) : integer;
            begin
                call write(n);
                print  := 1;
            end;
begin
    data.i := 1;
    data.j := 1;
    data.k := 3;
    data.s:=3e-4;
    data.name:='S';

    d:=fun(1,data.i,data.j);
    call write(d);

    j:=1;
    i:=1;
    repeat
        k := j ;
        j := i+j;
        i := k
    until j >10;
    call write(j);

    for a:= 0 to data.k do
        i:=fun(0,a,0);
    i:=print(data.s-1.01);
    case data.name of
        'S' : call write (11);
        'M' : call write (00)
    end


end.