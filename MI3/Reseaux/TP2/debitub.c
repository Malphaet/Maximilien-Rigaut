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
#include <bor-util.h>

/* ========= Defines ==========*/
void handler(int signal);
unsigned long int readed=0;
#define SFSG printf("%d: So far so good\n",p)
/* =========== Main ===========*/


int main(int argv,char ** kwargs){
	/* Variable declaration */
	int p;
	int fd[2];
	
	int buffersize;
	char *buffer;
	int tmp=0;

	srand((unsigned int) time(NULL));
	
	/* Initialasing */
	if (argv<2) fprintf(stderr,"Buffersize: Incorrect arguments given.\n");
	buffersize=atoi(kwargs[1]);
	buffer=malloc(sizeof(char)*(buffersize+2));
	if (buffer==NULL) perror("Buffer: Malloc error");
	while (tmp<buffersize+2) *(buffer+tmp++)=' ' + (char) rand()%50;
	
	/* Main program */
	if (pipe(fd)<0) perror("Pipeing: Generation error");
	if ((p=fork())<0) perror ("Fork: Generation error");
	
	bor_signal(SIGPIPE,handler,0);


/*	alarm(1);*/
	/* Child */
	if (p==0){
			bor_signal(SIGALRM,handler,0);
		close(fd[1]);
		printf("Buffer generated, streaming in process.\n");
			alarm(1);
/*		printf("Each dot represents %d chars (%dkb).\n",1024*buffersize,buffersize*(int)sizeof(char));*/
		while ((tmp=read(fd[0],buffer,buffersize))>=0) readed+=tmp;
		exit(EXIT_SUCCESS);
	}
	/* Master */
	
	bor_signal(SIGCHLD,handler,0);
	close(fd[0]);

	while(write(fd[1],buffer,buffersize)>=0);
	return 0;
}

/* ========= Functions ========*/
void handler(int signal){
	switch(signal){
		case SIGPIPE:
			printf("Was that it ?\n");
			exit(EXIT_FAILURE);
			break;
		case SIGALRM:
			printf("Actual speed : %.2f mb/s\n",((float)readed)/1048576);
			readed=0;
			alarm(1);
			break;
		case SIGCHLD:
			printf("Child process closed : Shutting down !\n");
			exit(EXIT_FAILURE);
			break;
		default:
			printf("Signal unknown %d : Stopping now...\n",signal);
			exit(EXIT_FAILURE);
	}

}
