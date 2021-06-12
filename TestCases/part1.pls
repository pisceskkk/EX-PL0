program main;
   var i,j,index,temp,k,x:integer;
begin
    k:=0;
    x:=10;
    for index:= 1 to x do
        begin
        case index mod 3 of
            2: k:=k+0;
            1: k:=k+1;
            0: k:=k+2
            end
        end;
    call write(k);


    repeat
        case k mod 2 of
            1: call write (1);
            0: call write (0)
        end;
        k:=k/2
    until k <2;
    call write (k)

end.
