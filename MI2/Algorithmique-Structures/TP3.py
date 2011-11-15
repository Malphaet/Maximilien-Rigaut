# -*- coding:utf8 -*-

##############################
# Copyleft Maximilien Rigaut
# TD3 Graphes ponderes
##############################

##############################
# Definition des Classes

class grapheP(object):
	"Graphe pondéré"
	def __init__(self,*l):
		mx=0
		for elt in l: mx=max(mx,elt[1],elt[0])
		self.longeur=mx
		self.table=[]
		for i in range(self.longeur+1):
			self.table.append([])
		self.ajouterArrete(l)
	def __len__(self): return self.longeur
	def augmenterTaille(self,n):
		if n>self.longeur:
			for i in range(n-self.longeur):
				self.table.append([])
	def ajouterArrete(self,l):
		for op in l: self.table[op[0]].append(op[1:])	
	def afficher(self):
		for l in self.table: print l
	def voisins(self,i):
		temp=[]
		for elt in self.table[i]: temp.append(elt[0])
		return temp

##############################
# Definition des Fonctions

def raw_parcourtP(table,i,j,Mtemps,points=[],temps=0):
	"Utilise un tableau(graphe), retourne un entier"
	points.append(i)
	for next in table[i]:
		if next[0] not in points:
			if next[0]==j:
				Mtemps.append(temps+next[1])
			else: raw_parcourtP(table,next[0],j,Mtemps,points=points[:],temps=next[1])

def parcourtP(matrice,i,j):
	Mtemps=[]
	raw_parcourtP(matrice.table,i,j,Mtemps)
	if len(Mtemps)> 0: return min(Mtemps)
	return False

def chemins(graphe):
	i,j,mx,res=0,0,len(graphe.table),[ [] for i in graphe.table]
	while i<mx:
		while j<mx:
			res[i].append(parcourtP(graphe,i,j))
			j+=1
		i,j=i+1,0
	return res
##############################
# Corps du programme

if __name__=='__main__':
	inf=float("Infinity")
	matrice=grapheP([0,1,8],[0,2,7],[2,4,4],[0,3,1],[3,4,2])
	matrice.afficher()
	#print matrice.voisins(1)
	tmp=parcourtP(matrice,0,1)
	print "Temps minimal de parcourt:",tmp
	print chemins(matrice)