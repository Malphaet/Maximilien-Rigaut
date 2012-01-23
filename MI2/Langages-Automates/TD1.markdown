# TD1 #
## Exercice n°1 ##

## Exercice n°2 ##

## Exercice n°3 ##

Soit V un alphabet $a,b \in V, u,v,x,t \in V*$

Mq $au=bv => a=u , b=v$
:  $<=> 1+\|u\| = 1+\|v\|$
:  $=> u=v$

Mq $xu = xv => u=v$
:  Si x=\epsilon alors u=v
:  On sait que \forall i \in \[1...\|xu\|\] (xu)_i = (xv)_i
:  Alors \forall i \in \[\|x\|...\|xu\|\] => u_(i-\|x\|) = v_(i-\|x\|)
:  => u=v

Mq (xu=yv \and \|x\| =\|y\|) => u=v
:  Si x=\epsilon u=v
:  \forall x,y \in V^n  xu=yv => x=y=u=v
:  Soient x,y \in V^(n+1) : \exista,b \in V \exist t,z \in V^n
:  x=at et y=bz atu=bzu => tu=zv et a=b donc t=z et u=v
:  x=y

Mq xu=yv \[x\] < \[y\]
:  On pose y\' \in V^(\[x\]) le prefixe de y de taille \|x\]
:  $\exist y'' \in V* y = y'y'' 
:  xu=y'y'', \[x\]=\[y'\]
:  x=y' et u=y''v
:  x prefixe de y => v suffixe de u

## Exercice n°4 ##

(<=) facile \forall p,q \in \mathBB(N) \lambda^p\lambda^q=\lambda^(p+q)=\lambda^p\lambda^q
(=>) Supposont que \|u\| <=\|v\|
Raisonnons par reccurence sur |v|-|u|
:  Si |v| - |u| = 0: alors u=v=\lambda

This is madness

(=>) On pose u=\lambda^p
Alors uv=vu 
:  => v[0:|u|]=\lambda^p
:  => v[|u|:|u|+|v|]=\lambda^
