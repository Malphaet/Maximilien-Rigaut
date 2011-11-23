http://rosettacode.org/wiki/Miller-Rabin_primality_test

def essai_composites(a):
    if ExpoRapide(a, d, n) == 1:
        return False
    for i in range(s):
        if ExpoRapide(a, 2**i * d, n) == n-1:
            return False
    return True # n is definitely composite
def essai_composites(a):
    if ExpoRapide(a, d, n) == 1:
        return False
    for i in range(s):
        if ExpoRapide(a, 2**i * d, n) == n-1:
            return False
    return True

def is_probable_prime(n):
    test=[2,3,5,7,13,17,31,71]
    if n<4: return True
    if n%2==0: return False
    d,s=n-1,0
    while d%2==0: s,d=s+1,d/2
    if log(d)<100: test=test[:4]
    def essai_composites(a):
        x=ExpoRapide(a,d,n)
        if x==1: return False
        for i in range(s):
            x=x*x%n
            if x==n-1: return False 
        return True # Composé
    for a in test: 
        if essai_composites(a): return False
    return True