/*
 * debitub.c
 * This file is part of TP2
 *
 * Copyright (C) 2012 - Maximilien Rigaut
 *
 * TP2 is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * TP2 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with TP2. If not, see <http://www.gnu.org/licenses/>.
 */


/* ========= Includes =========*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>

/* ========= Defines ==========*/

/* =========== Main ===========*/

int main(int argv,char ** kwargs){
	int p;
	int fd[2];
	
	int buffersize;
	char *buffer;
	int tmp=0;
	int timer=0;
	srand((unsigned int) time(NULL));

	if (argv<2) fprintf(stderr,"buffersize: Incorrect arguments given.\n");
	buffersize=atoi(kwargs[1]);
	buffer=malloc(sizeof(char)*(buffersize+2));
	if (buffer==NULL) perror("buffer: Malloc error");
	while (tmp<buffersize+2) *(buffer+tmp++)='a' + (char) rand()%42;
	
	if (pipe(fd)<0) perror("piping: Generation error");
	if ((p=fork())<0) perror ("fork: Generation error");
	if (p==0){
		close(fd[1]);
		printf("%s\n",buffer);
/*		printf("Each dot represents %d chars (%dkb).\n",1024*buffersize,buffersize*(int)sizeof(char));*/
		while (read(fd[0],buffer,buffersize)>=0) 
		if (++timer>1024) {
			timer=0;
/*			printf("Moo");*/
			printf("%i",rand()%10);
		}
		exit(EXIT_SUCCESS);
	}
	close(fd[0]);
	while(write(fd[1],buffer,buffersize)>=0);
	return 0;
}

/* ========= Functions ========*/

