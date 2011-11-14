# -*- Coding: UTF-8 -*-

##############################
# Copyleft Maximilien Rigaut
# TP 3.5 Tri recursif
##############################

#############################
# Declarations de fonctions
###############

def matriceAdj(*l):
	"Le t represente la taille du graphe. Les l sont les arretes reliees sous forme de tableau"
	table=[]
	t=0
	for ligne in l:
		t=max(t,max(ligne))
	for i in range(t+1):
		table.append([0]*(t+1))
	for lien in l:
		table[lien[0]][lien[1]]=1
		table[lien[1]][lien[0]]=1
	return table
def matriceLpr(tab):
	for ligne in tab:
		print ligne
def stable(n):
	"Renvoie le stable a n sommets"
	table=[]
	for i in range(n):
		table.append([0]*n)
	return table
def clique(n):
	"Renvoie la clique a n sommets"
	table=[]
	for i in range(n):
		table.append([1]*(n))
		table[i][i]=0
	return table
def voisins(table,i):
	"Renvoie les voisins de i"
	v,somm=[],0
	mx=len(table)
	while somm<mx:
		if table[i][somm]: v.append(somm)
		somm+=1
	return v
def nb_arretes(table):
	nb=0
	for ligne in table:
		for somm in ligne:
			if somm: nb+=1
	return nb
def degre_total(table):
	"Degre des sommets"
	nb=0
	for ligne in table:
		for i in ligne:
			if i: nb+=1
	return nb



#############################
# Corps du programme
###############
# Qul

#matrice=matriceAdj([0,1],[0,2],[2,3],[1,3],[3,4],[3,5])
#matriceLpr(matrice)
#print voisins(matrice,0)
#print nb_arretes(matrice)
#print degre_total(matrice)
#matriceLpr(stable(6))

