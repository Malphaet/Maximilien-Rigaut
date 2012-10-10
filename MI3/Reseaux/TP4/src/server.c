/*
 * server.c
 * This file is part of TP4
 *
 * Copyright (C) 2012 - Maximilien Rigaut
 *
 * TP4 is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * TP4 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with TP4. If not, see <http://www.gnu.org/licenses/>.
 */

/* ========= Includes =========*/
#include "server.h"

/* ========= Defines ==========*/

/* Environnement Variables */
#define RW S_IRUSR|S_IWUSR

/* Paths */
#define P_DICT ""
#define P_SOCKET "main.sock"

/* Boundaries */
#define SIZE_BUFFERS 2000

/* =========== Main ===========*/

annuary **Dict;

int main(int nbargs,char **argv){
/*	int p_master,p_socket;*/
	char *p_dict_name,*p_socket; /** Path to the dictionnary and to the main communicating socket */
	char p_sock_w[SIZE_BUFFERS],p_sock_r[SIZE_BUFFERS]; /** Sockets names */
	
	int fd_new_socket;
	char socket_info[SIZE_BUFFERS]; /** What is red from the incomming transmission */
	int size_socket_info; /* Actual size of the given information */
	
	int p; /* Name of the current process */
	
	/** Checking variables */
	if (nbargs<3) OUT("Syntax incorrect\nUsage:\n  server <path_dict> <path_fifo>");
	
	/** Initialisation of main variables */
	p_dict_name=argv[1]; p_socket=argv[2];
	
	unlink(p_socket); if (mkfifo(p_socket,RW)<0) ERROR("Main socket");
	load_dict(p_dict_name,Dict);
	
	/* Server core */
	while(1){
		if((fd_new_socket=open(p_socket,O_RDWR))<0) ERROR("Oppening new socket");
		if ((size_socket_info=read(fd_new_socket,&socket_info,SIZE_BUFFERS))<0) ERROR("Reading new Socket");
		
		if ((sscanf(p_sock_w,"%s %s",p_sock_r,p_sock_w))<0) ERROR("Ill formated feed");
		
		if ((p=fork())<0) ERROR("Forking child");
		if (p) child_socket(p_sock_r,p_sock_w);

		close(fd_new_socket);
	}
	close(fd_new_socket); unlink(p_socket);
	
	return 0;
}

/* ========== Functions ==========*/

void child_socket(char*p_sock_r,char*p_sock_w){
/*	Split sockets, create FD*/
	while(1);
/*	Loop*/
/*		Wait request */
/*		Analyse*/
/*		Seek*/
/*		Send*/
/*	End Loop*/
/*	Close*/
	Dict++;
/*	p_fifo++;*/
}

void load_dict(char*path,annuary **Dict){
	annuary * dic=malloc(sizeof(annuary));
	path++; /* Load dict */
	strcpy(dic->name,"Mooo");
	strcpy(dic->numero,"0478");
	*Dict=dic;
}
