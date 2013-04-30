program addmult;

var a, b, op : integer;
   isadd     : boolean;

function add(a, b : integer) : integer;
begin
   add := a + b;  
end;

function mult(a, b : integer) : integer;
begin
   mult := a * b;  
end;

begin
   a := read();
   b := read();
   isadd := (read() = 1);
   if isadd then write(add(a,b))
   else write(mult(a,b));
end.
      