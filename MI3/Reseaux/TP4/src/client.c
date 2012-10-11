/*
 * client.c
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
#include "client.h"

/* ========= Defines ==========*/
#define PATH_TEMP_SOCK "tmp/tube"
int verbose;
/* =========== Main ===========*/
int main (int argc, char **argv){
	verbose=0;
	if (argc<2) OUT("Incorrect number of arguments\nUsage:\nclient <sock_addr>");
	if (argc>2) verbose=atoi(argv[2]);
	client_socket(argv[1]);
	return 0;
}

/* ========= Functions =========*/

/** A basic client, note that he will create the sockets not the server */
void client_socket(char *path){
	sk_addr* main_socket=make_socket(path);
	sk_addr**new_socket;
	/** Connect to the given socket address */
	open_socket(main_socket,S_IWUSR/*MODE_SOCKET*/);
	/** Creation of the two sockets */
	new_socket=open_communication();
	/** Handshake with the server
	 * Send the socket to listen to */
	if (handshake(main_socket,new_socket)<0) OUT("The server didn't accepted connection");
	/** Wait for user requests */
	close_socket(main_socket,0);
	close_socket(new_socket[0],1);
	close_socket(new_socket[1],1);
}

/** Open a new communication to the server */
sk_addr** open_communication(){
	sk_addr** sockets=malloc(sizeof(sk_addr*)*2);
	char paths[2][SIZE_BUFFER];
	if (sockets==NULL) ERROR("Sockets malloc error");
	/** Generating names */
	sprintf(paths[0],"%s_r_%d.sock",PATH_TEMP_SOCK,getpid());
	sprintf(paths[1],"%s_w_%d.sock",PATH_TEMP_SOCK,getpid());
	/** Generating sockets */
	sockets[0]=make_socket(paths[0]);
	sockets[1]=make_socket(paths[1]);
	/** Opening sockets */
	open_socket(sockets[0],S_IRUSR);
	open_socket(sockets[1],S_IWUSR);
	if (verbose) printf("The following sockets were created: %s:%s\n",sockets[0]->addr,sockets[1]->addr);
	return sockets;
}

/** Have a handshake with the server, return -1 if the communication cannot be established */
int handshake(sk_addr*main_socket,sk_addr**sockets){
	char message[SIZE_BUFFER*2];
	/** Forging message */
	sprintf(message,"%s:%s\n",sockets[0]->addr,sockets[1]->addr);
	if (verbose) printf("The following message wil be send to the server: %s",message);
	if (socket_send(main_socket,message,strlen(message))<0) OUT("Cannot send message to the server");
	if (verbose) printf("Waiting for server response...\n");
	
	socket_receive(sockets[0],message,SIZE_BUFFER);
	if (verbose) printf("Received %s from the server\n",message);
	if (strcmp(message,SOCKET_RECEIVED)==0) return 1;
	else return -1;
}
