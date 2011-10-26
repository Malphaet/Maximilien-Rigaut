def factorial(x):
	temp=1
	while x>0:
		temp*=x
		x-=1
	return temp
def approcheDirecte(n):
	"Approche approximative de exp(e,-10)"
	k,temp,fact=0,0,1
	while k<=n:
		j=1
		while k>=j:
			fact*=10./j
			j+=1
		temp+=fact*(-1)**k
		fact=1
		k+=1
	return temp

def approcheIndirecte(n):
	"Approche indirecte de la valeur exp(e,-10)"
	temp=0
	k=0
	while k<=n:
		temp+=(10**k)*1./factorial(k)
		k+=1			
	return 1./temp

def rump(a,b):
	return(333.75*b**6+a**2*(11*a**2*b**2-b**6-121*b**4-2)+5.5*b**8+a*1./2*b)

def suite(n):
	if n<2: return 'NOOOOOOOOOOOOOO !'
	un_m,un=2,-4
	i=2
	while i<n:
		un_p=111-1130./un+3000./(un_m*un)
		un_m,un=un,un_p
		i+=1
	return un

def integrale(n,a,b):
	i=0
	temp=0
	while i<n:
		ai=aii
		aii=(a-b)*i*1./n
		temp+=
#print approcheDirecte(50)
#print approcheIndirecte(50)
#print rump(77617,33096)
#for i in range(40): print suite(i)
print integrale(10)
