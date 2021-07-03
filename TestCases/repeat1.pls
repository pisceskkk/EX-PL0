program main;
   var k,i,j:integer;
begin
   j := 1;
   i := 1;
   repeat
      if ((j < 100) and (j>10))
           then call write(j);
        k := j ;
      j := i+j;
      i := k
   until j >100
end.
