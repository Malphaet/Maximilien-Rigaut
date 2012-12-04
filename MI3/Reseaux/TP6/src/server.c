/*
 * server.c
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
 * 
 */
#if defined __STRICT_ANSI__ && !defined _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include "server.h"
#include "liblsockets.h"
#include <signal.h>

#define PORT 4242
#define MAXBUFFER 16384
#define MAX_USERS 20
#define MAX_MESSAGES 1000
#define MAX_PENDING 20

struct user allusers[MAX_USERS];
struct message allmessages[MAX_MESSAGES];
struct toidentify alltoidentify[MAX_PENDING];
int nbusers,nbmessages,nbtoidentify;
volatile int should_quit;
#include "functions.c"

void termination_handler (int signum){
	if (signum==SIGINT||signum==SIGTERM){
		printf("\r[Server] Shutting Down...\n");
		should_quit=1;
	}
}
 
int main(void){
	//char buffer[MAXBUFFER+1];
	//char buffer2[MAXBUFFER+1] = "Welcome\n";
	int optval=1;
	int*actives_sockets,i;
	struct sigaction new_action;

	lsocket*server,*sender;
	lpodrum*sockets;
	lpacket*pck;
	
	/* Init usefull variables */
	nbusers=0;nbmessages=0;nbtoidentify=0;
	should_quit=0;
	
	/* Sigaction */
	new_action.sa_handler = termination_handler;
	sigemptyset(&new_action.sa_mask);
	new_action.sa_flags = 0;
	
	sigaction(SIGTERM,&new_action,NULL);
	sigaction(SIGINT,&new_action,NULL);

	/* Init server */
	server=make_lsocket(" :4242");
	open_lsocket(server,AF_INET,SOCK_STREAM);
	setsockopt(server->file,SOL_SOCKET,SO_REUSEADDR,&optval,sizeof(int));
	bind_lsocket(server);
	listen_lsocket(server,SIZE_PENDING);

	sockets=make_lpodrum(SIZE_PENDING);
	add_lsocket(sockets,server,POLLIN);
	
	create_user("Superman","clarkken");
	create_user("Batman","brucewayne");
	
	/* Start server */
	printf("Starting server on port 4242\n");
	while (!should_quit){
		actives_sockets=listen_lpodrum(sockets,-1);
		
		for(i=0;actives_sockets[i]!=LPOP_ERROR;i++){
			/* 0 is the server address: new connections comes from here */
			if (actives_sockets[i]==0){
				/* Send an answer with the new connection */
				WHERE;
				sender=accept_lsocket(server);
				add_lsocket(sockets,sender,POLLIN|POLLOUT);
				
				message_send(sender,msg_recv,"[S3RV3R] w3lc0me us3r");
				printf("Client connected %s\n",sender->addr);
				
				continue;
			}
			
			if (get_event(sockets,actives_sockets[i])^POLLIN){
				/* Wait for the communication */
				printf("Waiting for incomming communication\n");
				
				pck=message_receive(get_lsocket(sockets,actives_sockets[i]),&sender);
			
				if (pck->type==msg_text){
					printf("[%s] sended %s\n",sender->addr,pck->message);
				} else if (pck->type==msg_kill){
					/* If he wants to die, well, kill it */
					printf("[Server] Client diconnected\n");
					message_send(sender,msg_kill,"[S3RV3R] g00dby3 us3r");
					del_lsocket(sockets,actives_sockets[i]);	
				} else if (pck->type==msg_wtf){
					ERROR("WTF Happened ?");
					del_lsocket(sockets,actives_sockets[i]);
				} else {
					WHERE;printf("%s ???\n",pck->message);
				}
				lpacket_drop(pck);
			}
		}
		free(actives_sockets);
	}
	drop_lpodrum(sockets,1);
	return 0;
}
