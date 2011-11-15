# -*- coding:utf8 -*-

##############################
# Copyleft Maximilien Rigaut
# Fonctions recusives sur listes chainées
##############################


##############################
# Definition des Classes
# Nb: Les classes contiennent ici des methodes
#     càd des fonctions propres ainsi qu'une initialisation.
#     Bonne chance et bonne lecture :)

class Node():
	def __init__(self,x,next=None):
		self.value=x
		self.next=next
	def append(self,node):
		self.next=node
	def __str__(self):
		return str(self.value)

class List():
	def __init__(self,first=None):
		self.first=first
	def cons(self,node):
		"Append a node to the List"
		self.first,node.next=node,self.first
	def vide(self):
		return (self.first==None)
	def tete(self):
		#print self.first.value
		return self.first
	def queue(self):
		return List(self.first.next)
	def len(self):
		return longeur(self)
	def __str__(self):
		if self.first==None: return ''
		st,nx=str(self.first.value),self.first.next
		while nx!=None:
			st+=','+str(nx.value)
			nx=nx.next
		return st
		
##############################
# Definition des Fonctions 1

def liste(*l):
	"""*[Int] Prend une suite d'entiers en parametres 
	NB, du a la structure des List, les elements sont inversés, ce n'est pas une erreur"""
	liste=List()
	for elt in l:
		liste.cons(Node(elt))
	return liste

def longeur(l):
	"[List]=>[int]"
	if l.vide(): return 0
	return 1+longeur(l.queue())

def element(l,i):
	"[List] => [Node] Retourne la node numéro <i>"
	if i<1: return l.tete()
	return element(l.queue(),i-1)

def supprimer(l,i):
	if i==1: l.first.next=l.first.next.next
	if i<1: l.first=l.first.next
	if i>1: supprimer(l.queue(),i-1)

#def ajouter(l,x,i):                             # Works better and don't sucks ass
#	elt,x=element(l,i-1),Node(x)
#	if i<1: l.first,x.next=x,elt
#	if i>0: elt.next,x.next=x,elt.next.next

def ajouter(l,x,i):
	if i==1: 
		x=Node(x,l.first.next)
		l.first.next=x
	if i<1: 
		x=Node(x)
		l.first,x.next=x,elt
	if i>1: ajouter(l.queue(),x,i-1)
		
def appliquer(l,f):
	if l.vide(): return None
	l.first.value=f(l.first.value)
	appliquer(l.queue(),f)

def filtrer(l,filt):
	if l.len()>1 and not filt(l.first.next.value):
		filtrer(l.queue(),filt)
		l.first.next=l.first.next.next
	if l.vide(): return True
	filtrer(l.queue(),filt)
	if not filt(l.first.value):	l.first=l.first.next # Due to stupid structure of our Lists

def compter(l,x):
	if l.vide(): return 0
	if l.first.value==x: return 1+compter(l.queue(),x)
	return compter(l.queue(),x)

def reduire(l,f,x):
	if l.vide(): return x
	return reduire(l.queue(),f,f(l.first.value,x))

##############################
# Definition des Fonctions 2

def ajoute(l,x): return appliquer(l,lambda y: x+y) # Explication: L'exo est bidon donc 1 ligne suffit

def paire(l): return filtrer(l,lambda x: x%2==0) # Idem: J'utilise la fonction filter qui est plus haut

def avant_dernier(l):
	if longeur(l)<1: return l.first # avant_dernier(List())=None Par definition
	if l.first.next.next==None: return l.first
	return avant_dernier(l.queue())

def incremente(l,i=0):
	if l.first==None: return None
	l.first.value+=i
	incremente(l.queue(),i=i+1)

def repete(l,n,i):
	if l.first.next==None and i:
		return True

def pgcd(m,n):
	while m%n: n,m=m%n,n
	return n

ppcm = lambda m,n: (n*m)/pgcd(m,n)

def multiple(l):
	if l.vide(): return 0 # Pas de ppcm sur une liste vide
	if l.first.next==None: return l.first.value
	return ppcm(l.first.value,multiple(l.queue()))

def applique(l,l2,f):
	if l.vide() or l2.vide(): return True
	if l2.first.value!=0:
		l2.first.value-=1
		l.first.value=f(l.first.value)
		applique(l,l2,f)
	applique(l.queue(),l2.queue(),f)

def alternance(l):
	if l.len()<3: return True # Plus facile que cela n'en a l'air
	if (l.first.value > l.first.next.value) == (l.first.next.value < l.first.next.next.value): return alternance(l.queue())
	return False

def repete(l,i,n):
	if l.vide() or n==0: return True
	if i>0: return repete(l.queue(),i-1,n)
	l.first.next=Node(l.first.value,next=l.first.next) # D'ou l'importance d'une bonne méthode d'initialisation de ses objets
	repete(l,i,n-1)

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