program main;
   var d,a:integer;
begin
   a := 2;
   case a*2 of
      2 : d:=0;
      4 : d:=1;
      6 : d:=2
   end;
   case d of
      1,4 : call write (-1);
      2,5 : call write (0);
      3,6,7 : call write (1)
   end
end.

