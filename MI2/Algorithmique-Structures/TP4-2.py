# -*- coding:utf-8 -*-

##############################
# Copyleft Maximilien Rigaut
# Fonctions iteratives sur les liste de taille finie
##############################


##############################
# Definition des Classes
# Nb: Les classes contiennent ici des methodes
#     càd des fonctions propres ainsi qu'une initialisation.
#     Bonne chance et bonne lecture :)

class List():
	def __init__(self,taille):
		self.__length=taille		# Cet attribt est privé, il ne devrait pas etre appelé
		self.__table=[0]*taille		# Idem
	
	def cons(self,x): self.__table[self.lenght],self.__lenght=x,self.__lenght+1
		
	def vide(self): return len(self)==0
		
	def tete(self): return self[0]
		
	def queue(self): return self[1:]
	
	def __index(self,i):							# Teste si un index est correct, premet d'utiliser l[-1]
		if i>len(self): raise IndexError
		if i<0: return __index[i+len(self)]
		return self[i]

	def __len__(self): return self.__lenght			# Pour utiliser len(l) plutot que longeur(l) et pour faire plus propre
	def __str__(self): return str(self.__table)		# Pour utiliser print l
	
	def __getitem__(self,i):						# Pour pouvoir faire: l[i]
		i=self.__index(i)
		return self.__table[i]
	
	def __setitem__(self,i,x):        				# Pour attrbuer un element List[i]=x
		i=self.__index(i)
		self.__table[i]=x
	
	def __delitem__(self,i):
		i=self.__index(i)
		j,mx=i,len(self)
		while j<mx:
			self[j]=self[j+1]
			j+=1
		self.__lengh-=1
##############################
# Definition des Fonctions 1

def liste(*l,lenght=False):
	"""*[Int] Prend une suite d'entiers en parametres 
	NB, du a la structure des List, les elements sont inversés, ce n'est pas une erreur"""
	if not lenght: lenght=len(l)
	liste=List(lenght)
	for elt in l:
		liste.cons(elt)
	return liste

def longeur(l):
	"[List]=>[int]"
	return len(l)			# Voir plus haut

def element(l,i):
	"[List] => [Node] Retourne la node numéro <i>"
	return l[i]				# Voir plus haut

def supprimer(l,i):
	del(l[i])
		
def ajouter(l,x,i):
	if i>len(l)+1 or i<0: raise IndexError		# Pas de délires Fancy cette fois, l'index doit etre compris entre 1 en len
	j=len(l)
	while j>i: l[j],j=l[j-1],j-1
	l[i]=x
		
def appliquer(l,f):
	i,mx=0,len(l)
	while i<mx:	l[i],i=f(l[i]),i+1

def filtrer(l,filt):
	i,mx=0,len(l)
	while i<mx:
		if not filt(l[i]): del(l[i])		# Peut aussi s'ecrire supprimer(l,i)
		i+=1

def compter(l,x):
	compt=0
	for i in l:
		if i==x: compt+=1
	return compt

def reduire(l,f,x):
	for i in l: x=f(x,i)				# Quelquefois les choses sont très simple
	return x

##############################
# Definition des Fonctions 2

def ajoute(l,x): return appliquer(l,lambda y: x+y) # Explication: L'exo est bidon donc 1 ligne suffit

def paire(l): return filtrer(l,lambda x: x%2==0) # Idem: J'utilise la fonction filter qui est plus haut

def avant_dernier(l):


def incremente(l,i=0):


def repete(l,n,i):


def pgcd(m,n):
	while m%n: n,m=m%n,n
	return n

ppcm = lambda m,n: (n*m)/pgcd(m,n)

def multiple(l):


def applique(l,l2,f):


def alternance(l):


def repete(l,i,n):


##############################
# Corps du programme

l=liste(1,2,3,7,42)
print l

def f(x): return 3*x
def fil(x): return x>5
def somme(a,b): return a+b

#print longeur(l)
#appliquer(l,f)
#ajouter(l,1212,2)
#print compter(l,2)
#
#print reduire(l,somme,0)
#filtrer(l,fil)
#
#paire(l)
#print avant_dernier(l)
#
#incremente(l)
#print multiple(l)
#l2=liste(3,1,2,1,3)
#applique(l,l2,f)
#print l2
#print alternance(l2)
#repete(l,2,5)

print l