program liste;
var
   i   : integer;
   tab : array [1..4] of integer;
       
begin
   i := 1;
   while i <= 5 do
   begin
      tab[i] := i;
      i := i+1;
   end;
   write (tab[1+1+1]);
end.