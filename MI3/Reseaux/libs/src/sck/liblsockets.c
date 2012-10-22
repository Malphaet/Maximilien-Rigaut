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
int message_send(lsocket*recv_sck,msg_type type_message,char*msg,lsocket*send_socket){
	lpacket*pck=lpacket_forge(type_message,msg);
	lpacket_send(recv_sck,pck,send_socket);
	lpacket_drop(pck);
	return lpacket_snd_bytes;
}

/** Big receiving function */
lpacket*message_receive(lsocket*recv_sck,lsocket*send_socket){
	char*message=malloc(sizeof(char)*SIZE_BUFFER);
	lsocket*recv; lpacket*pck;
	if (message==NULL) ERROR("lPacket malloc");
	
	recv=lsocket_receive(recv_sck,message,SIZE_BUFFER);
	pck=lpacket_request(message);

	if (send_socket!=NULL) send_socket=recv;
	
	return pck;
}

/** @} */


/** \defgroup liblsockets
 * A very small lib, made mainly to avoid direct socket handling
 * 
 */
/** @{ */
 
/** Create a socket from the given informations 
 * @param name Address of the socket
 * @param type Type of the connection AF_UNIX or other
 * @param more Mode of the connection SOCK_DGRAM or other
 * @param bnnd Only solution for now: should I bind it or not ?
 */
lsocket* make_lsocket(char*name){
	lsocket*sck=malloc(sizeof(lsocket));
	char*addr=malloc(sizeof(char)*SIZE_ADDR);
	if (sck==NULL) ERROR("Socket malloc impossible");
	if (addr==NULL) ERROR("Socket naming impossible");
	
	/* Socket creation */
	if (verbose>1) printf("Socket created: %s\n",name);
	strcpy(addr,name); sck->addr=addr;
	
	return sck;
}

/** Open the connection of the given socket 
 * @param type Type of the connection AF_UNIX or other
 * @param more Mode of the connection SOCK_DGRAM or other
 */
void open_lsocket(lsocket*sck,int type,int mode){
	struct sockaddr_un*sock_un;
/*	struct sockaddr*sock;*/
	if ((sck->file=socket(type,mode,0))<0) ERROR("Socket opening was impossible");
	
	switch (type){
		case AF_UNIX:
			sock_un=malloc(sizeof(struct sockaddr_un*));
			if (sock_un==NULL) ERROR("Socket malloc");
			sock_un->sun_family=type;
			strcpy(sock_un->sun_path,sck->addr);
			sck->socket=(struct sockaddr*)sock_un;
			sck->mode=mode;
			sck->type=type;
			break;
		default:
			OUT("Unhandled mode");
			break;
	}
}

/** Create a connection from the given socket and informations 
 * @param type Type of the connection AF_UNIX or other
 * @param more Mode of the connection SOCK_DGRAM or other
 */
lsocket*make_from_socket(struct sockaddr*sock,int type,int mode){
	lsocket*sck=malloc(sizeof(lsocket));
	struct sockaddr_un*sock_un; struct sockaddr_in*sock_in;
	if (sck==NULL) ERROR("Socket malloc impossible");
/*	printf("%s\n",(char*)sock);*/
	sck->type=type;
	sck->mode=mode;
	sck->socket=sock;
	
	switch (type){
		case AF_UNIX:
			sock_un=(struct sockaddr_un*) sock;
			sck->addr=malloc(sizeof(char)*50);
			printf("%p\n",(void*)sck->addr);
			strcpy(sck->addr,sock_un->sun_path);
/*			printf("%s\n",sock_un->sun_path);*/
			break;
		case AF_INET:
			sock_in=(struct sockaddr_in*) sock;
			strcpy(sck->addr,inet_ntoa(sock_in->sin_addr));
			break;
		default:
			OUT("Unhandled mode");
			break;
	}
	return sck;
}

/** Bind the sending socket for answers
 *
 * @param send_sck the socket witch will be binded
 */
void bind_lsocket(lsocket*send_sck){
	unlink(send_sck->addr);
	if (bind(send_sck->file,(struct sockaddr*)send_sck->socket,sizeof(*send_sck->socket))<0) ERROR("Binding socket failed"); /* TODO: Check */
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
int lsocket_send(lsocket*recv_sck,char*message,int bytes,lsocket*send_sck){
	struct sockaddr_un*ss;
	switch (recv_sck->mode){
		case SOCK_DGRAM:
			ss=(struct sockaddr_un*) send_sck->socket;
			sendto(recv_sck->file,message,bytes,0,(struct sockaddr*)send_sck->socket,sizeof(ss->sun_family)+strlen(ss->sun_path));
			printf("Send name: %s\n",((struct sockaddr_un*)send_sck->socket)->sun_path);
			return 8;
		default:
			return write(recv_sck->file,message,bytes);
	}
}

/** Receive string from the socket */
lsocket* lsocket_receive(lsocket*sck, char*message,int bytes){
	unsigned int bsize=sizeof(struct sockaddr_un);
	lsocket*recv_sck;
	struct sockaddr*sock=malloc(sizeof(struct sockaddr));
	
	switch (sck->mode){
		case SOCK_DGRAM:
			WHERE;
			printf("Old size %d\n",bsize);
			lpacket_rcv_bytes=recvfrom(sck->file,message,bytes,0,sock,&bsize);
/*			recv_sck=make_from_socket((struct sockaddr*)sock,sck->type,sck->mode);*/
			WHERE;
			printf("New size %d\n",bsize);
			return recv_sck;
		default:
			lpacket_rcv_bytes=read(sck->file,message,bytes);
			return NULL;
	}
}
/**@}*/


/** \defgroup Packetlib 
 * Packetlib is a small lib build ontop of liblsockets.
 * 
 * It is used extensively to avoid any interference with the implementation of the sockets.
 * The main functions you should use for communication are the wrappers message_send() message_receive().
 *
 * However, the following will allow you to handle basic communication:
 * \li lpacket_forge()
 * \li lpacket_send()
 * \li lpacket_drop()
 *
 * Moreover, the following functions should be avoided:
 * \li lpacket_message()
 * \li lpacket_receive()
 * @{
 */

/** Sending a message, with less information to provide */
int lsocket_message_send(lsocket*sck,msg_type type_message,char *message){
	lpacket*pck=lpacket_forge(type_message,message);
	lpacket_send(sck,pck,NULL);
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
 * @param recv_sck Witch socket will receive the packet
 * @param send_sck Witch socket is the sender
 */
void lpacket_send(lsocket*recv_sck,lpacket*pck,lsocket*send_sck){
	lpacket_snd_bytes=lsocket_send(recv_sck,lpacket_message(pck),strlen(pck->message)+5,send_sck);
}

/** Receive a packet through the given socket
 *
 * Note that you will receive a socket not the number of readed packets. 
 * You can access that information through packet_rcv_bytes.
 */
lpacket*lpacket_receive(lsocket*sck){
	char*message=malloc(sizeof(char)*SIZE_BUFFER);
	if (message==NULL) ERROR("lPacket malloc");
	lsocket_receive(sck,message,SIZE_BUFFER);
	return lpacket_request(message);
}
/** }@ */
