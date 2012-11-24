/*
 * utils.c
 * This file is part of Algorithms 2012
 *
 * Copyright (C) 2012 - Maximilien Rigaut
 *
 * Algorithms 2012 is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Algorithms 2012 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Algorithms 2012. If not, see <http://www.gnu.org/licenses/>.
 */

#include "utils.h"

/**@defgroup tools Debug tools 
 * @{
 */
/** Print the given char in binary */
void binary_print(char*val){
	printf("%s\n",atobin(val));
}

/** Convert the char to binary format 
 * @param str The string to convert to binary
 * @return The binary value as a string
 */
char* atobin(char*str){
	char*res=malloc(((strlen(str)*sizeof(char))*8+1)*sizeof(char));
	char*tmp=res;
	do{
		strcpy(tmp,itobin(*str,sizeof(char)*8));
		tmp+=8;
		*tmp++=' ';
	}while (*++str);
	*tmp=0;
	return res;
}

/** Convert the integer to binary format 
 * @param nb The number to convert
 * @param size The number of bits to print sizeof()*8
 * 
 * @return The binary value as a string
 */
char* itobin(int nb,unsigned int size){
	char*res=calloc(size+1,sizeof(char));
	unsigned int i;
	if (!res) ERROR("Malloc");
	for (i=0;i<size;i+=1){
		res[i]=(nb&1)+'0';
		nb>>=1;
	}
	return res;
}
/** @} */
