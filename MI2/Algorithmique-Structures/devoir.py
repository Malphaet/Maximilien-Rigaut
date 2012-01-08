# -*- coding:utf8 -*-

##############################
# Copyleft Maximilien Rigaut
# Devoir a la maison
##############################


##############################
# Importation des Modules
import random

##############################
# Definition des Classes

class SkipList:
	pass
class Noeud:
	pass
class Debut:
	pass

def noeud(x):
	n = Noeud()
	n.valeur = x
	n.suivant = None   # le champ suivant permet d'avancer dans la liste
	n.inferieur = None # le champ inferieur permet de descendre d'un niveau
	return n

def debut():
	# les elements de type Debut sont des noeuds n'ayant pas de valeur, placès
	# en tete des listes. Il faut pouvoir monter et descendre d'un niveau a
	# partir d'un Debut.
	d = Debut()
	d.superieur = None # pour monter d'un niveau
	d.inferieur = None # pour descendre
	d.suivant = None   # pointe vers le premier vrai element de la liste
	return d

def skiplist():
	l = SkipList()
	l.haut = None   # le Debut de la liste de plus haut niveau
	l.bas = None    # le Debut de la liste de plus bas niveau (contenant tous les elements)
	return l

def flip():
	"""Fonction permettant de tirer a pile ou face.
	Elle renvoie True ou False avec probabilite 1/2"""
	return random.choice([True, False])

def inserer(x, l):
	"""Cette fonction insere un element x dans une skip-list l"""
	premier = l.bas   # On commence par inserer x dans la liste de plus bas niveau
	inferieur = None  # Le noeud qui sera en dessous du noeud qu'on va ajouter
	test = True       # Ce test indique si on doit ajouter x dans un niveau de plus
	                  # au debut le test est vrai car tout element doit etre ajoute
	                  # dans le niveau le plus bas
	while test:
		# on ajoute x dans la liste dont le Debut est premier
		if premier == None: # si ce niveau n'existe pas
			premier = debut()
			premier.inferieur = l.haut
			if l.haut != None:
				l.haut.superieur = premier
			l.haut = premier
			if l.bas == None: # si il n'y avait aucun niveau dans la liste l (elle etait vide)
				l.bas = premier
		n = premier # on part du premier noeud
		while n.suivant != None and x >= n.suivant.valeur: # on avance dans la liste jusqu'au
			n = n.suivant                        # premier element qui est plus grand que x
		nx = noeud(x)              # on ajoute un nouveau noeud contenant x
		nx.suivant = n.suivant     # et on le relie aux autres noeuds de la liste
		n.suivant = nx
		nx.inferieur = inferieur   # inferieur est le noeud contenant x qu'on a ajoute au
		                           # niveau inferieur d
		inferieur = nx             # on memorise que nx est le dernier noeud ajoute
		premier = premier.superieur  # on passe a la liste de niveau superieur
		test = flip()                # on choisit si on insere x dans le prochain niveau

def affiche(l):
	"""Fonction d'affichage d'une skip-list"""
	hauteurs = {}
	premier = l.haut
	while premier != None:
		n = premier.suivant
		while n != None:
			ni = n
			h = 1
			while ni.inferieur != None:
				h += 1
				ni = ni.inferieur
			if not ni in hauteurs:
				hauteurs[ni] = h
			n = n.suivant
		premier = premier.inferieur
	
	premier = l.bas
	g = []
	hmax = 1
	if premier != None:
		n = premier.suivant
		while n != None:
			g.append((n.valeur, hauteurs[n]))
			if hauteurs[n] > hmax:
				hmax = hauteurs[n]
			n = n.suivant
	for h in range(hmax, 0, -1):
		print '[]',
		for (v, hv) in g:
			if hv >= h:
				print repr(v).rjust(2),
			else:
				print "  ",
		print

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

class Node(object):
    def __init__(self,value=None,next=None):
        self.value=value
        self.next=next
    
        
def ajouter(x,l): return l.add(Node(x))
def supprimer(x,l): return l.delete(x)
def appartient(x,l): return x in l
# 2. Complexité:
# - ajouter: O(2)
# - supprimer: O(2n)
# - appartient: O(2n)

def ajouter(x,l):
    node,node0,nodeN=l.first,l.first,Node(value=x)
    while node!=None:
        if node.value>value: node0.next,nodeN.next=nodeN,node
        node,node0=node.next,node
    
def appartient2(x,l):
    node=l.first
    while node!=None:
        if node.value>x: return False
        elif node.value==x: return True
        node=node.next
    return False

###############################
# ----      Partie 2     ---- #
###############################

def appartient(x,l):
    val=l.haut
    test=True
    while test:
        if val.suivant==None or x<val.suivant.valeur:
            val=val.inferieur
            if val==None: return False
        else:
            val=val.suivant
            if x==val.valeur: return True

def supprimer(x,l):
    pass

###############################
# ----    Questions      ---- #
###############################
# 4. En moyenne une SkipList possede log2(n) niveaux
#
# 5. Complexité
#    
#   
# 7. Complexité
#   

l = skiplist()
for i in range(40): inserer(i, l)
affiche(l)
print appartient(99,l)
    