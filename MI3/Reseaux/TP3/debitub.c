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
	int nb_pipes, **pipes,tmp,*tmp_fd;
	char size_buffer,*buffer;
	int p; /* Process */ 
	int nb_ready; /* Pipes ready */
	int max_fd[2]={0,0};
	fd_set liste;
	
	if (nbargs<3) Exit("Incorrect number of arguments\nUsage: debitub <nb_pipes> <buffersize>");
	size_buffer=atoi(kwargs[2]);
	nb_pipes=atoi(kwargs[1]);
	if (!size_buffer|!nb_pipes) Exit("Arguments can't be void")

	pipes=malloc(sizeof(int*)*nb_pipes);
	if (!pipes) Error("(Malloc) Pipes");
	
	
	tmp=nb_pipes;
	while (tmp--){
		tmp_fd=malloc(sizeof(int)*2);
		if (!tmp_fd) Error("(Malloc) Pipes.");
		if (pipe(tmp_fd)) Error("(Pipe) Generation error");
		pipes[tmp]=tmp_fd;

		max_fd[0]=max_fd[0]>tmp_fd[0]?max_fd[0]:tmp_fd[0];
		max_fd[1]=max_fd[1]>tmp_fd[1]?max_fd[1]:tmp_fd[1];
		
	}

	if ((p=fork())<0) Error("(Fork) Generation Error");
	
	if (p){ /* Father Process */
		tmp=nb_pipes; while (tmp--) close(pipes[tmp][0]);
		
		buffer=malloc(sizeof(char)*size_buffer);
		if (!buffer) Error("(Malloc) Buffer");
		tmp=size_buffer; while(tmp--) *(buffer+tmp)='*';  *(buffer+size_buffer-1)='\0';
		while (1){
			FD_ZERO(&liste);
			
			tmp=nb_pipes; while(tmp--) FD_SET(pipes[tmp][1],&liste);
			nb_ready=select(max_fd[1]+1,NULL,&liste,NULL,NULL);
			if (nb_ready>0){
				tmp=nb_pipes; while(tmp--) if (FD_ISSET(pipes[tmp][1],&liste)){
					write(pipes[tmp][1],&buffer,size_buffer);
				}
			}	
		}
		
		return 0;
	} else { /* Child Process */
		tmp=nb_pipes;
		while (tmp--) close(pipes[tmp][1]);
		alarm(1);
		bor_signal(SIGALRM,&sig,0);
		
		while (1){
			FD_ZERO(&liste);
			
			tmp=nb_pipes; while(tmp--) FD_SET(pipes[tmp][0],&liste);
			nb_ready=select(max_fd[0]+1,&liste,NULL,NULL,NULL);
			if (nb_ready>0){
				tmp=nb_pipes; while(tmp--) if (FD_ISSET(pipes[tmp][0],&liste)){
					buffer=malloc(sizeof(char)*size_buffer);
					if (!buffer) Error("(Read) Buffer creation");
					read(pipes[tmp][0],&buffer,size_buffer);
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
		printf("%li b/s\n",readed);
		alarm(1);
	}
}
