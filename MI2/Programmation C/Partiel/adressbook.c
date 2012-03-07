/*
 * adressbook.c
 * This file is part of Tintable
 *
 * Copyright (C) 2012 - Maximilien Rigaut
 *
 * Tintable is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Tintable is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */



/* ========= Includes =========*/

#include <stdio.h>
#include <stdlib.h>
#include "tintable_lib.h"

/* ========= Defines ==========*/

/* =========== Main ===========*/

int main(void){
	int table[]={4,1,2,3,4,5,6,7,8,9};
	char*u=tintable(table,6);
	print_tintable(u,3);
	/*printf("%s\n",tintable(table,10));*/
	return 0;
}

/* ========= Functions ========*/

