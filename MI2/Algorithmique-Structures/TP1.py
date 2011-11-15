# -*- Coding: UTF-8 -*-

##############################
# Copyleft Maximilien Rigaut
# TP 3.5 Tri recursif
##############################

import random

##############################
# Definition des Fonctions
# - - - - - - - - - - - - -
# Exercice 1
# - - - - - - 

double = lambda x: 2*x

def double_tab(t): return [2*i for i in t] # Shortest way

# def double_tab(t):  # Cleanest Way
#	i,mx=0,len(tab)
#	while i<mx:
#		t[i]*=2
#		i+=1

def compare(x,y):				# Very useless
	if x==y: return 'equal'
	if x>y: return 'bigger'
	return 'smaller'

# - - - - - - - - - - - - -
# Exercice 2
# - - - - - - 

def randrange(x):					# Stupid but OK
	i,t,res=0,range(x),[]
	while i<x:
		nb=random.randint(x-i)
		res,i=[t[nb]]+res,t.pop(nb)
	return t

t1= range(100)
t2= range(99,-1,-1)
t3= range(100)
random.shuffle(t3)

# - - - - - - - - - - - - -
# Exercice 3
# - - - - - - 

def maximum(t):
	i=t[0]
	for el in t:
		if el>i: i=el
	return i

def minimum(t):
	i=t[0]
	for el in t:
		if el<i: i=el
	return el

# max,min=len(l)

def min_max(t):
	i,j=t[0],t[0]
	for el in t:
		if el<i:
			i=el
		else:
			if el>j: j=el
	return i,j

def tri_permut(t):
	i,j=0,len(t)
	while j>0:
		if t[i]>t[i+1]: t[i],t[i+1]=t[i+1],t[i]
		i+=1
		if i>j-2: i,j=0,j-1
	return t

# - - - - - - - - - - - - -
# Exercice 4
# - - - - - - 

def sort(t):
	lng=len(t)
	if lng<2: return t
	return fusionSort(sort(t[:lng/2]),sort(t[lng/2:]))

def fusionSort(t1,t2):
	i,j,m1,m2=0,0,len(t1),len(t2)
	res=[]
	while i<m1 and j<m2:
		if t1[i]<t2[j]:
			res.append(t1[i])
			i+=1
		else:
			res.append(t2[j])
			j+=1
	res=res+t1[i:]+t2[j:]
	return res

# #sort=((len(t)+1)*len(l))/2

def tri_fouillis(t):
	while not sorted(t):
		i=random.randint(0,len(t)-2)
		if t[i]>t[i+1]: t[i],t[i+1]=t[i+1],t[i]
	return t

def sorted(t):
	i,mx=0,len(t)
	while i<mx-1:
		if t[i]>t[i+1]: return False
		i+=1
	return True
##############################
# Corps du programme

print maximum(t1),minimum(t2),min_max(t1)

#print t2
#print tri_permut(t2)

#t=sort(t3)
#print t,sorted(t)

print tri_fouillis([0,1,4,2,5,778,5,57,89,55,6])