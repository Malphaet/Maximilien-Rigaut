# -*- coding:utf8 -*-

##############################
# Copyleft Maximilien Rigaut
# Devoir a la maison
##############################


##############################
# Importation des Modules
import random
from devoir import *

###############################
# ----      Partie 1     ---- #
###############################

class Liste(object):
    def __init__(self,first=None):
        self.first=first
    
    def add(self,node):
        self.first,node.next=node,self.first
    
    def delete(self,value):
        while self.first!=None:
            if self.first.value==value: self.first=self.first.next
            else: break
        node,node0=self.first.next,self.first
        while node!=None:
            if node.value==value: node0.next=node.next
            node,node0=node.next,node
    
    def __contains__(self,x):
        node=self.first
        while node!=None:
            if node.value==x: return True
            node=node.next
        return False

    def __str__(self):
        ret,node='',self.first
        while node!=None:
            ret+=', '+str(node.value)
            node=node.next
        return '['+ret[2:]+']'
 
class Node(object):
    def __init__(self,value=None,next=None):
        self.value=value
        self.next=next
    
        
def ajouter(x,l): return l.add(Node(x))
def supprimer(x,l): return l.delete(x)
def appartient(x,l): return x in l


def ajouter2(x,l):
    node,node0,nodeN=l.first,l.first,Node(value=x)
    if l.first==None: 
        l.first=nodeN
        return nodeN
    while True:
        if node==None or node.value>x: 
            node0.next,nodeN.next=nodeN,node
            return nodeN
        node,node0=node.next,node
    
def appartient2(x,l):
    node=l.first
    while node!=None:
        if node.value>x: return False
        elif node.value==x: return True
        node=node.next
    return False

###############################
# ----    Questions      ---- #
###############################
# 2. Complexité:
# - ajouter: O(1)
# - supprimer: O(n)
# - appartient: O(n)
###############################
# ----       Tests       ---- #
###############################
# 1. ajouter supprimer appartient
print "+---------------+"
print "| Liste chainée |"
print "+---------------+"
l=Liste()
for i in xrange(10): ajouter(i,l)
print "+ Ajouter"
print "|   ",l

supprimer(9,l)
print "|\n+ Supprimer"
print "|   ",l

print "|\n+ Appartient"
print "|   ",appartient(9,l),appartient(2,l)

# 2. ajouter2 appartient2
print "+ - - - - - - - - - - - +"
print "| Liste chainée ordonée |"
print "+ - - - - - - - - - - - +"
l2=Liste()
for i in range(10):
    if i%2!=0: ajouter2(i,l2)
print "+Ajouter"
print "|   ",l2

print "|\n+Appartient"
print "|   ",appartient2(12,l2),appartient2(2,l2),appartient2(5,l2)

###############################
# ----      Partie 2     ---- #
###############################

def appartient(x,l):
    val=l.haut
    while True:
        if val.suivant==None or x<val.suivant.valeur:
            val=val.inferieur
            if val==None: return False
        else:
            val=val.suivant
            if x==val.valeur: return True

def findPrec(x,l):
    val,val0=l.haut,l.haut
    while True:
        if val.suivant==None or x<val.suivant.valeur:
            val=val.inferieur
            if val==None: return None
        else:
            val,val0=val.suivant,val
            if x==val.valeur: return val0

def supprimer(x,l):
    while l.haut!= None and l.haut.suivant!=None and l.haut.suivant.valeur==x:
        l.haut=l.haut.inferieur         # L'étape n'est pas necessaire mais est plus propre
        l.haut.supperieur==None         # Ainsi la liste ne possede jamais plus de niveaux que necessaire
    val0=findPrec(x,l)
    while val0!=None:
        if val0.suivant.valeur==x:
            val0.suivant=val0.suivant.suivant
            val0=val0.inferieur
        else:
            val0=val0.suivant 

###############################
# ----    Questions      ---- #
###############################
# 4. En moyenne une SkipList possede log2(n) niveaux
#
# 5. Complexité: inserer
#   O(n)        <-  [2n(1-0.5log2(n))]
#
# 7. Complexité: appartient
#   O(log2(n))  <-  [1 ou 2 deplacement par niveau]
#

###############################
# ----       Tests       ---- #
###############################
# 1. ajouter afficher
print "+----------+"
print "| Skiplist |"
print "+----------+"
l = skiplist()
for i in range(40): inserer(i, l)
affiche(l)

# 6. appartient
print "|\n+ Appartient"
print "|   ",appartient(12,l)

# 8. supprimer
print "|\n+ Supprimer"
supprimer(30,l)
affiche(l)