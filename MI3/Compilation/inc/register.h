/*
 * register.h
 * 
 * Copyright 2013 Maximilien Rigaut <max[dot]rigaut[at]orange.fr>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 */

#ifndef __REGISTER_H__
#define __REGISTER_H__

/* ========= Defines  ==========*/
#define SIZE_REGISTER 10


/* ======== Prototype =========*/
void trouve_dernier_appel();
int registre_libre(int ligne);
int registre_associe(int ligne);
//int optimise_registres();

#endif
