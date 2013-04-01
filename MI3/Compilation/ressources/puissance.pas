program puissance;

function pow(a, n : integer) : integer;
var c : integer;  
begin
   if n = 0 then pow := 1
   else     
      if n mod 2 = 0 then
      begin
	 c := pow(a, n/2);
	 pow := c*c;	
      end
      else pow := a* pow(a, n-1);
end;

begin
   write(pow(2,3));
end.