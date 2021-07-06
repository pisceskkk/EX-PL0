program pp;
  var n,p:integer;
  procedure p1(n:integer;var p:integer);
     begin
        if n<=1 then p:=1
        else begin
              call p1(n-1,p);
              p:=n*p
        end
     end;
  begin
     call read(n);
     call p1(n,p);
     call write(p)
  end.