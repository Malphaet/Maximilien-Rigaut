/*
 * server.h
 * 
 * Copyright 2012 Maximilien Rigaut <max[dot]rigaut[at]orange.fr>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include "liblsockets.h"

#ifndef __SERV_H__
#define __SERV_H__

/* Defines */
#define MAX(a,b) (a)>(b)?(a):(b)
#define SIZE_PASSWD 64

/* Structures */

struct user{
	char login[40];
	char passwd[14];
	short status;
	lsocket* socket;
};

struct message{
	char message[1000];
	int sender; // index->socket ?
	int sendto; //index->socket ?
};

struct toidentify{
	char login[40];
	lsocket*socket;
};

/* Prototype */

int create_user(char*,char*);
int find_user(char*);
int set_login_user(struct toidentify*);

//int find_socket(int);
int find_socket_toidentify(lsocket*);
int create_user_toidentify(lsocket*);

//int add_message(char*,int,int);
//int get_message(struct message*);
//int send_message(struct message*);
//int cut_message(char*,char*,const char*);

//int prepare_read();
//int prepare_write();
//int global_wait();

#endif
