/*
 * crypto.c
 * 
 * Copyright 2012 Maximilien Rigaut <max[dot]rigaut[at]orange.fr>
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

#include "crypto.h"
#include <crypt.h>
#include <unistd.h>

unsigned char SALT_RANGE[]="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789./";
 
/* Crypt password */
char*lcrypt(char*passwd){
	char*ret,salt[3]="**\0";
	unsigned int hash;
	
	/* Pass 1 */
	hash=jhash(passwd,8);
	salt[0]=SALT_RANGE[hash&0x00003F];
	salt[1]=SALT_RANGE[hash>>7];
	
	ret=crypt(passwd,salt);
	
	return ret;
}

/** Hash the given word according to the java string hash function
 * @param word The word to hash
 * @param hash_size Size of the hash (in bits)
 
 * @return The unsigned int of the hash
 */
unsigned int jhash(const char*word,int hash_size){
	unsigned int i,hash=0,l=strlen(word),finalhash=-1,mask=-1;
	for (i=0;i<l;i++) hash=((hash<<HASH_POWR)-hash+(unsigned int)word[i]);
	
	/* Strip the checksum (Here some XORing for entropy purposes) */
	mask=mask>>(sizeof(int)*8-hash_size);
	do{
		finalhash=(finalhash^hash)&mask;
		hash=hash<<hash_size;
	} while(hash);
	
	return finalhash;
}
