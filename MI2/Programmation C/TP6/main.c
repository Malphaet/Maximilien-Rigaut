/*
 * main.c
 * This file is part of Genelib
 *
 * Copyright (C) 2012 - Maximilien Rigaut
 *
 * Genelib is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Genelib is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

/* ========= Includes =========*/

#include <stdio.h>
#include <stdlib.h>
#include "gene_lib.h"
#include "utils.h"


/* ========= Defines ==========*/

/* =========== Main ===========*/

int main(void){
    PERSONNE deValois = cree_personne("de Valois","Marguerite",1553,1615);
    PERSONNE henriIV = cree_personne("IV","Henri",1553,1610);
    PERSONNE deMedicis = cree_personne("de Medicis","Marie",1573,1642);

    PERSONNE louisXIII = cree_personne("XIII","Louis",1601,1643);
    PERSONNE anneDAutriche = cree_personne("d'Autriche","Anne",1601,1666);
    PERSONNE louisXIV = cree_personne("XIV","Louis",1643,1715);
    PERSONNE philippeDOrleans = cree_personne("d'Orleans","Philippe",1640,1701);
    POINTEUR tout_le_monde = liste_vide();
    
    OUTNF("\nUne personne:\n");
    affiche_personne_abbrev(deValois);
    OUTNF("\n");
    
    ajoute_personne(deValois,tout_le_monde);
    ajoute_personne(henriIV,tout_le_monde);
    ajoute_personne(deMedicis,tout_le_monde);
    ajoute_personne(louisXIII,tout_le_monde);
    ajoute_personne(anneDAutriche,tout_le_monde);
    ajoute_personne(louisXIV,tout_le_monde);
    ajoute_personne(philippeDOrleans,tout_le_monde);
    
    
    OUTNF("\nTout le monde:\n");
    affiche_liste_abbrev(tout_le_monde);
    OUTNF("\n");
    
    ajoute_pere_enfant(henriIV,louisXIII);
    ajoute_pere_enfant(louisXIII,philippeDOrleans);
    ajoute_pere_enfant(louisXIII,louisXIV);
    
    ajoute_mere_enfant(deMedicis,louisXIII);
    ajoute_mere_enfant(anneDAutriche,philippeDOrleans);
    ajoute_mere_enfant(anneDAutriche,louisXIV);
    
    ajoute_conjoint(henriIV,deValois);
    divorce(deValois);
    ajoute_conjoint(henriIV,deMedicis);
    ajoute_conjoint(louisXIII,anneDAutriche);
    
    OUTNF("\nQuelques personnes:\n");
    affiche_personne(deValois);
    OUTNF("\n");
    affiche_personne(henriIV);
    OUTNF("\n");
    affiche_personne(anneDAutriche);
    OUTNF("\n");
    affiche_personne(louisXIII);
    OUTNF("\n");
    
    return 0;
}

/* ========= Functions ========*/



