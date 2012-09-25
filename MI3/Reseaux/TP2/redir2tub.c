/*
 * redir2tub.c
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

/*#include <stdnoreturn.h>*/

/* ========= Defines ==========*/

#define SIZEBUFF 12
#define noreturn void

noreturn child1(void);
noreturn child2(void);
/* =========== Main ===========*/

int tube1[2],tube2[2];
char buff[SIZEBUFF];
	
int main(void){
	int p1,p2;

	/* Create Child 1 */
	if (pipe(tube1)) perror("Tube 1: creation aborted");
	p1=fork();
/*	if ((p1=fork())<0) perror("Child 1: Creation aborted");*/
	if (p1==0) child1();
	
	/* Create Child 2 */
	if (pipe(tube2)) perror("Tube 2: creation aborted");
	if ((p2=fork())<0) perror("Child 2: Creation aborted");
	if (p2==0) child2();
	
	/* Execute Main Program */
	close(tube1[0]); close(tube1[1]);
	close(tube2[1]);
	dup2(tube2[0],STDIN_FILENO);
	
	read(STDIN_FILENO,&buff,SIZEBUFF);
	write(STDERR_FILENO,buff,SIZEBUFF);
	
	while(wait(NULL)>0);
	return 0;
}

/* ========= Functions ========*/
noreturn child1(void){
	close(tube1[0]);
	dup2(tube1[1],STDOUT_FILENO);
/*	write(STDERR_FILENO,"Child 1 : Initialised\n",22);*/
	
	write(STDOUT_FILENO,"Child 1: OK\n",SIZEBUFF);
	
	close(tube1[0]);
	exit(EXIT_SUCCESS);
}

noreturn child2(void){
	close(tube1[1]); close(tube2[0]);
	dup2(tube1[0],STDIN_FILENO);
	dup2(tube2[1],STDOUT_FILENO);
/*	write(STDERR_FILENO,"Child 2 : Initialised\n",22);*/
	
	read(STDIN_FILENO,&buff,SIZEBUFF);
	write(STDERR_FILENO,buff,SIZEBUFF);
	write(STDOUT_FILENO,"Child 2: OK\n",SIZEBUFF);
	
	close(tube1[1]); close(tube2[0]);
	exit(EXIT_SUCCESS);
}
