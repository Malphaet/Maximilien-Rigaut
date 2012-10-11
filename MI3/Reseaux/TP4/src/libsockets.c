/*
 * libsockets.c
 * This file is part of libsockets
 *
 * Copyright (C) 2012 - Maximilien Rigaut
 *
 * libsockets is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * libsockets is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libsockets. If not, see <http://www.gnu.org/licenses/>.
 */

#include "libsockets.h"

/* ========= Defines ==========*/
int verbose;
/* ========= Functions ========*/

/** Create a socket from the given informations */
sk_addr* make_socket(char *p_socket){
	sk_addr *socket=malloc(sizeof(sk_addr));
	char*addr=malloc(sizeof(char)*SIZE_BUFFER);
	if (socket==NULL) ERROR("Socket malloc impossible")
	/** Uber socket creation */
	if (access(p_socket,F_OK)==-1) mkfifo(p_socket,MODE_SOCKET);
	
	if (verbose) printf("Socket created: %s\n",p_socket);
	strcpy(addr,p_socket); socket->addr=addr;
	return socket;
}

void open_socket(sk_addr *socket,int mode){
	if ((socket->file=open(socket->addr,O_RDWR,mode))<0) ERROR("Socket opening was impossible");
}

void close_socket(sk_addr *socket,int shutdown/**Is the connection to be shutdown or just delete the pointer*/){
	close(socket->file);
	if (shutdown) unlink(socket->addr);
	free(socket);
}

/** Send string to the server */
int socket_send(sk_addr* socket,char*message,int bytes){
/*	if (verbose) printf("Waiting %s\n",socket->addr);*/
	return write(socket->file,message,bytes);
}

/** Receive string from the server */
int socket_receive(sk_addr* socket, char*message,int bytes){
	return read(socket->file,message,bytes);
}
