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
#include "version.h"

#ifndef __SERV_H__
#define __SERV_H__

/* Defines */
#define MAX(a,b) (a)>(b)?(a):(b)
#define SIZE_PASSWD 64

#define DELETE_SOCKET {del_lsocket(sockets,actives_sockets[i]);WHERE;}

#define MSG_CONNATMP printf("[SERVER] Unregistered user \"%s\" attempted to connect <%s>\n",pck->message,sender->addr);
#define MSG_CONNPROG printf("[SERVER] %s is attempting to connect <%s>\n",pck->message,sender->addr);
#define MSG_CONNPASS printf("[SERVER] Unregistered user is sending a password (%s) <%s>\n",pck->message,sender->addr);
#define MSG_WRNGPASS printf("[SERVER] User sent a wrong passwd %s <%s>\n",pck->message,sender->addr);
#define MSG_USERCONN printf("[SERVER] User <%s> is connected\n",sender->addr);
#define MSG_RECEIVED printf("[%s] sended %s\n",sender->addr,pck->message);
#define MSG_CLNTQUIT printf("[Server] Client diconnected <%s>\n",sender->addr);

#define SND_ACK message_send(sender,msg_recv,"[SERVER] Everything's running smoothly.");
#define SND_CONNDENY message_send(sender,msg_kill,"[SERVER] I'm afraid I can't let you in.");
#define SND_CONNPROC sprintf(buffer,"[SERVER] I don't beleive you are %s.",pck->message);message_send(sender,msg_pass,buffer);
#define SND_MSGGREET message_send(sender,msg_text,"[SERVER] It's been a looong time");
#define SND_CLNTQUIT message_send(sender,msg_kill,"[SERVER] This conversation can serve no purpose any more. Goodbye");

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

int find_socket(lsocket*);
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
