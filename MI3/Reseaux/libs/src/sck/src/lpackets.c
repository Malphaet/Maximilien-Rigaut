/*
 * lpackets.c
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

#include "lpackets.h"

/* ========= Defines ==========*/

/* ========= Functions ========*/
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


