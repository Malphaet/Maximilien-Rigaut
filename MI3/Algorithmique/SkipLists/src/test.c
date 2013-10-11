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



int main(int argc,char **argv){
	SkipList*l=sk_create(0.5);
	char*txt;
	(void)argc;(void)argv;
	sk_add_int(l,12);
	sk_add_int(l,2);
	sk_add_int(l,1);
	sk_add_int(l,16);
	sk_add_int(l,2000);
	sk_add_int(l,5);
	printf("%p : %s\n",(void*)l,txt=sk_tostring_int(l));
	sk_delete(l); free(txt);
	return 0;
}
