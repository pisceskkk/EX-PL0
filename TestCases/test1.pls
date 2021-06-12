program main;
    var x,y:real;
        i:integer;
begin
    y := 9.0;
    x := -2.3E-2;
    x := (x)*1.2;
    repeat
        i := 0;
        repeat
            call write(x);
            i := i + 1
        until i>2;
        y := y+0.5
    until (y > 10.0)
end.
