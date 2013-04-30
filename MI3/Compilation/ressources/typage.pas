program typage;
var
   a : integer;
   b : boolean;
   c: integer;
begin
   a := 5;
   b := true;
   c := 2;
   if (b or (a < 4)) then write (4) else write (5);
end.
