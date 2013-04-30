program quicksort;

var
   i   : integer;
   tab : array [1..5] of integer;

procedure switch(a, b : integer);
var aux	: integer;   
begin
   aux := tab[a];
   tab[a] := tab[b];
   tab[b] := aux;
end;

procedure qsort(debut, fin : integer );
var i, lim : integer;
begin
   if debut < fin then
   begin      
      lim := debut;
      i := debut + 1;
      while i <= fin do
      begin	 	 
	 if tab[i] < tab[debut] then
	 begin
	    lim := lim+1;
	    switch(lim, i);
	 end;
	 lim := lim+1;
	 switch(debut, lim);
	 qsort(debut, lim-1);
	 qsort(lim+1, fin);	 
      end;	 
   end;
end;

begin
   i := 1;
   while i < 6 do
   begin 
      tab[i] := read();
      i := i+1;
   end;
   qsort(1,5);
   i := 1;
   while i < 6 do
   begin 
      write(tab[i]);
      i := i+1;
   end;   
end.
