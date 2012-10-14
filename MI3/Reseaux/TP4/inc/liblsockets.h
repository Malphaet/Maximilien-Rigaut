/*
 * liblsockets.h
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

#ifndef __liblsockets_H__
#define __liblsockets_H__

/* ========= Includes =========*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "utils.h"

/* ========= Defines ==========*/


#define SOCKET_MODE_READ S_IRUSR
#define SOCKET_MODE_WRITE S_IWUSR
#define MODE_SOCKET SOCKET_MODE_READ|SOCKET_MODE_WRITE


#define KEEP_ALIVE 42
#define LATENCY 1
#define SIZE_BUFFER 1024

/* Global variables */
int packet_rcv_bytes; /** Number of received bytes */
int packet_snd_bytes; /** Number of sended bytes */

/* ========= Typedef ==========*/

/** @enum Message type
 * @brief The type of message sent through the socket
 * 
 * Keep in mind that, as an enum, this will be integers during runtime.
 * Beside that, don't be afraid if you see strange int in your packets.
 * 
 * Explanations of tags:
 * \li The tag [core] means it's only meant for the core program (you're the boss though)
 * \li The tag [program] means it's meant to be used by the program to cmmunicate.
 * \li The tag [msg] means the packet is carring a text-based message
 * \li The tag [nfo] means the packet is carring an information
 * \li The tag [wrn] means the packet is reporting a warning
 * \li The tag [err] means the packet is reporting an error
 */
enum msg_enum{
	msg_recv,	/**< [nfo]:[program] Message received */
	msg_keep,	/**< [nfo]:[core] [TBI] Keep-alive */
	msg_text,	/**< [msg]:[program] String sent */
	msg_warnings, 	/**< Not a message: Upper that this are warnings */
	msg_wait,	/**< [wrn]:[core] [NYI] Server overloaded, wait */
	msg_errors, 	/**< Not a message: Upper that this are errors */
	msg_kill,	/**< [err]:[program] The connection is to be shutdown, process now */
	msg_err,	/**< [err]:[core] [NYI] (Unknown) Error in received socket */
	msg_die,	/**< [err]:[core] [NYI] Server died, will not process requests anymore */
	msg_wtf		/**< [err]:[program] Request isn't the the one expected, I don't know what to do ! Abort ! Abort !*/
}; typedef enum msg_enum msg_type;

/**
 * @brief Small wraping socket
 */
struct sk_addr{
	char* addr;		/**< Path to the socket */
	int file;		/**< The file descriptor to use */
}; typedef struct sk_addr lsocket;

/**
 * @brief A raw packet, for abstraction purpose
 *
 * Note that a socket MUST be newline free, as it is used to end packets (see packet_forge() for details)
 */
struct pk_struct {
	msg_type type;		/**< The request being done, important for having normalised communications */
	char*message;		/**< The body of the message, can be empty */
}; typedef struct pk_struct lpacket;

/* ======== Prototype =========*/

/* Wrappers */
int 	message_send			(lsocket*,msg_type,char*);
char*	message_receive			(lsocket*);
char*	message_exchange		(lsocket*,msg_type,char*,lsocket*,msg_type);

/* Low level communication */
lsocket* make_socket	(char *);
void 	 open_socket	(lsocket*,int);
void 	 close_socket	(lsocket*,int);
int 	 socket_send	(lsocket*,char*,int);
int 	 socket_receive	(lsocket*,char*,int);
/* High level communication */
int 	 socket_message_send	(lsocket*,msg_type,char*);	/* Public: Send message */
char*	 socket_message_receive	(lsocket*);					/* Deprecated */
/* Packet lib */
lpacket* packet_forge	(msg_type,char*);
void 	 packet_drop	(lpacket*);
lpacket* packet_request	(char*);
char*	 packet_message	(lpacket*);
void 	 packet_send	(lsocket*,lpacket*);
lpacket* packet_receive	(lsocket*);							/* Public: Receive packet */

#endif /* __liblsockets_H__ */


