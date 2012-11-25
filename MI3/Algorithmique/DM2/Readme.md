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

## Modus Operandi
### Twisting
1. Detect hiphenable characters (being: "a:âà" e:"éèë" i:"ïî" c:"ç" oe:"")
1. Twist the words
1. Detect posible options

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
+ Add utf8 support to word recognition
+ Better @ref build_3tupledict, maybe a subfunction
+ Threadify it a little
