# -*- Coding: UTF-8 -*-

##############################
# Copyleft Maximilien Rigaut
# TP 9 - Arbres Binaires
##############################


##############################
# Definition des Classes

def Node(object):
    def __init__(self,x,left=None,right=None):
        self.value=x
        self.left=left
        self.right=right

def Tree(object):
    def __init__(self,no=None):
        self.root=no
        
    def vide(self):
        return self.root==None
    def gauche(self):
        if not self.vide(): return self.root.left
    def droite(self):
        if not self.vide(): return self.root.right
    def racine(self): 
        if not self.vide(): return self.root.value
        
    def __len__(self):
        if self.vide(): return 0
        return 1+max(len(self.droite()),len(self.gauche()))
    def nb_nodes(self):
        if self.vide(): return 0
        return self.droite().nb_nodes+self.gauche().nb_nodes
    def sum_values(self):
        if self.vide(): return 0
        return self.racine()+self.gauche().nb_nodes+self.droite().nb_nodes
    def incremente(self):
        if not self.vide():
            self.root.x+=1
            self.gauche().incremente()
            self.droite().incremente()
    def sorted(self):
        if self.vide(): return True
        if self.droite().racine() < self.racine(): return False
        
            
    def print_all(self):
        if self.vide():
            print None
        else:
            print self.racine()
            self.gauche.print_all()
            self.droite.print_all()

##############################
# Definition des Fonctions

def cons(x,t1,t2): Tree(n=Node(x,left=t1,right=t2))
def profondeur(x): return len(x)

##############################
# Corps du programme
Tree(no=12)
#T1=cons(12,Tree(),Tree())
print T1