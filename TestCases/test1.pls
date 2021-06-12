program main;
    var x,y:real;
        i:integer;
    procedure add(i :integer);
    var j,k:integer;
    begin
        i := i+1;
        j := i+2;
        k := j+2;
        j := k+2;
        k := j+2;
        call write(j)
    end;
begin
    y := 9.0;
    x := -2.3E-2;
    x := (x)*1.2;
    i := 10;
    call add(i)
end.
