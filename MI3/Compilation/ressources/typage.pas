program typage;
var
   a : integer;
   b : boolean;

begin
   a := 5;
   b := true;
   if (b or (a < 4)) then write (4) else write (5);
end.