# Fonctions examples
def implies(a,b):
    if a==True: return bool(b)
    return True

def equiv(a,b): return a==b

def unhappy(a,b): return False

logic={'ou':'or','et':'and','modulo':'%','vrai':'True','faux':'False'} #Absolument non necessaire si l'on ne souhaite ecrire en français
functions={'<=>': equiv,'=>':implies,'=/':unhappy} #Nb, le dictionnaire contient des fonctions pas des chaines

def clever_eval(text):
    "Evalue l'expression entrée. Retourne une valeur de verité."
    status=True
    if ')' in text: # Parenthésage prime sur les fonctions !
        i=text.index(')')
        j=text[:i].rindex('(')
        return clever_eval(text[j+1:i])
    for fun  in functions:
        if fun in text:
            text=text.split(fun,1)
            return functions[fun](clever_eval(text[0]),clever_eval(text[1])) # By the almighty recursion !
    if status:
        for fun in logic:
            text=text.replace(fun,logic[fun])
        return eval(text) # Puissance de python: Faire le job pour moi

def replace(expression,valeurs):
    pass
def table_expression(expression,variables,typ=int):
    """<expression>,<variables> - Table de verité de l'expression <expression> en fonction des variables <variables>"""
    bin_max,var_max,binary=2**(len(variables)),len(variables),0
    expression=' '+expression+' '
    separator='+'+'-'*(9+len(expression)+var_max)+'+'
    print separator
    print '| Table of truth'+' '*(-7+len(expression)+var_max)+' |'
    print '|'+' '*(7+var_max)+'  %s'%expression+'|'
    print separator
    while binary<bin_max:
        i,temp_expression=0,expression
        while i<var_max:
            temp_expression=temp_expression.replace(' %s '%variables[i],' %s '%int(bin(binary+bin_max)[i+3]))
            i+=1
        try:
            print '|',bin(bin_max+binary)[3:],'|',temp_expression,'|',int(clever_eval(temp_expression)),'|'
        except:
            print "Verifiez que toutes vos variables sont declarées comme variables et séparées par des espaces"
            return False
        binary+=1
    print separator
print clever_eval.__doc__
print clever_eval(" ( 1 => 1) => False")

table_expression(" a or ( b => c )",['a','b','c'])
table_expression(" a or b => 0",['a','b'])