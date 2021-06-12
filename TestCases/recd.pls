program main;
    var shape : integer;
    var date : record
        year : real;
        month : real;
        day : real;
        case shape: integer  of
        1:  (casetest1, casetest2: integer);
        2:  (casetest11, casetest22: real);
    end;

begin
    shape := 2;

    date.day := 365;
    date.month := date.day/30;
    date.year := date.month / 12;


    if ((date.year > 1.0138) and (date.year - 1.0138 < 0.0001)) or ((date.year < 1.0138) and (1.0138 - date.year < 0.0001)) then
        if (shape = 1) then
        begin
            date.casetest1 := 1;
            date.casetest2 := -1.01;
            call write(date.casetest2)
        end
        else
        begin
            date.casetest11 := 0.01;
            date.casetest22 := -1;
            if (date.casetest11>0.0) then
            call write(date.casetest22)
        end

    else
        call write(0)

end.