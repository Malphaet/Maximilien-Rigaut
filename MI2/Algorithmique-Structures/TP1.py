# -*- Coding: UTF-8 -*-

##############################
# Copyleft Maximilien Rigaut
# TP 3.5 Tri recursif
##############################

from math import ceil,floor

##############################
# Definition des Fonctions

def sort(list):
	lng=len(list)
	if lng<2:
		return list
	else:
		return fusionSort(sort(list[:ceil(lng/2.)],list[floor(lng/2.):]))
def genList(n=5):
	list=[]
	for i in range(n):
		list.append(int(rand()*n*10000))
	return list
##############################
# Corps du programme

print genList(13)
