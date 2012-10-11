/*
 * libsockets.h
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

#ifndef __LIBSOCKETS_H__
#define __LIBSOCKETS_H__

/* ========= Includes =========*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "utils.h"

/* ========= Defines ==========*/
#define MODE_RW S_IRUSR|S_IWUSR
#define MODE_SOCKET MODE_RW

#define SOCKET_RECEIVED "RCV"
#define SOCKET_KEEPALIVE "K-A"
#define SOCKET_MESSAGE "MSG"

#define SOCKET_MODE_READ S_IRUSR
#define SOCKET_MODE_WRITE S_IWUSR

/** Global variables */
/* @param packet_rcv_bytes Number of received bytes
 * @param packet_snd_bytes Number of sended bytes
 */
int packet_rcv_bytes;
int packet_snd_bytes;

/* ========= Typedef ==========*/

/** The type of message sent through the socket */
enum msg_enum{
	msg_recv,
	msg_keep,
	msg_text
}; typedef enum msg_enum msg_type;

/** Socket */
struct sk_addr{
	char* addr;
	int file;
}; typedef struct sk_addr socket;

/** Packet */
struct pk_struct {
	msg_type request;
	char*message;
}; typedef struct pk_struct packet;

/* ======== Prototype =========*/

/* Low level communication */
socket*	 make_socket	(char *);
void 	 open_socket	(socket*,int);
void 	 close_socket	(socket*,int);
int 	 socket_send	(socket*,char*,int);
int 	 socket_receive	(socket*,char*,int);
/* High level communication */
int 	 socket_message_send	(socket*,msg_type,char*);	/* Public: Send message */
char*	 socket_message_receive	(socket*);						/* Deprecated */
/* Packet lib */
packet*	 packet_forge	(msg_type,char*);
void 	 packet_drop	(packet*);
packet*	 packet_request	(char*);
char*	 packet_message	(packet*);
void 	 packet_send	(socket*,packet*);
packet*	 packet_receive	(socket*);								/* Public: Receive packet */

#endif /* __LIBSOCKETS_H__ */


