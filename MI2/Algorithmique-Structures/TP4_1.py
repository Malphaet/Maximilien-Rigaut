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
		self.__length=taille	# (Taille totale) Cet attribt est privé, il ne devrait pas etre appelé hors de la fonction
		self.__table=[0]*taille	# Idem
		self.__last=0			# (Taille effective)
	
	def __index(self,i):							# Teste si un index est correct, premet d'utiliser l[-1]
		if i>=len(self): raise IndexError
		if i<0: return self.__index(i+len(self))
		return i

	def __len__(self): return self.__last			# Pour utiliser len(l) plutot que longeur(l) et pour faire plus propre
	def __str__(self): return str(self.__table[:self.__last])		# Pour utiliser print l (Affiche les valeurs existantes)
	
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
			self[j]=self.__table[j+1]
			j+=1
		self.__last-=1
	
	def add(self,x,i):
		if not(i==len(self)): i=self.__index(i)
		j=len(self)
		while j>i:
			self.__table[j]=self.__table[j-1]
			j-=1
		self.__table[i]=x
		self.__last+=1
	
##############################
# Definition des Fonctions 1

def liste(length,*l):
	"""[length,*[Int]] Construit un tableau de longeur length, contenant la liste d'element fournie"""
	length=max(len(l),length)	# Pour les utilisateurs ne lisant pas la doc
	liste=List(length)
	i=0
	for elt in l:
		liste.add(elt,i)
		i+=1
	return liste

def longeur(l):
	"[List]=>[int]"
	return len(l)			# Voir plus haut

def element(l,i):
	"[List] => [Node] Retourne la node numéro <i>"
	return l[i]				# Voir plus haut

def supprimer(l,i):
	del(l[i])				# Voir plus haut
		
def ajouter(l,x,i):
	"L'index doit etre compris entre 0 en len(l)"
	l.add(x,i)


##############################
# Fonctions Avancées	

def appliquer(l,f):
	i,mx=0,len(l)
	while i<mx:	l[i],i=f(l[i]),i+1

def filtrer(l,filt):
	i,mx=0,len(l)
	while i<len(l):
		if not filt(l[i]):
			del(l[i])		# Peut aussi s'ecrire supprimer(l,i)
		else:
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
# Fonctions Inutiles

def vide(l):
	return len(l)==0
		
def tete(l):
	return l[0]
		
def queue(l):		# Inexact mais, il n'existe aucune maniere elegante de faire cela
	del(l[0])

##############################
# Definition des Fonctions 2

def ajoute(l,x): return appliquer(l,lambda y: x+y) # Explication: L'exo est bidon donc 1 ligne suffit

def paire(l): return filtrer(l,lambda x: x%2==0) # Idem: J'utilise la fonction filter qui est plus haut

def avant_dernier(l): return l[-2]

def incremente(l,i=0):
	for elt in l: l[i],i=elt+i,i+1

def repete(l,i,n):
	while n>0:
		ajouter(l,l[i],i)
		n-=1

def pgcd(m,n):
	while m%n: n,m=m%n,n
	return n

ppcm = lambda m,n: (n*m)/pgcd(m,n)

def multiple(l):
	if len(l)==0: return 0
	temp=l[1]
	for i in l:	temp=ppcm(temp,i)
	return temp

def applique(l,l2,f):
	i,j,mx=0,0,len(l)
	while i<mx:
		while j<l2[i]: l[i],j=f(l[i]),j+1
		i,j=i+1,0

def alternance(l):
	i,mx=0,len(l)
	while i<mx-2:
		if (l[i]<l[i+1]) != (l[i+1]>l[i+2]): return False
		i+=1
	return True

##############################
# Corps du programme

TAILLE=100
l=liste(TAILLE,1,2,3,7,42)
print l,len(l)

def f(x): return 3*x
def fil(x): return x>5
def somme(a,b): return a+b

print "--- Fonction de base ---"
print longeur(l)
print element(l,4),l[4]
supprimer(l,4)
print l,len(l)
ajouter(l,42,4)
print l

print "--- Fonctions des listes iteratives ---"
print vide(l),tete(l)#,queue(l)

print "--- Fonctions avancées ---"
appliquer(l,f)
print compter(l,3)
print reduire(l,somme,0)
print l
filtrer(l,fil)
print l

print "--- Fonctions avancées 2 ---"
paire(l)
l=liste(TAILLE,1,2,3,7,42)
print l
print avant_dernier(l)
incremente(l)
print multiple(l)

l2=liste(TAILLE,3,1,2,1,3)
print l2
applique(l,l2,f)
print alternance(l2)
repete(l2,2,2)
print l2

print l