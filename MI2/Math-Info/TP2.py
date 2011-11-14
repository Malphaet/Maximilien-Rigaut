# -*- Coding: UTF-8 -*-

##############################
# Copyleft Maximilien Rigaut
# TP2 Ensembles applications Denombrement
##############################



##############################
# Importation des Modules

from math import *
import os


##############################
# Definition des Classes

class polynome(object):
	"Polynome p(x)=x[0]*x**0+x[1]*x**1..."
	def __init__(self,*x):
		self.coefs=x
		self.degre=len(x)
	def value(self,x):
		i,temp=0,0
		while i<self.degre:
			temp+=self.coefs[i]*x**i
			i+=1
		return temp

class ensemble(object):
	"Ensemble de definition"
	def __init__(self,a,b):
		if type(a)!=tuple and a!=float('Inf'):
			a=(a,inclus)
		if type(b)!=tuple and b!=inf:
			b=(b,inclus)
		self.a=a
		self.b=b
		self.inc=1
	#def range(self,a=self.a,b=self.b,inc=self.inc):
	#	return range(a,b,inc)

class fileHandler(object):
	"Filehandler"
	def __init__(self,file,content=''):
		self.file_name=file
		if not os.path.isfile(file) or content!='':
			try:
				self.create(content)
			except:
				raise IOError(file)
	def create(self,content=''):
		self.file_handler=open(self.file_name,'w')
		self.file_handler.write(content)
		self.file_handler.close()
	def set_text(self,content):
		self.create(content)		
	def append(self,content):
		self.file_handler=open(self.file_name,'a')
		self.file_handler.write(content)
		self.file_handler.close()
	def append_line(self,content):
		self.append('\n'+content)
	def delete(self):
		os.remove(self.file_name)
	def read(self):
		self.file_handler=open(self.file_name,'r')
		temp=''
		for line in self.file_handler.readlines():
			temp+=line
		self.file_handler.close()
		return temp
	def read_table(self):
		self.file_handler=open(self.file_name,'r')
		temp=self.file_handler.readline()
		self.file_handler.close()
		return temp
class setFiles(object):
	"Etudie des ensembles par filehandling"
	def __init__(self,*files):
		self.set_file=files
		self.cardinal=len(files)
		self.debug=False
	def read(self,sets):
		"List:[Sets to read] => List[List:[Sets]]"
		if type(sets)==int: sets=[sets]
		table=[]
		for i in sets:
			table.append(eval(self.set_file[i].read()))
		return table
	def union(self,sets=0):
		if sets==0: sets=range(self.cardinal)
		table=self.read(sets)
		self.union=[]
		for set in table:
			for elt in set:
				if elt not in self.union:
					self.union.append(elt)
		return self.union
	def inter(self,sets=0):
		if sets==0: sets=range(self.cardinal)
		table=self.read(sets)
		self.inter=[]
		i,mx=0,len(table)
		while i<mx-1:
			for a in table[i]:
				if a in table[i+1]:
					self.inter.append(a)
			i+=1
		return self.inter
##############################
# Definition des Fonctions

def test_disque(z):
	x,y=z
	if (x-4)**2+(y+2)**2==49: return 1
	return 0
##############################
# Corps du programme
#inf=float('inf')
#inclus=1
#exclus=0

#f1=polynome(7,1)
#print f1.value(4)

#file1=fileHandler('next.txt','MOOOOOO')
#file1.append_line('Moooooo')
#print file1.read()
a=fileHandler('e1.in','[0,1,2,3]')
b=fileHandler('e2.in','[0,11,34,42]')
A=setFiles(a,b)
print A.read(0)
print A.union()
print A.inter()
