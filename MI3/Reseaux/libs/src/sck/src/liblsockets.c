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
	lsocket*ret_sck=NULL;
	
	switch (type){
		case AF_UNIX:
			ret_sck=make_lsocket(((struct sockaddr_un*)sock)->sun_path);
/*			printf("%s\n",ret_sck->addr);*/
			break;
		case AF_INET:
			OUT("Unhandled mode");
/*			ret_sck=make_lsocket(((struct sockaddr_in*)sock)->sin_addr);*/
			break;
		default:
			OUT("Unhandled mode");
			break;
	}
	open_lsocket(ret_sck,type,mode);
	return ret_sck;
}

/** Bind the sending socket for answers
 *
 * @param send_sck the socket witch will be binded
 */
void bind_lsocket(lsocket*send_sck){
	unlink(send_sck->addr);
	if (bind(send_sck->file,(struct sockaddr*)send_sck->socket,sizeof(*send_sck->socket))<0) ERROR("Binding socket failed");
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

/** Send string to the server 
 * @param recver_socket The socket to send to
 * @param sender_socket The sender's socket 
 * @param message The message itself
 * @param bytes Length of the message (in bytes)
 */
int lsocket_send(lsocket*recver_socket,char*message,int bytes,lsocket*sender_socket){
	int write_to=recver_socket->file;
	if (sender_socket!=NULL) write_to=sender_socket->file;
	
	switch (recver_socket->mode){
		case SOCK_DGRAM:
			return sendto(write_to,message,bytes,0,
				(struct sockaddr*)recver_socket->socket,
				sizeof(((struct sockaddr_un*)recver_socket->socket)->sun_family)
				+strlen(((struct sockaddr_un*)recver_socket->socket)->sun_path));
		default:
			return write(write_to,message,bytes);
	}
}

/** Receive string from the socket */
lsocket* lsocket_receive(lsocket*sck, char*message,int bytes){
	unsigned int bsize=sizeof(struct sockaddr_un);
	lsocket*recv_sck=NULL;
	struct sockaddr*sock=malloc(sizeof(struct sockaddr));
	
	switch (sck->mode){
		case SOCK_DGRAM:
			lpacket_rcv_bytes=recvfrom(sck->file,message,bytes,0,sock,&bsize);
			if (lpacket_rcv_bytes<0) {
				printf("Receiving packet from %s\n",sck->addr);
				ERROR("Reciving packet");
			}
			if (sock!=NULL) recv_sck=make_from_socket((struct sockaddr*)sock,sck->type,sck->mode);

			return recv_sck;
		default:
			lpacket_rcv_bytes=read(sck->file,message,bytes);
			return NULL;
	}
}
/**@}*/
