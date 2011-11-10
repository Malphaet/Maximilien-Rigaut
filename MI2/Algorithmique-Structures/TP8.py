# -*- Coding: UTF-8 -*-

##############################
# Copyleft Maximilien Rigaut
# TP7 - Hachage
##############################


##############################
# Definition des Fonctions
# - - - - - - - -
# Exo 1
def ajoute(motf,mota,d):
	if motf not in d.keys(): d[motf]=mota

def print_d(d):
	for i in d.values(): print i

def del_ch(char,d):
	for i in d.keys():
		if char == i[:len(char)]: del(d[i])

# - - - - - - - -
# Exo 2
def char2oct(char):
	i,res=0,0
	for l in char: res,i=res+ord(l)*(256**i),i+1
	return res

h=lambda x: x%255
h_word=lambda w: h(char2oct(w))

# - - - - - - - -
# Exo 3

def anniversaire(n):
	res,i,j,p=1.,365,365-n,1
	if n>355: return float('inf')
	while i>0:
		res=res*i/(j*(365**p))
		i,j,n,p=i-1,max(j-1,1),n-1,max(min(n,1),0)
		if i%30==0: print res,i,j,p
	return 1-res
##############################
# Corps du programme

lang={'erreur':'error','non-autorise':'unauthorised','echec':'failure','corrompu':'corrupted','damnation':'damnatus'}
lang['maux']='woe'
#print_d(lang)
#print '---'
#del_ch("e",lang)
#print_d(lang)

#a,b=char2oct("yyw"),char2oct("zwx") ## Erreur !
#print a,b
#print h(a),h(b)

print anniversaire(23)