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

/* ========= Typedef ==========*/
struct sk_fifo{
	char* addr;
	int file;
};
struct pk_struct {
	int request;
	char*message;
};

typedef struct sk_fifo sk_addr;
typedef struct pk_struct packet;

/* ======== Prototype =========*/

sk_addr* make_socket	(char *);
void 	 open_socket	(sk_addr*,int);
void 	 close_socket	(sk_addr*,int);
int 	 socket_send	(sk_addr*,char*,int);
int 	 socket_receive	(sk_addr*,char*,int);

#endif /* __LIBSOCKETS_H__ */


