program main;
    var d,a:real;
    function foo (m: real ) : real;
    begin
        m := m -0.00001;
        foo := m + 3e-2
    end;
begin
    a := 2e-2;
    d := foo(a);
    call write(d);
    if ((d > 0.05) and (d - 0.05 < 0.0001)) or ((d < 0.05) and (0.05 - d < 0.0001)) then
        call write(1)
    else
        call write(0)
end.