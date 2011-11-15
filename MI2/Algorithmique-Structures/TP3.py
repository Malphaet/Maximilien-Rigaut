# -*- Coding: UTF-8 -*-

##############################
# Copyleft Maximilien Rigaut
# TD3 Graphes ponderes
##############################


##############################
# Importation des Modules


##############################
# Definition des Classes

class grapheP():
	"Graphe pondéré"
	def __init__(self,*l):
		mx=0
		for elt in l: mx=max(mx,elt[1])
		self.longeur=mx
		self.table=[]
		i=0
		for i in range(self.longeur):
			self.table.append([])
		self.ajouterArrete(l)
	def augmenterTaille(self,n):
		if n>self.longeur:
			for i in range(n-self.longeur):
				self.table.append([])
	def ajouterArrete(self,l):
		for op in l:
			self.table[op[0]].append(op[1:])	
	def afficher(self):
		for l in self.table:
			print l
	def voisins(self,i):
		temp=[]
		for elt in self.table[i]:
			temp.append(elt[0])
		return temp


##############################
# Definition des Fonctions

def raw_parcourtP(table,i,j,Mtemps,points=[],temps=0):
	"Utilise un tableau(graphe), retourne un entier"
	points.append(i)
	#print "Point",points
	for next in table[i]:
		if next[0] not in points:
			#print next
			if next[0]==j:
				#print "temps",next[0],next[1]
				Mtemps.append(temps+next[1])
				#print Mtemps
			else:
				raw_parcourtP(table,next[0],j,Mtemps,points=points[:],temps=next[1])
				

def parcourtP(matrice,i,j):
	Mtemps=[]
	raw_parcourtP(matrice.table,i,j,Mtemps)
	if len(Mtemps)> 0: return min(Mtemps)
	return False		
##############################
# Corps du programme

inf=float("Infinity")
matrice=grapheP([0,1,8],[0,2,7],[2,4,4],[0,3,1],[3,4,2])
matrice.afficher()
#print matrice.voisins(1)
tmp=parcourtP(matrice,0,4)
print "Temps minimal de parcourt:",tmp
