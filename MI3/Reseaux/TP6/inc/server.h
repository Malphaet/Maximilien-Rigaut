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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <fcntl.h>

#include <netdb.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/un.h>

#include <stropts.h>
#include <poll.h>
#include "utils.h"

#ifndef __SERVER_H__
#define __SERVER_H__

/* Defines */
#define PORT 4242
#define MAXBUFFER 16384
#define MAX_USERS 20
#define MAX_MESSAGES 1000
#define MAX_PENDING 20
#define MAX(a,b) (a)>(b)?(a):(b)
/* Structures */
struct user{
	char login[40];
	char passwd[40];
	short status;
	int socket;
};

struct message{
	char message[1000];
	int sender; // index
	int sendto; //index
};

struct toidentify{
	char login[40];
	char passwd[40];
	int socket;
};

/* Prototype */

int create_user(char*,char*);
int set_login_user(struct toidentify*);

int find_socket(int);
int find_socket_toidentify(int);
int create_user_toidentify(int);

int add_message(char*,int,int);
int get_message(struct message*,fd_set*);
int send_message(struct message*);
int cut_message(char*,char*,const char*);

int cree_socket_ecoute();
void affiche_adresse_socket(int);

int prepare_read(fd_set*);
int prepare_write(fd_set*);
int global_wait();
#endif
