# -*- coding:utf8 -*-

##############################
# Copyleft Maximilien Rigaut
# TP 3.5 Tri recursif
##############################

from TP2_0 import *

############################
# Declaration des fonctions
#############

def listeAdj(*l):
	"Matrice d'adjaence courte"
	mx,table=0,[]
	for t in l: mx=max(mx,max(t))
	for i in range(mx+1): table.append([])
	for op in l:
		table[op[0]].append(op[1])
		table[op[1]].append(op[0])
	return table

def liste_en_matrice(liste):
	table,mx=[],len(liste)
	for i in range(mx): table.append([0]*(mx))
	i=0
	while i<mx:
		for elt in liste[i]: table[i][elt]=1
		i+=1
	return table

def matrice_en_liste(matrice):
	mx=len(matrice)
	table=[]
	for i in range(mx):
		table.append([])
	i,j=0,0
	while i<mx:
		while j<mx:
			if matrice[i][j]:
				table[i].append(j)
				table[j].append(i)
			j+=1
		i+=1
		j=i
	return table

def l_stable(n):
	table=[]
	for l in range(n): table.append([])
	return table

def l_clique(n):
	table=[]
	for i in range(n):
		table.append(range(n))
		table[i].pop(i)
	return table


def l_nb_arretes(table):
	ret=0
	for ligne in table: ret+=len(ligne)
	return ret

def l_degre_total(table): return l_nb_arretes(table)

def l_connecte(table,i,j):
	if j in table[i]: return true
	return false

def m_connecte(table,i,j):
	if table[i][j]: return true
	return false

def l_chemin(table,i,j,points=[]):
	"Parcour de chemin de i a j"
	points.append(i)
	#print i,j,':',points
	for next in table[i]:
		#print next
		if next not in points:
			if next==j:
				return True
			else:
				if(l_chemin(table,next,j,points=points[:])): return True

def l_connexe(table):
	i,mx,point=0,len(table),[]
	while i<mx:
		if len(table[i])<1: return False
		for elt in table[i]:
			if elt not in point: point.append(elt)
		i+=1
	return len(point)==mx

############################
# Corps du programme
#############

liste=listeAdj([0,1],[0,2],[1,3],[2,3],[3,4],[3,5])
liste2=[[1],[0,2],[1]]
matriceLpr(liste)

#matrice=liste_en_matrice(liste)
#liste=matrice_en_liste(matrice)
#matriceLpr(liste)
#matriceLpr(matrice)
#matriceLpr(lStable(6))
#matriceLpr(lClique(6))
#print l_nb_arretes(liste)
print l_chemin(liste,0,5)
print l_connexe(liste2)
matriceLpr(liste_en_matrice(liste2))