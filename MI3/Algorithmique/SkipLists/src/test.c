/*
 * test.c
 * This file is part of Algorithms 2013
 *
 * Copyright (C) 2013 - Maximilien Rigaut
 *
 * Algorithms 2013 is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Algorithms 2013 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Algorithms 2013. If not, see <http://www.gnu.org/licenses/>.
 */

#include "utils.h"
#include "skiplib.h"
#include "test.h"
#include "stdlib.h"

int compint(t_key a,t_key b){
	return *((int*)a)==*((int*)b);
}

int compstr(t_key a,t_key b){
	return strcmp((char*)a,(char*)b)==0;
}

int main(int argc,char **argv){
	int *i=malloc(sizeof(int));
	*i=1;
	printf("Hello world %d\n",sk_contains(NULL,i,compint));
	return 0;
}
