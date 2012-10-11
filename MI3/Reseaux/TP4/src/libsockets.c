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
	/* Uber socket creation */
	if (access(p_socket,F_OK)==-1) mkfifo(p_socket,MODE_SOCKET);
	
	if (verbose) printf("Socket created: %s\n",p_socket);
	strcpy(addr,p_socket); socket->addr=addr;
	return socket;
}

/** Open the connection of the given socket */
void open_socket(sk_addr *socket,int mode){
	if ((socket->file=open(socket->addr,O_RDWR,mode))<0) ERROR("Socket opening was impossible");
}

/** Close a socket connection
 * @param shutdown Is the connection to be shutdown or just delete the pointer
 */
void close_socket(sk_addr *socket,int shutdown){
	close(socket->file);
	if (shutdown) unlink(socket->addr);
	free(socket);
}

/** Send string to the server */
int socket_send(sk_addr* socket,char*message,int bytes){
	return write(socket->file,message,bytes);
}

/** Receive string from the server */
int socket_receive(sk_addr* socket, char*message,int bytes){
	return read(socket->file,message,bytes);
}

/** A nicer way to communicate */
/** Will need struct packet{
 * int request;
 * char * message
 * }
 * packet_forge();
 * packet_request();
 * packet_message();
 * packet_send();
 * packet_receive();
 */
/** Sending a message, with less information to provide */
int socket_message_send(sk_addr *socket, char *type_message,char *message){
	int size=strlen(type_message)+strlen(message)+5;
	char *msg=malloc(sizeof(char)*size);
	if (msg==NULL) ERROR("Malloc error, given message impossible to write");
	sprintf(msg,"%s %s\n",type_message,message);
	return socket_send(socket,msg,size);
}
/** Receiving a message with less information to provide */
char *socket_message_receive(sk_addr *socket){
	char*message=malloc(sizeof(char)*SIZE_BUFFER);
	socket_receive(socket,message,SIZE_BUFFER);
	return message;
}
