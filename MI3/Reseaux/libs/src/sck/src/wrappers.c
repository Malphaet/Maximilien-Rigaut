/*
 * wrappers.c
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

#include "wrappers.h"

/* ========= Defines ==========*/


/* ========= Functions ========*/


/** \defgroup Wrappers Communication Managers
 * Handful of functions for managing communications, take care of everithing for you
 */
/** @{ */

/** Big sending function
 * @param recver_socket The socket to send through
 * @param sender_socket The sender's socket
 * @param type_message The type of the message (msg_type definitions are pretty clear)
 * @param msg The message itself
 */
int message_send(lsocket*recver_socket,msg_type type_message,char*msg,lsocket*sender_socket){
	lpacket*pck=lpacket_forge(type_message,msg);
	lpacket_send(recver_socket,pck,sender_socket);
	lpacket_drop(pck);
	return lpacket_snd_bytes;
}

/** Big receiving function 
 * @param recver_socket The socket used for receiving the message
 * @param sender_socket The socket with will contain the sender's socket (if binded)
 */
lpacket*message_receive(lsocket*recver_socket,lsocket*sender_socket){
	char*message=malloc(sizeof(char)*SIZE_BUFFER);
	lsocket*recv; lpacket*pck;
	if (message==NULL) ERROR("lPacket malloc");
	
	recv=lsocket_receive(recver_socket,message,SIZE_BUFFER);
	pck=lpacket_request(message);
	
	if (sender_socket!=NULL) *sender_socket=*recv;
	
	return pck;
}

/** Create new listening set (a basement: podrum in croatian) 
 * @param size Size of the future socket list
 */
lpodrum* make_lpodrum (int size,int type){
	lsocket**sock_list=malloc(sizeof(lsocket*)*size);
	lpodrum*podr=malloc(sizeof(lpodrum));
	if (sock_list==NULL) ERROR("Socket list malloc");
	if (podr==NULL) ERROR("Podrum list malloc");
	
	podr->cur_size=0;
	podr->max_size=size;
	podr->type=type;
	podr->sockets=sock_list;
/*	podr->*/
	
	return podr;
}

/** Add a num socket to the basement */
void add_lsocket(lpodrum*podr,lsocket*sock){
	if (podr->cur_size==podr->max_size) OUT("Podrum max size reached (basement overflow)");
	podr->sockets[podr->cur_size++]=sock;
}

/** Get the socket number (nb) */
lsocket* get_lsocket(lpodrum*podr,int nb){
	if (podr->cur_size-1<nb) OUT("Index out of range");
	return podr->sockets[nb];
}

/** Delete the socket (nb) from the basement */
int del_lsocket(lpodrum*podr,int nb){
	if (podr->cur_size-1<nb) return -1;
	printf("Heavy stuff not being done...\n");
	return -1;
}

/** Purge the podrum before using it 
 *
 * Note that it is NOT supposed to be user-trigerred
 */

void purge_lpodrum(lpodrum*podrum){
	podrum++;
	return;
}

/** Return the list from all the socket ready to communicate 
 * @param podr The lpodrum for the listening
 * @param timeout Timeout before forced return (-1 for disabling)
 */
int*listen_lpodrum(lpodrum*podr,int time){
	int i,j=0;
	int nbs,*ret;
	fd_set set,*r_ser=NULL,*w_set=NULL,*e_set=NULL;
	struct timeval timeout;
	if (time>0) {timeout.tv_sec=time;timeout.tv_usec=0;}
	
	/* Initialize the file descriptor set. */
	FD_ZERO (&set);
	
	/* Purge lpodrum */
	purge_lpodrum(podr);
	
	/* Set the fdset */
	for (i=0;i<(podr->cur_size);i+=1) FD_SET((get_lsocket(podr,i))->file,&set);
	
	/* Listen for awaiting requests */
	switch(podr->type){
		case 0: r_ser=&set; break;
		case 1: w_set=&set;	break;
		case 2: e_set=&set;	break;
		default: OUT("Unhandled mode");
	}
	nbs=select(podr->cur_size*sizeof(set),r_ser,w_set,e_set,time>0?&timeout:NULL);
	if (nbs<0) ERROR("Podrum select");
	
	/* Create the return list */
	ret=malloc(sizeof(int)*(nbs+1));
	if (ret==NULL) ERROR("Return indexv malloc");
	for (i=0;i<podr->cur_size/* && j<=nbs*/;i+=1) if (FD_ISSET(get_lsocket(podr,i)->file, &set)) ret[j++]=i;
	ret[j]=-1;
	
	return ret;
}

/** @} */
