# -*- coding:utf8 -*-

##############################
# Copyleft Maximilien Rigaut
# TP7 - Hanoi, Fibo
##############################


##############################
# Definition des Fonctions
# - - - - - - - - - - - - - -
# Fibonacci
# - - - - - -

def sub_fib(text):
	res=''
	for l in text:
		if l=='a':
			res+='ab'
		else:
			res+='a'
	return res

def subo(n,text='a'):
	for i in range(n): text=sub_fib(text)
	return text

def fibo(n,text): return subo(n,text)

def fibon(n):
	if n<2: return "a"
	if n==2: return "ab"
	return fibon(n-1)+fibon(n-2)

# - - - - - - - - - - - - - -
# Hanoi
# - - - - - -

def hanoi_print(table):
	taille=sum([len(i) for i in table])
	def segment(table,h):
		if len(table)>h: return ' '*(taille-table[h])+"="*2*table[h]+' '*(taille-table[h])
		return ' '*2*taille
	for h in range(taille-1,-1,-1): print segment(table[0], h), segment(table[1], h), segment(table[2], h)

def saut(i,j,t):
	hanoi(len(t[i]),i,j,[x for x in range(3) if x not in [i,j]][0],t)
	
def hanoi(n,i,j,k,t):
	if n==1: 
		t[i],t[j]=t[i][:-1],t[j]+[t[i][-1]]
		return hanoi_print(t)
	hanoi(n-1,i,k,j,t), hanoi(1,i,j,k,t),hanoi(n-1,k,j,i,t)
##############################
# Corps du programme

##for i in range(13): print fibon(i)

table=[range(7,0,-1),[],[]]
#hanoi_print(table)
#hanoi(4,0,1,2,table)
saut(0,1,table)