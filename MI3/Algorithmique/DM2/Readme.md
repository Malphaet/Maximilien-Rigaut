Orthographic Corrector  {#mainpage}
====================

## Installation

> + `make init`
> + `make`
> + `make doc`
> + `./bin/corrector ressources/dico.txt ressources/fautes2012.txt`

## Introduction

## Modules
Here is a quick description of the implemented modules, covering their main functionnalities.
### Levenshtein distance
+ Calculate the difference between two strings

### Hash codes
+ Hashing a string
+ Linking each tri-gram to a list
+ Creating a trigram-dictionnary

### Orthographic Corrector

## Performances of different algorithms

### Hashing
Theese are experimental measures, hence not being in any case a valid mathematical proof.

The two compeiting implementation are a modulus (the base java hash function), and a XORing function (@ref jhash_char). 

The idea beneath the XORing function is the following:
+ If I have to sum up my function in X bits of entropy, instead of applying a modulus (even in a fast bitwise fashion),
it would be way faster to "split" my checksum in sizeof(int)*8/X block of bits and XOR them altogether

### Scattering
+ The XORing give a ±70% scattering variation.
+ The modulus gives a ±150% scattering variation.
The goal being a 0% scattering variation (that is to say, a perfectly uniform hash function).
### Speed
The XORing runs 17% faster in average than the modulus function.
### Collisions
Hashing a word dictionnary the XOR function produce +2% to -120% less collisions than modulus.
 
## Modus Operandi
### Twisting
1. Detect hiphenable characters (being: "a:âà" e:"éèë" i:"ïî" c:"ç" oe:"")
2. Twist the words
3. Detect posible options

### Hash Tables
+ Create a hash table
+ Do hash comparaison

### Jacquard Distance
+ Calculate the Jacquard Distance
+ Solve

## Usage

## Todo
+ @ref todo
+ Free a lot more ressources
+ Update and complete this page
  + Add data as examples
+ Add utf8 support to word recognition
+ Better @ref build_3tupledict, maybe a subfunction
+ Threadify it a little
+ Aim at the 0 leak !

