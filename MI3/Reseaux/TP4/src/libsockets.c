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
int verbose; /*< Verbosity of the program */

/* ========= Functions ========*/

/** \defgroup Libsockets
 * A very small lib, made mainly to avoid direct socket handling
 * 
 */
/** @{ */
 
/** Create a socket from the given informations */
socket* make_socket(char *p_socket){
	socket *sck=malloc(sizeof(socket));
	char*addr=malloc(sizeof(char)*SIZE_BUFFER);
	if (sck==NULL) ERROR("Socket malloc impossible");
	
	/* Socket creation */
	if (access(p_socket,F_OK)==-1) mkfifo(p_socket,MODE_SOCKET);
	if (verbose) printf("Socket created: %s\n",p_socket);
	strcpy(addr,p_socket); sck->addr=addr;
	
	return sck;
}

/** Open the connection of the given socket */
void open_socket(socket *sck,int mode){
	if ((sck->file=open(sck->addr,O_RDWR,mode))<0) ERROR("Socket opening was impossible");
}

/** Close a socket connection
 * @param shutdown Is the connection to be shutdown or just delete the pointer
 */
void close_socket(socket *sck,int shutdown){
	close(sck->file);
	if (shutdown) unlink(sck->addr);
	free(sck);
}

/** Send string to the server */
int socket_send(socket*sck,char*message,int bytes){
	return write(sck->file,message,bytes);
}

/** Receive string from the server */
int socket_receive(socket*sck, char*message,int bytes){
	return read(sck->file,message,bytes);
}
/**@}*/

/** \defgroup Packetlib 
 * Packetlib is a small lib build ontop of libsockets.
 * 
 * It is used extensively to avoid any interference with the implementation of the sockets.
 * The main function you should use for communication is packet_receive().
 *
 * However, the following will allow you to handle basic communication:
 * \li packet_forge()
 * \li packet_drop()
 * \li packet_send()
 *
 * Moreover, the following function should be avoided:
 * \li packet_message()
 * @{
 */

/** Sending a message, with less information to provide */
int socket_message_send(socket *sck,msg_type type_message,char *message){
	packet*pck=packet_forge(type_message,message);
	packet_send(sck,pck);
	packet_drop(pck);
	return packet_snd_bytes;
}

/** [Deprecated] Receive a message with less information to provide,
 * note that it is advised to use a packet instead.
 */
char *socket_message_receive(socket*sck){
	char*message=malloc(sizeof(char)*SIZE_BUFFER);
	socket_receive(sck,message,SIZE_BUFFER);
	return message;
}

/** Forge a packet with the given information.
 *
 * For memory usage reason, the message is copied not linked, free it if needed.
 */
packet*packet_forge(msg_type request,char *message){
	packet*pck=malloc(sizeof(packet));
	char*pck_message=malloc(sizeof(char)*(strlen(message)+1));
	if (pck==NULL) ERROR("Malloc packet");
	if (pck==NULL) ERROR("Malloc message");
	if (!strcmp(message,"")) pck_message[0]=42;
	else strcpy(pck_message,message);
	pck->request=request;
	pck->message=pck_message;
	return pck;
}

/** Drop a packet and free the allocated memory. */
void packet_drop(packet*pck){
	free(pck->message);free(pck);
}

/** Create a packet from the given message. */
packet*packet_request(char*message){
	int request;
	char*pck_message;
	request=atoi(strtok(message," "));
	pck_message=strtok(NULL,"\n");
	return packet_forge(request,pck_message);
}

/** Create a message from given packet. */
char *packet_message(packet*pck){
	int size=strlen(pck->message)+5;
	char*message=malloc(sizeof(char)*size);
	if (message==NULL) ERROR("Packet malloc");
	sprintf(message,"%d %s\n",pck->request,pck->message);
	return message;
}

/** Send a packet through the given socket.
 *
 * Note that you will NOT receive the number of readed packets.
 * You can access that information through ::packet_snd_bytes.
 */
void packet_send(socket*sck,packet*pck){
	packet_snd_bytes=socket_send(sck,packet_message(pck),strlen(pck->message)+5);
}

/** Receive a packet through the given socket
 *
 * Note that you will receive a socket not the number of readed packets. 
 * You can access that information through packet_rcv_bytes.
 */
packet*packet_receive(socket*sck){
	char*message=malloc(sizeof(char)*SIZE_BUFFER);
	if (message==NULL) ERROR("Packet malloc");
	packet_rcv_bytes=socket_receive(sck,message,SIZE_BUFFER);
	return packet_request(message);
}
/** }@ */
