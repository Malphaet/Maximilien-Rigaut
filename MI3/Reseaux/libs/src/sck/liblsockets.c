/*
 * liblsockets.c
 * This file is part of liblsockets
 *
 * Copyright (C) 2012 - Maximilien Rigaut
 *
 * liblsockets is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * liblsockets is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with liblsockets. If not, see <http://www.gnu.org/licenses/>.
 */

#include "liblsockets.h"


/* ========= Defines ==========*/
int verbose; /*< Verbosity of the program */

/* ========= Functions ========*/


/** \defgroup Wrappers Communication Managers
 * Two functions for managing communications, take care of everithing for you
 */
/** @{ */

/** Big sending function 
 * Note that it will just call socket_message_send() because it's actually the best function for that.
 */
int message_send(lsocket*sck,msg_type type_message,char*msg){
	return lsocket_message_send(sck,type_message,msg);
}

/** Kinda deprecated but well, you can't have everything */
char*message_receive(lsocket*sck){
	lpacket*pck=lpacket_receive(sck);
	char*msg=malloc(sizeof(char)*strlen(pck->message));
	strcpy(pck->message,msg);
	lpacket_drop(pck);
	return msg;
}

/** @} */


/** \defgroup liblsockets
 * A very small lib, made mainly to avoid direct socket handling
 * 
 */
/** @{ */
 
/** Create a socket from the given informations 
 * @param name Address of the socket
 */
lsocket* make_lsocket(char*name){
	lsocket*sck=malloc(sizeof(lsocket));
	char*addr=malloc(sizeof(char)*SIZE_ADDR);
	if (sck==NULL) ERROR("Socket malloc impossible");
	
	/* Socket creation */
	if (verbose>1) printf("Socket created: %s\n",name);
	strcpy(addr,name); sck->addr=addr;

	return sck;
}

/** Open the connection of the given socket 
 * @param type Type of the connection AF_UNIX or other
 * @param more Mode of the connection SOCK_DGRAM or other
 * @param bnd Only solution for now: should I bind it or not ? 1: Local, 0:Distant
 */
void open_lsocket(lsocket*sck,int type,int mode,int bnd){
	struct sockaddr_un*sock_un;
/*	struct sockaddr*sock;*/
	if ((sck->file=socket(type,mode,0))<0) ERROR("Socket opening was impossible");
	switch (mode){
		case SOCK_DGRAM:
			sock_un=malloc(sizeof(struct sockaddr_un*));
			if (sock_un==NULL) ERROR("Socket malloc");
			sock_un->sun_family=type;
			strcpy(sock_un->sun_path,sck->addr);
			sck->socket=sock_un;
			sck->mode=mode;
			sck->type=type;
			if (bnd) {
				unlink(sck->addr);
				if (bind(sck->file,(struct sockaddr*)sock_un,sizeof(*sock_un))<0) ERROR("Binding socket failed");
			}
			break;
		default:
			OUT("Unhandled mode");
			break;
	}
}


/** Close a socket connection
 * @param Shutdown shall I shutdown or just free the memory ?
 */
void close_lsocket(lsocket*sck,int shutdown){
	switch (sck->type){
		case AF_UNIX:
			if (shutdown) unlink(sck->addr);
			break;
		default:
			break;
	}
	
	close(sck->file);
	free(sck->socket);
	free(sck);
}

/** Send string to the server */
int lsocket_send(lsocket*sck,char*message,int bytes){
	switch (sck->mode){
		case SOCK_DGRAM:
			return sendto(sck->file,message,bytes,0,(struct sockaddr*)sck->socket,sizeof(*(sck->socket)));
		default:
			return write(sck->file,message,bytes);
	}
}

/** Receive string from the server */
int lsocket_receive(lsocket*sck, char*message,int bytes){
	unsigned int bsize=sizeof(*(sck->socket));
	switch (sck->mode){
		case SOCK_DGRAM:
			return recvfrom(sck->file,message,bytes,0,(struct sockaddr*)sck->socket,&bsize);
		default:
			return read(sck->file,message,bytes);
	}
}
/**@}*/


/** \defgroup Packetlib 
 * Packetlib is a small lib build ontop of liblsockets.
 * 
 * It is used extensively to avoid any interference with the implementation of the sockets.
 * The main function you should use for communication is lpacket_receive() and lsocket_message_send().
 *
 * However, the following will allow you to handle basic communication:
 * \li lpacket_forge()
 * \li lpacket_send()
 * \li lpacket_drop()
 *
 * Moreover, the following function should be avoided:
 * \li lpacket_message()
 * @{
 */

/** Sending a message, with less information to provide */
int lsocket_message_send(lsocket*sck,msg_type type_message,char *message){
	lpacket*pck=lpacket_forge(type_message,message);
	lpacket_send(sck,pck);
	lpacket_drop(pck);
	return lpacket_snd_bytes;
}

/** [Deprecated] Receive a message with less information to provide,
 * note that it is advised to use a packet instead.
 */
char *lsocket_message_receive(lsocket*sck){
	char*message=malloc(sizeof(char)*SIZE_BUFFER);
	lsocket_receive(sck,message,SIZE_BUFFER);
	return message;
}

/** Forge a packet with the given information.
 *
 * For memory usage reason, the message is copied not linked, free it if needed.
 */
lpacket*lpacket_forge(msg_type type,char *message){
	lpacket*pck=malloc(sizeof(lpacket));
	char*pck_message=malloc(sizeof(char)*(strlen(message)+1));
	if (pck==NULL) ERROR("Malloc lpacket");
	if (pck==NULL) ERROR("Malloc message");
	if (!strcmp(message,"")) pck_message[0]=42;
	else strcpy(pck_message,message);
	pck->type=type;
	pck->message=pck_message;
	return pck;
}

/** Drop a packet and free the allocated memory. */
void lpacket_drop(lpacket*pck){
	free(pck->message);free(pck);
}

/** Create a packet from the given message. */
lpacket*lpacket_request(char*message){
	int type;
	char*pck_message;
	type=atoi(strtok(message," "));
	pck_message=strtok(NULL,"\n");
	return lpacket_forge(type,pck_message);
}

/** Create a message from given packet. */
char *lpacket_message(lpacket*pck){
	int size=strlen(pck->message)+5;
	char*message=malloc(sizeof(char)*size);
	if (message==NULL) ERROR("lPacket malloc");
	sprintf(message,"%d %s\n",pck->type,pck->message);
	return message;
}

/** Send a packet through the given socket.
 *
 * Note that you will NOT receive the number of readed packets.
 * You can access that information through ::packet_snd_bytes.
 */
void lpacket_send(lsocket*sck,lpacket*pck){
	lpacket_snd_bytes=lsocket_send(sck,lpacket_message(pck),strlen(pck->message)+5);
}

/** Receive a packet through the given socket
 *
 * Note that you will receive a socket not the number of readed packets. 
 * You can access that information through packet_rcv_bytes.
 */
lpacket*lpacket_receive(lsocket*sck){
	char*message=malloc(sizeof(char)*SIZE_BUFFER);
	if (message==NULL) ERROR("lPacket malloc");
	lpacket_rcv_bytes=lsocket_receive(sck,message,SIZE_BUFFER);
	return lpacket_request(message);
}
/** }@ */
