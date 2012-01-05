#########################
#          RSA          #
#      system:sage      #
#########################

# --------------------- #
# Fonctions Utilitaires #
# --------------------- #

def ExpoRapide(x,p,n):
    if p==0: return 1
    if p%2==0:
        temp=ExpoRapide(x,p/2,n)%n
        return temp*temp%n
    else:
        temp=ExpoRapide(x,(p-1)/2,n)%n
        return x*temp*temp%n

def div(d,b):
    s = 0
    while d%b==0: s,d=s+1,d/b
    return (s,d)

# ------------ #
# Classes Clef #
# ------------ #

class Clef_pub(object):
    def __init__(self,e,n):
        self.clef=e
        self.modulo=n
        self.__dict__={'clef':self.clef,'modulo':self.modulo}
    def __str__(self):
        return str((self.clef,self.modulo))
    def listall(self):
        for cle in self.__dict__: print cle,self.__dict__[cle]
class Clef_priv(Clef_pub):
    def __init__(self,e,d,n,p,q):
        "*<int> - Clef publique, Clef privée, modulo, p et q"
        Clef_pub.__init__(self,d,n)
        self.clef_p=d%(p-1)
        self.clef_q=d%(q-1)
        self.q_inv=Inverse(q,p)
        self.p,self.q=p,q
        self.__dict__.update({'clef_p':self.clef_p,'clef_q':self.clef_q})

# --------------------- #
# Fonctions Importantes #
# --------------------- #

def MillerRabin(n):
    "(<int>:n) - Renvoie (<bool>:Pseudo-Premier)"
    test=[2,3,5,7,13,17,31,71]
    if n<4: return True
    if n%2==0: return False
    d,s=n-1,0
    while d%2==0: s,d=s+1,d/2
    if log(d)<100: test=test[:4]
    def EssaiCompose(a):
        x=ExpoRapide(a,d,n)
        if x==1: return False
        for i in range(s):
            x=x*x%n
            if x==n-1: return False 
        return True # Composé
    for a in test: 
        if EssaiCompose(a): return False
    return True

def Prim(i):
    "(<int>:nb decimales) - Renvoie un Pseudo Premier de taille i"
    j=4
    while not MillerRabin(j):
        j=0
        for ex in range(i): j+=randint(0,9)*(10**ex)
        while not MillerRabin(j):
            j+=randint(1,10)
            if j.digits()>i: break
    return j

def PremierAvec(a,n):
    "(<int>:nombre,<int>:modulo) - Renvoie un nombre premier avec a modulo n"
    assert(a>2)
    while True:
        i=randint(2,n)
        b,j = a,i
        if b<j: b,j=j,b
        while j>0: b,j=j,b%j
        if b==1: return i

def EuclideEtendu(a, n):
    if n == 0: return (1, 0)
    q = a//n
    r = a - n*q
    s,t = EuclideEtendu(n,r)
    return (t, s - q * t)

def Inverse(a,n):
    "(<int>:nombre,<int>:modulo) - Renvoie l'inverse de a modulo n"
    res=EuclideEtendu(a,n)[0]
    if res<0: return res+n
    return res

def CleInit(i):
    "(<int>:taille) - Renvoie (<Clef_pub>,<Clef_priv>) deux clef de taille superieure a 2i chacune."
    p,q=Prim(i),Prim(i)
    n,mx=p*q,(p-1)*(q-1)
    e=PremierAvec(mx,mx)
    d=Inverse(e,mx)
    c1,c2=Clef_pub(e,n),Clef_priv(e,d,n,p,q)     # Old fashion: ((d,n),(e,n))
    return c1,c2

def Chiffrement(m,c):
    "(<list>:messages a encripter,<Clef_pub>:Clef) - Renvoie le message cripte"
    return [(int(i)*1).powermod(c.clef,c.modulo) for i in m]

def Dechiffrement(msgs,c1,c2):
    "(<list>:messages a décrypter,<Clef_pub>:clef,<Clef_priv>:clef) - Renvoie le message déchiffré"
    table=[]
    for m in msgs:
        m1=m.powermod(c2.clef_p,c2.p)
        m2=m.powermod(c2.clef_q,c2.q)
        ad=m1-m2
        if ad<0:ad+=c2.p
        h = (c2.q_inv * (ad)) % c2.p
        table.append(str(m2+h*c2.q))
    return table

def Encodage(s,size):
    "(<str>:chaine,<int>:taille du modulo) - Retourne le tableau des chaines a coder"
    msg,size='',size-2
    for char in s: msg+=str(100+ord(char))
    return ['1'+msg[i*size : (i+1)*(size)] for i in range(len(msg)/size+1)]

def Decodage(msgs,c):
    "(<list>:messages,<Clef_pub>:Clef) - Decode le message"
    msg,m='',''
    for i in msgs: m+=i[1:]
    for i in range(len(m)//3): msg=msg+chr(int(m[i*3:(i+1)*3])-100)
    return msg

def RSA(s,i):
    c1,c2= CleInit(i)
    size=len(str(c1.modulo))
    print 'Clef 1',c1
    print 'Clef 2',c2
    m=Encodage(s,size)
    m_enc=Chiffrement(m,c1)
    print 'Message Encodé:',m
    print 'Message Encripté:',m_enc
    m_dec=Dechiffrement(m_enc,c1,c2)
    
    print 'Message Decripté:',m_dec
    m=Decodage(m_dec,size)
    print 'Message Decodé:',m
///
}}}

{{{id=31|
def PollardTest(n,B,g):
    a=g.powermod(g,n)
    x=gcd(a-1,n)
    if x!=1 and x!=n: return x
    return False

def Pollard(n,B):
    "(<int>:nombre compose,<int>:seuil) - Renvoie un facteur de B"
    g=2
    while g<B:
        x=PollardTest(n,B,g)
        if x: return x
        g+=1
    return False

def AttaqueRSA(m,c):
    "(<int>:message crypte,<Clef_pub>:clef) - Renvoie le message decrypte"
    p=Pollard(c.modulo,c.clef)
    q=c.modulo/p
    d=inverse_mod(c.clef,(p-1)*(q-1))
    return (d,c.modulo),m.powermod(d,c.modulo)

# -------------------- #
# Programme Principal  #
# -------------------- #

#print Prim(42)
#print PremierAvec(20.factorial(),20.factorial())
#print Inverse(44,7)

#c1,c2,m= CleInit(42),42
#m_enc=Chiffrement(m,c1)
#m_dec=Dechiffrement(m_enc,c1,c2)
#print m,m_enc,m_dec

print """
+--------------------+
| Implementation RSA |
+--------------------+"""
RSA("Mon Nom Est Quelqu'un",5)

print """
+--------------------+
| Attaque de Pollard |
+--------------------+"""
print "Factorisation test sur",139,197,":", Pollard(139*197,13*19),139*197/Pollard(139*197,13*19)

clef_pu,clef_pr= CleInit(4)
message=1337.powermod(clef_pu.clef,clef_pu.modulo)
print "Message Intercepté:",message
print "Clef publique:",clef_pu.modulo,clef_pu.clef

clef,message=AttaqueRSA(message,clef_pu)
print "Clef privée:",clef
print "Message décrypté:",message





#--------------------#
#----- Resultat -----#
#--------------------#

+--------------------+
| Implementation RSA |
+--------------------+
Clef 1 (1046205869, 2521586759)
Clef 2 (1107189029, 2521586759)
Message Encodé: ['117721121', '101321782', '111209132', '116921521', '161321812', '117201208', '121321713', '19217210']
Message Encripté: [876932417, 76725851, 645297924, 1906238654, 1685106018, 2228408869, 1831107983, 1785998853]
Message Decripté: ['117721121', '101321782', '111209132', '116921521', '161321812', '117201208', '121321713', '19217210']
Message Decodé: "Mon Nom Est Quelqu'un"

+--------------------+
| Attaque de Pollard |
+--------------------+
Factorisation test sur 139 197 : 139 197
Message Intercepté: 14958411
Clef publique: 16765223 9939767
Clef privée: (15920903, 16765223)
Message décrypté: 1337