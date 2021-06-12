program main;
    var k,i,j:integer;
begin
    j := 1;
    i := 1;
    repeat
        if j>100
            then call write(j);
        k := j ;
        j := i+j;
        i := k
    until j >1000
end.
