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

/** @file liblsockets.c Socket Library (code) */

/* ========= Defines ==========*/

int verbose; /**< Verbosity of the program */

/* ========= Functions ========*/
/** \defgroup liblsockets Little Socket Library
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
	sck->sendto=NULL;
	
	return sck;
}

/** Open the connection of the given socket 
 * @param sck The socket to open
 * @param type Type of the connection AF_UNIX or other
 * @param mode Mode of the connection SOCK_DGRAM or other
 */
void open_lsocket(lsocket*sck,int type,int mode){
	struct sockaddr_un*sock_un; struct sockaddr_in*sock_in; 
	char*tmp; int address=0;
	struct hostent *result;
	if ((sck->file=socket(type,mode,0))<0) ERROR("Socket opening was impossible");
	
	switch (type){
		case AF_UNIX:
			sock_un=malloc(sizeof(struct sockaddr_un*));
			if (sock_un==NULL) ERROR("Socket malloc");
			
			sock_un->sun_family=type;
			strcpy(sock_un->sun_path,sck->addr);
			
			sck->socket=(struct sockaddr*)sock_un;
			sck->mode=mode; sck->type=type;
			break;
		case AF_INET:
			sock_in=malloc(sizeof(struct sockaddr_in*));
			if (sock_in==NULL) ERROR("Socket malloc");
			
			
			/* Worse than horrible any suggestion is welcome */
/*			sock_in->sin_family=type; */
/*			tmp=strtok(sck->addr,"."); 	address=(address|atoi(tmp))<<8; printf("%s\n",tmp);*/
/*			tmp=strtok(NULL,"."); 		address=(address|atoi(tmp))<<8; printf("%s\n",tmp);*/
/*			tmp=strtok(NULL,"."); 		address=(address|atoi(tmp))<<8; printf("%s\n",tmp);*/
/*			tmp=strtok(NULL,":"); 		address=(address|atoi(tmp)); printf("%s\n",tmp);*/
/*			tmp=strtok(NULL,"");*/
			
			sock_in->sin_addr.s_addr = htonl(address);
			sock_in->sin_port=htons(atoi(tmp));
			
/*			if (result!=NULL) printf("%s %d\n",result->h_addr_list[0],result->h_length);	*/
/*			else OUT("Given adress incorrect");*/
/*			sa.sin_addr.s_addr = htonl();*/
/*			sock_in->port=htons();*/
			
/*			sck->socket=(struct sockaddr*)sock_in;*/
			sck->mode=mode; sck->type=type;
			break;
		default:
			OUT("Unhandled mode");
			break;
	}
}

/** Create a connection from the given socket and informations
 * @param sock The socket received durring incoming transmission
 * @param type Type of the connection AF_UNIX or other
 * @param mode Mode of the connection SOCK_DGRAM or other
 */
 
lsocket*make_from_socket(struct sockaddr*sock,int type,int mode){
	lsocket*ret_sck=NULL;
	
	switch (type){
		case AF_UNIX:
			if(((struct sockaddr_un*)sock)->sun_path[0]==0) return NULL;
			ret_sck=make_lsocket(((struct sockaddr_un*)sock)->sun_path);
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
 * @param send_sck The socket to bind for answers
 */
void bind_lsocket(lsocket*send_sck){
	switch (send_sck->type){
		case AF_UNIX:
			unlink(send_sck->addr);
			if (bind(send_sck->file,(struct sockaddr*)send_sck->socket,sizeof(*send_sck->socket))<0) ERROR("Binding socket failed");
			break;
		case AF_INET:
			OUT("Unhandled mode");
			break;
		default:
			OUT("Unhandled mode");
			break;
	}
}

/** Connect the sending socket to another socket
 * @param sck The socket to be connected
 * @param recv_sck the socket witch will be connected to
 */
void connect_lsocket(lsocket*sck,lsocket*recv_sck){
	switch(sck->mode){
		case (SOCK_DGRAM):
			sck->sendto=recv_sck;
			break;
		case (SOCK_STREAM):
			OUT("Unhandled mode");
			break;
		default:
			OUT("Unhandled mode");
	}
}

/** Close a socket connection
 * @param sck The socket to close
 * @param shutdown Shall I shutdown or just free the memory ?
 */
void close_lsocket(lsocket*sck,int shutdown){
	switch (sck->type){
		case AF_UNIX:
			if (shutdown) unlink(sck->addr);
			break;
		case AF_INET:
			OUT("Unhandled mode");
			break;
		default:
			OUT("Unhandled mode");
			break;
	}
	
	close(sck->file);
	free(sck->socket);
	free(sck);
}

/** Send string to the server 
 * @param socket if connect_lsocket() wasn't used it's considered to be the receiver
 * If it was, it's considered to be the sender's socket and lsocket->sendto is considered to be the destination.
 * @param message The message itself
 * @param bytes Length of the message (in bytes)
 */
int lsocket_send(lsocket*socket,char*message,int bytes){
	int write_to;
	lsocket*recver_socket;
	if (socket->sendto!=NULL) {
		recver_socket=socket->sendto;
		write_to=socket->file;
	} else {
		recver_socket=socket;
		write_to=socket->file;
	}
	
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
	struct sockaddr*sock=calloc(1,sizeof(struct sockaddr));
	
	switch (sck->mode){
		case SOCK_DGRAM:
			lpacket_rcv_bytes=recvfrom(sck->file,message,bytes,0,sock,&bsize);
			if (lpacket_rcv_bytes<0) {
				printf("Error receiving packet from %s\n",sck->addr);
				ERROR("Reciving packet");
			}
			if (sock!=NULL) recv_sck=make_from_socket((struct sockaddr*)sock,sck->type,sck->mode);
			return recv_sck;
		default:
			lpacket_rcv_bytes=read(sck->file,message,bytes);
			return NULL;
	}
}

/** Sending a message, with less information to provide
 * @deprecated Only for debug purpose, a lot of informations can't be sent that way */
int lsocket_message_send(lsocket*sck,msg_type type_message,char *message){
	lpacket*pck=lpacket_forge(type_message,message);
	lpacket_send(sck,pck);
	lpacket_drop(pck);
	return lpacket_snd_bytes;
}

/**  Receive a message with less information to provide,
 * note that it is advised to use a packet instead.
 * @deprecated Only for debug purpose, a lot of information is lost in the process.
 */
char *lsocket_message_receive(lsocket*sck){
	char*message=malloc(sizeof(char)*SIZE_BUFFER);
	lsocket_receive(sck,message,SIZE_BUFFER);
	return message;
}

/**@}*/
