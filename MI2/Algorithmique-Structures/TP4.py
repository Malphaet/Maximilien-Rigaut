# -*- coding:utf-8 -*-

##############################
# Copyleft Maximilien Rigaut
# 
##############################



##############################
# Importation des Modules


##############################
# Definition des Classes

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
# Definition des Fonctions

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

#def filtrer(l,filt):
#	if l.vide(): return True
#	if not filtrer(l.queue(),filt):
#		l.first.next=l.first.next.next
#	if not filt(l.first.value):
#		l.first=l.first.next
#		return False

def compter(l,x):
	if l.vide(): return 0
	if l.first.value==x: return 1+compter(l.queue(),x)
	return compter(l.queue(),x)

def reduire(l,f,x):
	if l.vide(): return x
	return reduire(l.queue(),f,f(l.first.value,x))


##############################
# Corps du programme

addresse="metal--addict@hotmail.fr"
l=liste(1,2,3,7,42)

def f(x): return 3*x
def fil(x): return x<42
def somme(a,b): return a+b

#appliquer(l,f)
#ajouter(l,1212,2)
#print compter(l,2)

#print reduire(l,somme,0)
print l