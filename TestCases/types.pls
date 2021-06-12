program main;
   var date1 : record
      year : integer;
      month : integer;
      day : integer;
       s: real;
       name: char;
   end;

   var date2 : record
       year : integer;
       month : integer;
       day : integer;
       s: real;
       name: char;
    end;

begin
   date1.day := 14;
   date1.month := 2;
   date1.year := 2000;
   date1.s:=0.00019;
   date1.name:='K';

    date2.day := 15;
   date2.month := 3;
   date2.year := 1998;
   date2.s:=2e-4;
   date2.name:='O';


    if (date1.year > date2.year)then
          call write(1)
       else
          call write(0);

    if (date1.month > date2.month) then
            call write(1)
        else
           call write(0);

    if (date1.day > date2.day)then
           call write(1)
        else
           call write(0);

    if (date1.s > date2.s)then
            call write(1)
        else
            call write(0);
    if(date1.name=date2.name)then
            call write(1)
        else
            call write(0)
end.
