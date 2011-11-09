# -*- Coding: UTF-8 -*-

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
	taille=sum([len(i+[0]) for i in table])
	res=['']*taille
	i,mx=0,3
	while i<mx:
		j=0
		for disque in uns(table[i]):
			res[j]+=' '*(taille-disque)+'='*disque*2+' '*(taille-disque+4)
			j+=1
		i+=1
	for line in uns(res): print line

def uns(table):
	res=[]
	for i in table: res=[i]+res
	return res

def saut(i,j,t):
	pass
	
def hanoi(n,i,j,k,t):
	if n==1: t[i],t[j]=t[i][:-1],t[j]+[t[i][-1]]
	hanoi(n-1,i,k,j,t)
	hanoi(1,i,j,k,t)
	hanoi(n-1,k,j,i,t)
	hanoi_print(t)
##############################
# Corps du programme

##for i in range(13): print fibon(i)

table=[[1,2,3,4,5,6,7],[],[]]
hanoi_print(table)