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
			//WHERE; printf("%i\n",i);
			if (actives_sockets[i]==0){
				/* Send an answer with the new connection */
				sender=accept_lsocket(server);
				add_lsocket(sockets,sender,POLLIN|POLLOUT);
				
				message_send(sender,msg_recv,"w3lc0me us3r");
				printf("Client connected %s\n",sender->addr);
				
				//pck=message_receive(sender,NULL);
				//printf("%s\n",pck->message);
				continue;
			}
			/* Wait for the communication */
			printf("[Server] Waiting incomming transmission\n");
			pck=message_receive(get_lsocket(sockets,actives_sockets[i]),&sender);
			
			if (pck->type==msg_text){
				printf("[%s] sended <%i> %s\n",
				sender?sender->addr:get_lsocket(sockets,actives_sockets[i])->addr,
				/*sender?(int)sender->file:get_lsocket(sockets,actives_sockets[i])->file,*/
				pck->type,pck->message);
			} else if (pck->type==msg_kill){
				/* If he wants to die, well, kill it */
				printf("Client diconnected\n");
				del_lsocket(sockets,actives_sockets[i]);	
			} else {
				// We won't need him in that case
				//WHERE;
				//close_lsocket(sender,0);
			}
			lpacket_drop(pck);
		}
		free(actives_sockets);
	}
	drop_lpodrum(sockets,1);
	return 0;
}
