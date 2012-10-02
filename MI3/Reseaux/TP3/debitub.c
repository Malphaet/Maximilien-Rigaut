/*
 * debitub.c
 * This file is part of TP3
 *
 * Copyright (C) 2012 - Maximilien Rigaut
 *
 * TP3 is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * TP3 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with TP3. If not, see <http://www.gnu.org/licenses/>.
 */


/* Includes */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <bor-util.h>

/* Defines */
#define Error(a) {perror(a);printf("\n");exit(EXIT_FAILURE);}
#define Exit(a) {printf(a);printf("\n");exit(EXIT_FAILURE);}

long unsigned int readed=0;
/* Main program */
void sig(int signal);

int main(int nbargs,char**kwargs){
	int nb_pipes, *pipes,i,tmp_fd[2];
	char size_buffer,*buffer;
	int p; /* Process */ 
	int nb_ready; /* Pipes ready */
	int max_fd[2]={0,0};
	fd_set liste;
	
	if (nbargs<3) Exit("Incorrect number of arguments\nUsage: debitub <nb_pipes> <buffersize>");
	size_buffer=atoi(kwargs[2]);
	nb_pipes=atoi(kwargs[1]);
	if (!size_buffer|!nb_pipes) Exit("Arguments can't be void")

	pipes=malloc(sizeof(int)*nb_pipes*2);
	if (!pipes) Error("(Malloc) Pipes");
	
	
	for (i = 0; i < nb_pipes; i += 1){
/*		tmp_fd=malloc(sizeof(int)*2);*/
/*		if (!tmp_fd) Error("(Malloc) Pipes.");*/
		if (pipe(tmp_fd)) Error("(Pipe) Generation error");
		pipes[2*i]=tmp_fd[0];
		pipes[2*i+1]=tmp_fd[1];
		max_fd[0]=max_fd[0]>tmp_fd[0]?max_fd[0]:tmp_fd[0];
		max_fd[1]=max_fd[1]>tmp_fd[1]?max_fd[1]:tmp_fd[1];
/*		free(tmp_fd);*/
	}

	if ((p=fork())<0) Error("(Fork) Generation Error");
	
	if (p){ /* Father Process */
		
		for(i=0;i<nb_pipes;i++) close(pipes[i*2+0]);
		
		buffer=malloc(sizeof(char)*size_buffer);
		if (!buffer) Error("(Malloc) Buffer");
		for(i=0;i<nb_pipes;i++) buffer[i]='*'; buffer[size_buffer-1]='\0';
		while (1){
			FD_ZERO(&liste);
			
			for(i=0;i<nb_pipes;i++)  FD_SET(pipes[i*2+1],&liste);
			nb_ready=select(max_fd[1]+1,NULL,&liste,NULL,NULL);
			if (nb_ready>0){
				for(i=0;i<nb_pipes;i++) 
					if (FD_ISSET(pipes[i*2+1],&liste)) write(pipes[i*2+1],&buffer,size_buffer);
			}
		}
		
		return 0;
	} else { /* Child Process */
		
		for(i=0;i<nb_pipes;i++) close(pipes[i*2+1]);
		alarm(1);
		bor_signal(SIGALRM,&sig,0);
		
		while (1){
			FD_ZERO(&liste);
			
			for(i=0;i<nb_pipes;i++) FD_SET(pipes[i*2+0],&liste);
			nb_ready=select(max_fd[0]+1,&liste,NULL,NULL,NULL);
			
			if (nb_ready>0){
				for(i=0;i<nb_pipes;i++)
					if (FD_ISSET(pipes[i*2+0],&liste)){
						buffer=malloc(sizeof(char)*size_buffer);
						if (!buffer) Error("(Read) Buffer creation");
						
						read(pipes[i*2+0],&buffer,size_buffer);
						readed+=(long unsigned int)size_buffer;
					}
			}
		}
		return 0;
	}
	return 0;
}

void sig(int signal){
	if (signal==SIGALRM){
		printf("\r%.2f Mb/s ",((float)readed)/1048576);
		fflush(stdout);
		readed=0;
		alarm(1);
	}
}
