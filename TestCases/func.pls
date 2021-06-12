program main;
    var c,a,b:integer;

    function GCD1 (m, n : integer) : integer ; forward;
    function GCD2 (m, n : integer) : integer ; forward;

    function GCD1 (m, n : integer): integer;
    begin
        if n=0 then GCD1 := m else GCD1 := GCD2(n, m mod n);
    end;

    function GCD2 (m, n : integer): integer;
    begin
        if n=0 then GCD2 := m else GCD2 := GCD1(n, m mod n);
    end;

    function  Fibonacci(m, n : integer) : integer;
    begin
        if m>10
            then Fibonacci  := m
        else
            Fibonacci  := Fibonacci(m+n,m);
    end;

begin
    a := 1;
    b := 1;
    c := Fibonacci(a,b);
    call write(c);
    a := GCD2(c*2,64);
    call write(a)
end.