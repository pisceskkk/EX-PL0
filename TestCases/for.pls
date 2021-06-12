program pp;
var
    ch: char;
    i, j, x: integer;
begin
    x:=2;

    for ch:='a' to 'z' do
     begin
     if ch='k'
       then call write(ch);
      if ch='o'
       then call write(ch)
     end;


   for i := 1 to 10 do
        for j := 10 downto i-1 do
            begin
            if i=7
              then call write(j)
            end
end.
